/* Copyright (C) 2016 - 2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "XMLFormatter.h"
#include <cctype>

namespace analyzer{
  namespace interpreter{

    XMLFormatter::XMLFormatter()
      :Formatter(), tabs(new std::wstring())
    {

    }

    XMLFormatter::~XMLFormatter()
    {
      delete this->tabs;
    }

    std::shared_ptr<std::wstring> XMLFormatter::GetText()
    {
      std::wstring text = this->getDataAsWString();

      if (text.size() < 20){
        return std::shared_ptr<std::wstring>(new std::wstring(text));
      }

      std::shared_ptr<std::wstring> formatedText(new std::wstring(text.substr(0, 20)));

      bool firstTab = true;
      for (size_t i = 20; i < text.size(); i++){
        if (text.at(i) == '<' && text.at(i - 1) == '>'){
          formatedText->push_back('\n');
          size_t tagEnd = text.find_first_of('>', i);
          wchar_t check1 = text.at(i + 1);
          wchar_t check2 = text.at(tagEnd - 1);
          if (text.at(i + 1) == '/' || text.at(tagEnd - 1) == '/'){
            this->decreaseTabs();
            *formatedText += *this->tabs;
          }
          else{
            if (firstTab){
              firstTab = false;
            }
            else{
              this->increaseTabs();
            }
            *formatedText += *this->tabs;
          }
        }
        formatedText->push_back(text.at(i));
      }
      return formatedText;
    }

    std::wstring XMLFormatter::getDataAsWString()
    {
      std::string asString; 
      auto& data = (*this->getData());
      for (auto& byte : data){
        char val = static_cast<char>(byte->GetValue());
        if (std::iscntrl(val)){
          continue;
        }
        asString.push_back(val);
      }
      return std::wstring(asString.begin(), asString.end());
    }

    void XMLFormatter::increaseTabs()
    {
      *this->tabs += L"  ";
    }

    void XMLFormatter::decreaseTabs()
    {
      if (!this->tabs->empty()){
        this->tabs->pop_back();
      }
      if (!this->tabs->empty()){
        this->tabs->pop_back();
      }
    }
  }
}