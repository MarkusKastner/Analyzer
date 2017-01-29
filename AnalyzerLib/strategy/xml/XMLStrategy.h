/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLSTRATEGY_H
#define XMLSTRATEGY_H

#include <memory>
#include <vector>

#include "AnalyzerLib\strategy\AnalyzingStrategy.h"

namespace analyzer{
  namespace strategy{
    class XMLStrategy : public AnalyzingStrategy
    {
    public:
      XMLStrategy();
      virtual ~XMLStrategy();

    protected:
      virtual void analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual bool compareResult(const std::shared_ptr<Result> & result1, const std::shared_ptr<Result> & result2);
    };
  }
}
#endif