/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "XMLStrategy.h"

namespace analyzer{
  namespace strategy{
    XMLStrategy::XMLStrategy()
      :AnalyzingStrategy()
    {

    }

    XMLStrategy::~XMLStrategy()
    {

    }


    void XMLStrategy::analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {

    }

    bool XMLStrategy::compareResult(const std::shared_ptr<Result> & result1, const std::shared_ptr<Result> & result2)
    {
      return false;
    }

  }
}