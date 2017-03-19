/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFObject.h"
#include "AnalyzerLib/interpreter/error/InterpreterException.h"

namespace analyzer {
  namespace interpreter {
    PDFObject::PDFObject()
      :number(0), revision(0), dataOffset(0), objectOffset(0), streamOffset(0), data(), isFolded(true)
    {
    }

    PDFObject::PDFObject(const size_t & number, const size_t & revision)
      :number(number), revision(revision), dataOffset(0), objectOffset(0), streamOffset(0), data(), isFolded(true)
    {
    }

    PDFObject::~PDFObject()
    {
    }

    PDFObject::PDFObject(const PDFObject & other)
      :number(other.number), revision(other.revision), dataOffset(other.dataOffset), streamOffset(other.streamOffset), objectOffset(other.objectOffset),
      data(other.data), isFolded(other.isFolded)
    {
    }

    PDFObject & PDFObject::operator=(const PDFObject & other)
    {
      if (this == &other) {
        return *this;
      }
      this->number = other.number;
      this->revision = other.revision;
      this->dataOffset = other.dataOffset;
      this->objectOffset = other.objectOffset;
      this->data = other.data;
      this->isFolded = other.isFolded;
      return *this;
    }

    void PDFObject::SetNumber(const size_t & number, const size_t & revision)
    {
      this->number = number;
      this->revision = revision;
    }

    const size_t & PDFObject::GetNumber() const
    {
      return this->number;
    }

    const size_t & PDFObject::GetRevision() const
    {
      return this->revision;
    }

    void PDFObject::SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t dataOffset, const size_t & objectOffset)
    {
      this->data = data;
      this->dataOffset = dataOffset;
      this->objectOffset = objectOffset;
    }

    const size_t & PDFObject::GetDataOffset()
    {
      return this->dataOffset;
    }

    const size_t & PDFObject::GetObjectOffset()
    {
      return this->objectOffset;
    }

    std::string PDFObject::GetRichTextExpression()
    {
      std::string expr("<h3>");
      if (this->isFolded) {
        expr += "+";
      }
      else {
        expr += "-";
      }
      expr += " Object ";
      expr += std::to_string(this->number);
      expr += " ";
      expr += std::to_string(this->revision);
      expr += ("</h3>");
      if (!this->isFolded) {
        expr += ("<p>");
        expr += this->ObjectData2String();
        expr += ("</p>");
      }
      return expr;
    }

    void PDFObject::Fold()
    {
      this->isFolded = true;
    }

    void PDFObject::Unfold()
    {
      this->isFolded = false;
    }

    const bool & PDFObject::IsFolded() const
    {
      return this->isFolded;
    }

    std::string PDFObject::ObjectData2String()
    {
      size_t limit = this->dataOffset + this->objectOffset;
      if (this->streamOffset > 0) {
        limit = this->streamOffset - 1;
      }
      if (this->dataOffset + this->objectOffset > data->size()) {
        throw InterpreterException("Invalid index or offset value in TypeAnalyzer::toASCII()");
      }
      std::string text;
      for (size_t i = this->dataOffset; i <= limit; ++i) {
        char letter = static_cast<char>(data->at(i));
        if ('<' == letter) {
          text += "&lt;";
        }
        else if ('>' == letter) {
          text += "&gt;";
        }
        else if ('&' == letter) {
          text += "&amp;";
        }
        else if ('"' == letter) {
          text += "&quot;";
        }
        else if ('\n' == letter) {
          continue;
        }
        else if ('\r' == letter) {
          continue;
        }
        else {
          text.push_back(letter);
        }
      }
      if (this->streamOffset > 0) {
        text += "<br>Stream: Object ";
        text += std::to_string(this->number);
        text += "-";
        text += std::to_string(this->revision);
      }
      return text;
    }

    bool PDFObject::HasStreamObj()
    {
      std::string streamTag("stream");
      std::string endStreamTag("endstream");

      if (this->objectOffset < streamTag.size() + endStreamTag.size()) {
        return false;
      }

      for (size_t i = this->dataOffset; i < this->dataOffset + this->objectOffset - streamTag.size(); ++i) {
        if (static_cast<char>(this->data->at(i)) == 's') {
          std::string found(this->data->begin() + i, this->data->begin() + i + streamTag.size());
          if(found.compare(streamTag) == 0){
            this->streamOffset = i;
            return true;
          }
          else {
            continue;
          }
        }
      }
      return false;
    }

    size_t PDFObject::FindStreamStartIndex()
    {
      std::string streamTag("stream");
      size_t streamStartIndex = 0;
      for (size_t i = this->dataOffset; i < this->dataOffset + this->objectOffset - streamTag.size(); ++i) {
        if (static_cast<char>(this->data->at(i)) == 's') {
          std::string found(this->data->begin() + i, this->data->begin() + i + streamTag.size());
          if (found.compare(streamTag) == 0) {
            streamStartIndex = i + streamTag.size();
            break;
          }
        }
      }
      return streamStartIndex;
    }

    size_t PDFObject::FindStreamOffset(const size_t & streamStartIndex)
    {
      std::string streamTag("endstream");
      size_t streamEndIndex = 0;
      size_t iLog = 0;
      size_t searchLimit = this->dataOffset + this->objectOffset - streamTag.size() + 1;
      for (size_t i = streamStartIndex; i < searchLimit; ++i) {
        if (static_cast<char>(this->data->at(i)) == 'e') {
          std::string found(this->data->begin() + i, this->data->begin() + i + streamTag.size());
          if (found.compare(streamTag) == 0) {
            streamEndIndex = i - 1;
            break;
          }
        }
        iLog = i;
      }
      size_t result = streamEndIndex - streamStartIndex + 1;
      if (result > this->objectOffset) {
        throw - 1;
      }
      return result;
    }
  }
}