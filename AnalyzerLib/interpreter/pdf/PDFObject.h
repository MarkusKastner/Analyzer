/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECT_H
#define PDFOBJECT_H

#include <string>

namespace analyzer {
  namespace interpreter {
    class PDFObject
    {
    public:
      PDFObject();
      explicit PDFObject(const size_t & number, const size_t & revision);
      virtual ~PDFObject();

      void SetNumber(const size_t & number, const size_t & revision);

      const size_t & GetNumber() const;
      const size_t & GetRevision() const;

    private:
      size_t number;
      size_t revision;
    };
  }
}

#endif