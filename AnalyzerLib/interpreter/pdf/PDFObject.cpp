/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "PDFObject.h"

namespace analyzer {
  namespace interpreter {
    PDFObject::PDFObject()
      :number(0), revision(0)
    {
    }

    PDFObject::PDFObject(const size_t & number, const size_t & revision)
      :number(number), revision(revision)
    {
    }

    PDFObject::~PDFObject()
    {
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
  }
}