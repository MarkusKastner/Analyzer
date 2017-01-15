/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef RESULT_H
#define RESULT_H

namespace analyzer{
  namespace strategy{
    class Result
    {
    private:
      Result(){}

    public:
      enum Classification
      {
        unknown = 0,
        warning,
        alarm,
        checked
      };

      virtual ~Result();

      const Classification & GetClassification() const;

    protected:
      explicit Result(const Classification & classification);

    private:
      Classification classification;
    };
  }
}
#endif