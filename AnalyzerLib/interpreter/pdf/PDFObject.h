/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFOBJECT_H
#define PDFOBJECT_H

#include <string>
#include <memory>
#include <vector>

namespace analyzer {
  namespace interpreter {
    class PDFObject
    {
    public:
      PDFObject();
      explicit PDFObject(const size_t & number, const size_t & revision);
      virtual ~PDFObject();

      PDFObject(const PDFObject & other);
      PDFObject & operator=(const PDFObject & other);

      void SetNumber(const size_t & number, const size_t & revision);

      const size_t & GetNumber() const;
      const size_t & GetRevision() const;

      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t dataOffset, const size_t & objectOffset);
      const size_t & GetDataOffset();
      const size_t & GetObjectOffset();

      std::string GetRichTextExpression();

      void Fold();
      void Unfold();
      const bool & IsFolded() const;

      std::string ObjectData2String();

      bool HasStreamObj();
      size_t FindStreamStartIndex();
      size_t FindStreamOffset(const size_t & streamStartIndex = 0);

    private:
      size_t number;
      size_t revision;
      size_t dataOffset;
      size_t objectOffset;
      size_t streamOffset;
      std::shared_ptr<std::vector<unsigned char>> data;
      bool isFolded;
    };
  }
}

#endif