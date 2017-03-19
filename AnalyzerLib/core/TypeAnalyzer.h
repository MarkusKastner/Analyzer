/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TYPEANALYZER_H
#define TYPEANALYZER_H

#include <memory>
#include <vector>

#include "AnalyzerLib\core\FileInfo.h"

namespace analyzer {
  namespace core {
    class TypeAnalyzer
    {
    public:
      const static size_t LenDosHeaderInclMsg = 110;
      const static size_t LenBMPHeader = 14;

      ~TypeAnalyzer();

      static TypeAnalyzer * GetInstance();

      FileInfo GetFileInfo(const std::shared_ptr<std::vector<unsigned char>> & data);
      FileInfo GetFileInfo(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & indexBegin, const size_t & offset);

    private:
      size_t indexBegin;
      size_t offset;

      static TypeAnalyzer * instance;
      TypeAnalyzer();

      bool isXML(const std::shared_ptr<std::vector<unsigned char>> & data);
      bool isASCII(const std::shared_ptr<std::vector<unsigned char>> & data);
      bool isPDF(const std::shared_ptr<std::vector<unsigned char>> & data);
      bool isWinExec(const std::shared_ptr<std::vector<unsigned char>> & data);
      bool isBmp(const std::shared_ptr<std::vector<unsigned char>> & data);

      static std::string toASCII(const std::shared_ptr<std::vector<unsigned char>> & data, const size_t & index, const size_t & offset);
    };
  }
}
#endif