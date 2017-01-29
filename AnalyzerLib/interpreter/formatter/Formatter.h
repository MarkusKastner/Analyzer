/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FORMATTER_H
#define FORMATTER_H

#include <memory>
#include <vector>
#include <string>

namespace analyzer{
  namespace interpreter{
    class Formatter
    {
    public:
      virtual ~Formatter();

      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual std::shared_ptr<std::wstring> GetText() = 0;

      virtual void SetHighlightingExpressions();
      void AddFunctionalHighlightingExp(const std::wstring & expression);
      virtual const std::vector<std::wstring> & GetFunctionalHighlightingExp();

    protected:
      Formatter();
      explicit Formatter(const std::shared_ptr<std::vector<unsigned char>> & data);
      const std::shared_ptr<std::vector<unsigned char>> & getData();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::vector<std::wstring> functionalHighlightExpressions;
    };
  }
}

#endif