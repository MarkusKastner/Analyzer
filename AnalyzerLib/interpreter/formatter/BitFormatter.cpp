/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BitFormatter.h"

#include <locale>
#include <codecvt>
#include <string>

namespace analyzer{
  namespace interpreter{

    BitFormatter::BitFormatter()
      :Formatter()
    {
    }

    BitFormatter::~BitFormatter()
    {
    }

    std::shared_ptr<std::wstring> BitFormatter::GetText()
    {
      int byteCounter = 0;
      std::string asString;
      auto& data = (*this->getData());
      for (auto& byte : data){
        asString += byte->GetBitsAsString();
        byteCounter++;
        if (byteCounter < 4){
          asString += " ";
        }
        else{
          asString += "\n";
          byteCounter = 0;
        }
      }
      if (!asString.empty() && asString.back() == ' '){
        asString.pop_back();
      }
      return std::shared_ptr<std::wstring>(new std::wstring(asString.begin(), asString.end()));
    }
  }
}
