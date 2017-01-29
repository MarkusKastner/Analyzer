/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BitFormatter.h"

#include <locale>
#include <codecvt>
#include <string>
#include <bitset>

namespace analyzer{
  namespace interpreter{

    BitFormatter::BitFormatter()
      :Formatter()
    {
    }

    BitFormatter::BitFormatter(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Formatter(data)
    {
    }

    BitFormatter::~BitFormatter()
    {
    }

    std::shared_ptr<std::wstring> BitFormatter::GetText()
    {
      auto& data = (*this->getData());

      if (data.size() == 0){
        return std::shared_ptr<std::wstring>(new std::wstring());
      }
      int byteCounter = 0;
      std::string asString;
      std::string valueString("    ");
      std::string nullByte("        ");

      for (auto& byte : data){
      
        asString += std::bitset<8>(byte).to_string();
        valueString += std::string('[' + this->make3Digit(byte) + ']');

        byteCounter++;
        
        if (byteCounter < 4){
          asString += "  ";
        }
        else{
          asString += valueString;
          valueString = "    ";
          asString += "\n";
          byteCounter = 0;
        }
      }

      if (byteCounter != 0 && byteCounter < 4){
        for (int i = byteCounter; i < 4; i++){
          asString += nullByte;
          if (i < 3){
            asString += "  ";
          }
        }
        asString += valueString;
      }
      if (!asString.empty()){
        if (asString.back() == ' ' || asString.back() == '\n'){
          asString.pop_back();
        }
      }
      return std::shared_ptr<std::wstring>(new std::wstring(asString.begin(), asString.end()));
    }

    std::string BitFormatter::make3Digit(const unsigned char & byte)
    {
      std::string val(std::to_string(byte));

      if (val.size() < 3){
        while (val.size() != 3){
          val.insert(val.begin(), '0');
        }
      }
      return val;
    }
  }
}
