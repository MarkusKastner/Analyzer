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