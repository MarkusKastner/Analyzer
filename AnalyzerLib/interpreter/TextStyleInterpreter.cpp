/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "TextStyleInterpreter.h"

#include "error\InterpreterException.h"

#include "AnalyzerLib\interpreter\formatter\SimpleTextFormatter.h"
#include "AnalyzerLib\interpreter\formatter\XMLFormatter.h"

namespace analyzer{
  namespace interpreter{
    TextStyleInterpreter::TextStyleInterpreter()
      :InterpreterDataImpl()
    {
      this->setDetailFormatter(new SimpleTextFormatter());
    }

    TextStyleInterpreter::TextStyleInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data)
      :InterpreterDataImpl(data)
    {
      this->setDetailFormatter(new SimpleTextFormatter());
    }

    TextStyleInterpreter::~TextStyleInterpreter()
    {
    }

    bool TextStyleInterpreter::IsXML()
    {
      auto text(this->GetText());
      if (text->size() < 21) {
        return false;
      }
      size_t startIndex = text->find(L"<?xml version=");
      if (startIndex < text->size()) {
        return true;
      }
      else {
        return false;
      }
    }

    void TextStyleInterpreter::setFormatter()
    {
      switch (this->getDetailFormat()){
      case analyzer::base::DetailFormat::simpleText:
        this->setDetailFormatter(new SimpleTextFormatter(this->GetData()));
        break;
      case analyzer::base::DetailFormat::xml:
        this->setDetailFormatter(new XMLFormatter(this->GetData()));
        break;
      case analyzer::base::DetailFormat::pdf:
        this->setDetailFormatter(new SimpleTextFormatter(this->GetData()));
        break;
      default:
        this->setDetailFormatter(new SimpleTextFormatter(this->GetData()));
      }
    }
  }
}