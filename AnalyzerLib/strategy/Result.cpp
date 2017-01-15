/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Result.h"

namespace analyzer{
  namespace strategy{
    Result::~Result()
    {
    }

    Result::Result(const Classification & classification)
      :classification(classification)
    {
    }

    const Result::Classification & Result::GetClassification() const
    {
      return this->classification;
    }
  }
}