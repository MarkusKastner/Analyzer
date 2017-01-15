/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "SimpleTextFormatter.h"

#include <locale>
#include <codecvt>
#include <string>

namespace analyzer{
  namespace interpreter{

    SimpleTextFormatter::SimpleTextFormatter()
      :Formatter()
    {

    }

    SimpleTextFormatter::~SimpleTextFormatter()
    {
    }

    std::shared_ptr<std::wstring> SimpleTextFormatter::GetText()
    {
      std::string asString;
      auto& data = (*this->getData());
      for (auto& byte : data){
        asString.push_back(static_cast<char>(byte->GetValue()));
      }
      std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
      return std::shared_ptr<std::wstring>(new std::wstring(converter.from_bytes(asString)));
    }
  }
}