/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "XMLInterpreter.h"

namespace analyzer {
  namespace interpreter {
    XMLInterpreter::XMLInterpreter()
      :Interpreter(), data(), text(), tabs()
    {

    }

    XMLInterpreter::XMLInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
      : Interpreter(), data(data), text(), tabs()
    {
    }

    XMLInterpreter::XMLInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
      : Interpreter(indexBegin, offset), data(data), text(), tabs()
    {
    }

    XMLInterpreter::~XMLInterpreter()
    {
    }

    bool XMLInterpreter::HasData()
    {
      return !(!data);
    }

    void XMLInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
    }

    void XMLInterpreter::SetData(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      this->setLimits(indexBegin, offset);
      this->SetData(data);
    }

    const std::string & XMLInterpreter::GetText()
    {
      this->format();
      return this->text;
    }

    core::FileFormat XMLInterpreter::GetFileFormat()
    {
      return core::FileFormat::xml;
    }

    void XMLInterpreter::format()
    {
      size_t begin = 0;
      size_t offset = this->data->size();

      if (this->hasLimits()) {
        begin = this->getIndexBegin();
        offset = this->getOffset();
      }

      std::shared_ptr<std::string> text(new std::string(this->toASCII(this->data, begin, offset)));

      size_t startHeader = text->find_first_of('<');
      size_t endHeader = text->find_first_of('>');

      std::shared_ptr<std::string> formatedText(new std::string(text->substr(startHeader, endHeader - startHeader + 1)));

      bool firstTag = true;
      for (size_t i = endHeader + 1; i < text->size(); i++) {

        if (text->at(i) == '<' && text->at(i - 1) == '>') {

          formatedText->push_back('\n');

          size_t tagEnd = text->find_first_of('>', i);

          wchar_t check1 = text->at(i + 1);
          wchar_t check2 = text->at(tagEnd - 1);

          if (text->at(tagEnd - 1) == '/') {
            *formatedText += this->tabs;
          }
          else if (text->at(i + 1) == '/') {
            this->decreaseTabs();
            *formatedText += this->tabs;
          }
          else {
            *formatedText += this->tabs;
            size_t tagEnd = text->find_first_of('>', i);
            if (tagEnd + 1 < text->size() && text->at(tagEnd + 1) == '<') {
              this->increaseTabs();
            }
          }
        }
        formatedText->push_back(text->at(i));
      }
      this->text = *formatedText.get();
    }

    void XMLInterpreter::increaseTabs()
    {
      this->tabs += "  ";
    }

    void XMLInterpreter::decreaseTabs()
    {
      if (!this->tabs.empty()) {
        this->tabs.pop_back();
      }
      if (!this->tabs.empty()) {
        this->tabs.pop_back();
      }
    }
  }
}