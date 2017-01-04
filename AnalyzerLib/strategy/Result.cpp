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