#include "XMLFormatter.h"

namespace analyzer{
  namespace interpreter{

    XMLFormatter::XMLFormatter()
      :Formatter(), token(new std::vector<XMLFormatter::XMLToken>())
    {

    }

    XMLFormatter::~XMLFormatter()
    {
      delete this->token;
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
      this->token->clear();
      std::wstring rawText(this->getDataAsWString());

      std::wstring current;
      for (auto& it = rawText.begin(); it != rawText.end(); ++it){
        auto letter = (*it);
        if (letter == '<'){
          this->onOpenChar(current, letter);
        }
        else if (letter == '>'){
          this->onCloseChar(current, letter);
        }
        else{
          current.push_back(letter);
        }
      }
      return *this->token;
    }

    XMLFormatter::XMLToken XMLFormatter::CreateToken(const std::wstring & token)
    {
      if (this->isOpenToken(token)){
        return XMLToken(token, XMLToken::Open);
      }
      if (this->isClosingToken(token)){
        return XMLToken(token, XMLToken::Close);
      }
      if (this->isInlineToken(token)){
        return XMLToken(token, XMLToken::Inline);
      }
      if (this->isCommentToken(token)){
        return XMLToken(token, XMLToken::Comment);
      }
      if (this->isHeaderToken(token)){
        return XMLToken(token, XMLToken::Inline);
      }
      return XMLToken(token, XMLToken::Value);
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

    void XMLFormatter::onOpenChar(std::wstring & current, const wchar_t & letter)
    {
      if (!current.empty()){
        token->push_back(this->CreateToken(current));
        current.clear();
      }
      current.push_back(letter);
    }

    void XMLFormatter::onCloseChar(std::wstring & current, const wchar_t & letter)
    {
      current.push_back(letter);
      if (!current.empty()){
        token->push_back(this->CreateToken(current));
        current.clear();
      }
    }

    bool XMLFormatter::isOpenToken(const std::wstring & text)
    {
      if (text.empty() || text.size() < 2 || text.at(0) != '<'){
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

    bool XMLFormatter::isInlineToken(const std::wstring & text)
    {
      if (text.empty() || text.size() < 2 || text.at(text.size() - 2) != '/' || text.at(0) != '<' || text.back() != '>'){
        return false;
      }
      return true;
    }

    bool XMLFormatter::isHeaderToken(const std::wstring & text)
    {
      if (text.empty() || text.size() < 2 || text.at(1) != '?' || text.at(0) != '<' || text.back() != '>'){
        return false;
      }
      return true;
    }

    bool XMLFormatter::isCommentToken(const std::wstring & text)
    {
      if (text.empty() || text.size() < 7 || text.at(1) != '!' || text.at(0) != '<' || text.back() != '>'){
        return false;
      }
      if (text.substr(0, 4).compare(L"<!--") == 0 && text.substr(text.size() - 4, 3).compare(L"-->")){
        return true;
      }
      return false;
    }
  }
}