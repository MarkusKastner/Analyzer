/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    Formatter::~Formatter()
    {
    }

    Formatter::Formatter()
      : data(new std::vector<unsigned char>()),
      functionalHighlightExpressions()
    {

    }

    Formatter::Formatter(const std::shared_ptr<std::vector<unsigned char>> & data)
      : data(data),
      functionalHighlightExpressions()
    {
    }

    void Formatter::SetData(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      this->data = data;
    }

    void Formatter::SetHighlightingExpressions()
    {
    }

    void Formatter::AddFunctionalHighlightingExp(const std::wstring & expression)
    {
      this->functionalHighlightExpressions.push_back(expression);
    }

    const std::vector<std::wstring> & Formatter::GetFunctionalHighlightingExp()
    {
      return this->functionalHighlightExpressions;
    }

    const std::shared_ptr<std::vector<unsigned char>> & Formatter::getData()
    {
      return this->data;
    }
  }
}