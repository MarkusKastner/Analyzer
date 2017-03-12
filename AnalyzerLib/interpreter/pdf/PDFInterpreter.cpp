#include "PDFInterpreter.h"

namespace analyzer {
  namespace interpreter {
    PDFInterpreter::PDFInterpreter()
      :Interpreter(), data(), text(), objects()
    {
    }

    PDFInterpreter::PDFInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data)
      : Interpreter(), data(data), text()
    {
      this->createObjects();
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
      this->createObjects();
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

    void PDFInterpreter::createObjects()
    {
      this->objects.clear();
      size_t objectIndex = 0;
      size_t dataOffset = 0;
      size_t objectOffset = 0;

      while (true) {
        objectIndex = this->findNextObject(objectOffset + dataOffset);
        if (objectIndex > this->data->size()) {
          break;
        }
        dataOffset = this->findDataOffset(objectIndex);
        objectOffset = this->findObjectOffset(dataOffset) - dataOffset;

        if (!this->offsetsValid(dataOffset, objectOffset)) {
          break;
        }

        PDFObject newObject(this->getObjectNumber(objectIndex), this->getObjectRevision(objectIndex));
        newObject.SetData(this->data, dataOffset, objectOffset);
        this->objects.push_back(newObject);
      }
    }

    size_t PDFInterpreter::findNextObject(const size_t & startIndex)
    {
      size_t objectIndex = 0;
      for (size_t i = startIndex; i < this->data->size(); ++i) {
        if (this->isLineBreak(i)) {
          if (Interpreter::toASCII(this->data, i - 4, 4).compare(" obj") != 0) {
            continue;
          }
          objectIndex = this->findPrevLineBreak(i - 3) + 1;
          break;
        }
      }
      if (objectIndex == 0) {
        objectIndex = this->data->size() + 2;
      }
      return objectIndex;
    }

    size_t PDFInterpreter::findDataOffset(const size_t & startIndex)
    {
      size_t objectIndex = 0;
      for (size_t i = startIndex; i < this->data->size(); ++i) {
        if (this->isLineBreak(i)) {
          objectIndex = i + 1;
          while (this->isLineBreak(objectIndex)) {
            objectIndex++;
          }
          break;
        }
      }
      if (objectIndex == 0) {
        objectIndex = this->data->size() + 2;
      }
      return objectIndex;
    }

    size_t PDFInterpreter::findObjectOffset(const size_t & startIndex)
    {
      size_t objectOffset = 0;
      for (size_t i = startIndex; i < this->data->size(); ++i) {
        if (static_cast<char>(this->data->at(i)) == 'e' &&  this->isLineBreak(i - 1)) {
          if (this->isEndObject(i)) {
            objectOffset = i - 3;
            break;
          }
        }
      }
      if (objectOffset == 0) {
        objectOffset = this->data->size() + 2;
      }
      return objectOffset;
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
      if (dataOffset > this->data->size()) {
        return false;
      }
      if (objectOffset > this->data->size()) {
        return false;
      }
      if (dataOffset + objectOffset > this->data->size()) {
        return false;
      }
      return true;
    }

    size_t PDFInterpreter::getObjectNumber(const size_t & objectIndex)
    {
      std::string numString;
      for (size_t i = objectIndex; i < this->data->size(); ++i) {
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
      for (size_t i = objectIndex; i < this->data->size(); ++i) {
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