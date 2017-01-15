/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FORMATFINDER_H
#define FORMATFINDER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace core{
    class IMEX FormatFinder
    {
    public:
      enum Format
      {
        unknown = 0,
        text,
        binary,
        xml,
        pdf
      };

      FormatFinder();
      virtual ~FormatFinder();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      void Analyze();
      analyzer::core::FormatFinder::Format GetBaseFormat();
      analyzer::core::FormatFinder::Format GetDetailFormat();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * data;
      analyzer::core::FormatFinder::Format baseFormat;
      analyzer::core::FormatFinder::Format detailFormat;

      void analyzeBaseFormat();
      void analyzeDetailTextFormat();
      
      bool isLetter(const std::shared_ptr<Byte> & byte);
      bool isXML();

    };
  }
}

#endif
