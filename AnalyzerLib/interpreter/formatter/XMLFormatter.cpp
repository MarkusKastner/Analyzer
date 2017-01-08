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
      this->createXMLToken();
      std::wstring formatedText;
      std::wstring tabs;
      for (auto it = this->token->begin(); it != this->token->end(); ++it){
        auto checkIt = it;

        switch (it->GetTokenType()){
        case XMLToken::Type::Open:
          formatedText += it->GetText();
          checkIt = it;
          checkIt++;
          if (checkIt != this->token->end() && checkIt->GetTokenType() != XMLToken::Value){
            formatedText += '\n';
            this->increaseTabs(tabs);
            formatedText += tabs;
          }
          break;
        case XMLToken::Type::Close:
          formatedText += it->GetText();
          checkIt = it;
          checkIt++;
          if (checkIt != this->token->end()){
            formatedText += '\n';
            this->decreaseTabs(tabs);
            formatedText += tabs;
          }
          break;
        case XMLToken::Type::Inline:
          formatedText += it->GetText();
          formatedText += '\n';
          checkIt = it;
          checkIt++;
          if (checkIt != this->token->end() && checkIt->GetTokenType() == XMLToken::Close){
            this->decreaseTabs(tabs);
          }
          formatedText += tabs;
          break;
        case XMLToken::Type::Value:
          formatedText += it->GetText();
          break;
        case XMLToken::Type::Comment:
          formatedText += it->GetText();
          formatedText += '\n';
          break;
        }
        
      }
      return formatedText;
    }

    std::vector<XMLFormatter::XMLToken> XMLFormatter::GetXMLToken()
    {
      this->createXMLToken();
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

    std::vector<std::wstring> XMLFormatter::GetOpenHLTags()
    {
      if (this->token->empty() && this->getData()->GetSize() > 0){
        this->createXMLToken();
      }
      std::vector<std::wstring> tags;
      for (auto& xmlToken : (*this->token)){
        if (xmlToken.GetTokenType() == XMLToken::Inline || xmlToken.GetTokenType() == XMLToken::Open){
          this->addToken(tags, xmlToken.GetText());
        }
      }
      return tags;
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

    void XMLFormatter::createXMLToken()
    {
      this->token->clear();
      std::wstring rawText(this->getDataAsWString());

      std::wstring current;
      for (auto& it = rawText.begin(); it != rawText.end(); ++it){
        auto letter = (*it);
        if (letter == '\r' || letter == '\n'){
          continue;
        }
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

    void XMLFormatter::increaseTabs(std::wstring & tabs)
    {
      tabs += L"  ";
    }

    void XMLFormatter::decreaseTabs(std::wstring & tabs)
    {
      if (!tabs.empty()){
        tabs.pop_back();
      }
      if (!tabs.empty()){
        tabs.pop_back();
      }
    }

    void XMLFormatter::addToken(std::vector<std::wstring> & tags, const std::wstring & tokenText)
    {
      std::wstring tag(tokenText.substr(0, tokenText.find_first_of(' ')));
      if (tag.back() == '>'){
        tag.pop_back();
      }
      if (tags.empty()){
        tags.push_back(tag);
      }
      else{
        for (auto existing : tags){
          if (existing.compare(tag) == 0){
            return;
          }
        }
        tags.push_back(tag);
      }
    }
  }
}