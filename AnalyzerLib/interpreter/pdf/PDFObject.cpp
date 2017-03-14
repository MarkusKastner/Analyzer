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
      :number(0), revision(0), dataOffset(0), objectOffset(0), data(), isFolded(true)
    {
    }

    PDFObject::PDFObject(const size_t & number, const size_t & revision)
      :number(number), revision(revision), dataOffset(0), objectOffset(0), data(), isFolded(true)
    {
    }

    PDFObject::~PDFObject()
    {
    }

    PDFObject::PDFObject(const PDFObject & other)
      :number(other.number), revision(other.revision), dataOffset(other.dataOffset), objectOffset(other.objectOffset), 
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
      if (this->dataOffset + this->objectOffset > data->size()) {
        throw InterpreterException("Invalid index or offset value in TypeAnalyzer::toASCII()");
      }
      std::string text;
      for (size_t i = this->dataOffset; i <= this->dataOffset + this->objectOffset; ++i) {
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
        else {
          text.push_back(letter);
        }
      }
      return text;
    }

    std::string PDFObject::dataSection2String()
    {
      if (this->dataOffset + this->objectOffset > data->size()) {
        throw InterpreterException("Invalid index or offset value in TypeAnalyzer::toASCII()");
      }
      std::string text;
      for (size_t i = this->dataOffset; i <= this->dataOffset + this->objectOffset; ++i) {
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
        else {
          text.push_back(letter);
        }
      }
      return text;
    }
  }
}