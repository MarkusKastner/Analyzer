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

    std::wstring BitFormatter::GetText()
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
      return std::wstring(asString.begin(), asString.end());
    }
  }
}
