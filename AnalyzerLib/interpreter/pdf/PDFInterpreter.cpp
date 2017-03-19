#include "PDFInterpreter.h"

#include <algorithm>

#include "AnalyzerLib\core\InternalFile.h"


namespace analyzer {
  namespace interpreter {
    PDFInterpreter::PDFInterpreter()
      :Interpreter(), data(), text(), objects(), maxIndex(0)
    {
    }

    PDFInterpreter::PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data)
      : Interpreter(), data(data), text(), maxIndex(data->size())
    {
    }

    PDFInterpreter::PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      : Interpreter(indexBegin, offset), data(data), text(), maxIndex(offset + indexBegin)
    {
    }

    PDFInterpreter::~PDFInterpreter()
    {
    }

    bool PDFInterpreter::HasData()
    {
      return !(!data);
    }

    void PDFInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
      if (this->hasLimits()) {
        this->maxIndex = this->getIndexBegin() + this->getOffset();
      }
      else {
        this->maxIndex = this->data->size();
      }
    }

    void PDFInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->setLimits(indexBegin, offset);
      this->SetData(data);
    }

    const std::string & PDFInterpreter::GetText()
    {
      this->text = "<h3>PDF</h3>";
      this->text += "<p>Version: ";
      this->text += Interpreter::toASCII(this->data, 5, 3);
      this->text += "</p>";
      for (auto& obj : this->objects) {
        this->text += obj.GetRichTextExpression();
      }
      return this->text;
    }

    core::FileFormat PDFInterpreter::GetFileFormat()
    {
      return core::FileFormat::pdf;
    }

    bool PDFInterpreter::UseRichText()
    {
      return true;
    }

    void PDFInterpreter::DoSpecialProcessing()
    {
      this->CreateObjects();
    }

    void PDFInterpreter::AddPDFObject(const PDFObject & object)
    {
      this->objects.push_back(object);
    }

    PDFObject PDFInterpreter::GetPDFObject(const size_t & number, const size_t & revision)
    {
      for (auto& object : this->objects) {
        if (object.GetNumber() == number && object.GetRevision() == revision) {
          return object;
        }
      }
      return PDFObject();
    }

    void PDFInterpreter::SwitchFolding(const std::string & objectName)
    {
      size_t numberIndex = objectName.find_first_of(' ') + 1;
      size_t revisionIndex = objectName.find(' ', numberIndex) + 1;

      size_t number = atoi(objectName.substr(numberIndex, revisionIndex - numberIndex).c_str());
      size_t revision = atoi(objectName.substr(revisionIndex, objectName.size() - revisionIndex).c_str());

      for (auto& object : this->objects) {
        if (object.GetNumber() == number && object.GetRevision() == revision) {
          if (object.IsFolded()) {
            object.Unfold();
          }
          else {
            object.Fold();
          }
        }
      }
    }

    void PDFInterpreter::CreateObjects()
    {
      this->objects.clear();
      size_t objectIndex = 0;
      size_t dataOffset = this->getIndexBegin();
      size_t objectOffset = 0;

      while (true) {
        objectIndex = this->findNextObject(objectOffset + dataOffset);
        if (objectIndex > this->maxIndex) {
          break;
        }
        dataOffset = this->findDataOffset(objectIndex);
        objectOffset = this->findObjectEndIndex(dataOffset) - dataOffset;

        if (!this->offsetsValid(dataOffset, objectOffset)) {
          break;
        }

        PDFObject newObject(this->getObjectNumber(objectIndex), this->getObjectRevision(objectIndex));
        newObject.SetData(this->data, dataOffset, objectOffset);

        this->objects.push_back(newObject);
      }

      std::sort(this->objects.begin(), this->objects.end(), smallerThen());

      for (auto& obj : this->objects) {
        if (obj.HasStreamObj()) {
          std::string name("Object " + std::to_string(obj.GetNumber()) + "-" + std::to_string(obj.GetRevision()));
          size_t index = obj.FindStreamStartIndex();
          size_t offset = obj.FindStreamOffset(index);
          std::shared_ptr<core::File> newFile(new core::InternalFile(name, this->data, index, offset));
          this->AddInternalFile(newFile);
        }
      }
    }

    size_t PDFInterpreter::findNextObject(const size_t & startIndex)
    {
      size_t objectIndex = 0;
      for (size_t i = startIndex; i < this->maxIndex; ++i) {
        if (this->data->at(i) == 'o') {
          if (Interpreter::toASCII(this->data, i - 1, 4).compare(" obj") != 0) {
            continue;
          }
          objectIndex = this->findPrevLineBreak(i - 3) + 1;
          break;
        }
      }
      if (objectIndex == 0) {
        objectIndex = this->maxIndex + 2;
      }
      return objectIndex;
    }

    size_t PDFInterpreter::findDataOffset(const size_t & startIndex)
    {
      size_t objectIndex = 0;
      for (size_t i = startIndex; i < this->maxIndex; ++i) {
        if (this->data->at(i) == 'o') {
          if (Interpreter::toASCII(this->data, i - 1, 4).compare(" obj") == 0) {
            objectIndex = i + 3;
            while (true) {
              if (this->isValidSign(objectIndex)) {
                break;
              }
              objectIndex++;
            }
          }
        }
        if (objectIndex != 0) {
          break;
        }
      }
      if (objectIndex == 0) {
        objectIndex = this->maxIndex + 2;
      }
      return objectIndex;
    }

    size_t PDFInterpreter::findObjectEndIndex(const size_t & startIndex)
    {
      size_t objectEndIndex = 0;
      for (size_t i = startIndex; i < this->maxIndex; ++i) {
        if (static_cast<char>(this->data->at(i)) == 'e') {
          if (this->isEndObject(i)) {
            objectEndIndex = i - 1;
            break;
          }
        }
      }
      if (objectEndIndex == 0) {
        objectEndIndex = this->maxIndex + 2;
      }
      return objectEndIndex;
    }

    size_t PDFInterpreter::findPrevLineBreak(const size_t & currentIndex)
    {
      for (size_t i = currentIndex; i > 0; --i) {
        if (this->isLineBreak(i)) {
          return i;
        }
      }
      return this->data->size() + 2;
    }

    bool PDFInterpreter::offsetsValid(const size_t & dataOffset, const size_t & objectOffset)
    {
      if (dataOffset > this->maxIndex) {
        return false;
      }
      if (objectOffset > this->maxIndex) {
        return false;
      }
      if (dataOffset + objectOffset > this->maxIndex) {
        return false;
      }
      return true;
    }

    size_t PDFInterpreter::getObjectNumber(const size_t & objectIndex)
    {
      std::string numString;
      for (size_t i = objectIndex; i < this->maxIndex; ++i) {
        char letter = static_cast<char>(this->data->at(i));
        if (' ' == letter) {
          break;
        }
        else {
          numString += letter;
        }
      }

      return static_cast<size_t>(atoi(numString.c_str()));
    }

    size_t PDFInterpreter::getObjectRevision(const size_t & objectIndex)
    {
      std::string numString;
      bool objectNumSpaceFound = false;
      for (size_t i = objectIndex; i < this->maxIndex; ++i) {
        char letter = static_cast<char>(this->data->at(i));
        if (' ' == static_cast<char>(this->data->at(i))) {
          if (!objectNumSpaceFound) {
            objectNumSpaceFound = true;
          }
          else {
            break;
          }
        }
        else {
          if (objectNumSpaceFound) {
            numString += letter;
          }
        }
      }
      return static_cast<size_t>(atoi(numString.c_str()));
    }

    bool PDFInterpreter::isLineBreak(const size_t & index)
    {
      if (this->data->at(index) == 10 || this->data->at(index) == 13) {
        return true;
      }
      return false;
    }

    bool PDFInterpreter::isValidSign(const size_t & index)
    {
      if (this->data->at(index) == 10 || this->data->at(index) == 13 || this->data->at(index) == 32) {
        return false;
      }
      return true;
    }

    bool PDFInterpreter::isEndObject(const size_t & index)
    {
      std::string eoString("endobj");
      std::string checkString(Interpreter::toASCII(this->data, index, eoString.size()));
      if (checkString.compare(eoString) == 0) {
        return true;
      }
      return false;
    }
  }
}