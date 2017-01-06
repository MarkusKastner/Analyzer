#include "XMLFormatter.h"

namespace analyzer{
  namespace interpreter{

    XMLFormatter::XMLFormatter()
      :Formatter()
    {

    }

    XMLFormatter::~XMLFormatter()
    {

    }

    std::wstring XMLFormatter::GetText()
    {
      std::wstring rawText(this->getDataAsWString());
      std::wstring formatedText;

      std::wstring currentGlyph;

      for (auto& it = rawText.begin(); it != rawText.end(); ++it){
        auto letter = (*it);
        if (letter == '<'){
          currentGlyph.clear();
          currentGlyph.push_back(letter);
        }
        else if (letter == '>'){
          currentGlyph.push_back(letter);
          formatedText += currentGlyph;
          auto testIt = it;
          testIt++;
          if (testIt != rawText.end() && (*testIt) == '<'){
            formatedText.push_back('\n');
          }
        }
        else{
          currentGlyph.push_back(letter);
        }

      }
      return formatedText;
    }

    std::wstring XMLFormatter::getDataAsWString()
    {
      std::string asString; 
      auto& data = (*this->getData());
      for (auto& byte : data){
        asString.push_back(static_cast<char>(byte->GetValue()));
      }
      return std::wstring(asString.begin(), asString.end());
    }
  }
}