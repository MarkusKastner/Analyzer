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

    std::vector<XMLFormatter::XMLToken> XMLFormatter::GetXMLToken()
    {
      std::vector<XMLFormatter::XMLToken> token;

      for (int i = 0; i < 6; i++){
        token.push_back(XMLToken(L"<>", XMLToken::Type::Inline));
      }
      //std::wstring rawText(this->getDataAsWString());

      //std::wstring current;
      //for (auto& it = rawText.begin(); it != rawText.end(); ++it){
      //  auto letter = (*it);
      //  if (letter == '<'){
      //    current.clear();
      //    current.push_back(letter);
      //  }
      //  else if (letter == '>'){
      //  }
      //  else{
      //    current.push_back(letter);
      //  }
      //}
      
      return token;
    }

    XMLFormatter::XMLToken XMLFormatter::CreateToken(const std::wstring & token)
    {
      if (this->isOpenToken(token)){
        return XMLToken(token, XMLToken::Open);
      }
      if (this->isClosingToken(token)){
        return XMLToken(token, XMLToken::Close);
      }
      return XMLToken(token, XMLToken::Inline);
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

    bool XMLFormatter::isOpenToken(const std::wstring & text)
    {
      if (text.empty() || text.at(0) != '<'){
        return false;
      }
      if (text.back() != '>' || text.at(text.size() - 2) == '/'){
        return false;
      }
      if (text.at(1) == '!' || text.at(1) == '/' || text.at(1) == '?'){
        return false;
      }
      return true;
    }

    bool XMLFormatter::isClosingToken(const std::wstring & text)
    {
      if (text.empty() || text.at(1) != '/' || text.at(0) != '<' || text.back() != '>'){
        return false;
      }
      return true;
    }
  }
}