#ifndef INTERPRETSTRATEGY_H
#define INTERPRETSTRATEGY_H

#include <string>

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      class InterpretStrategy
      {
      public:
        virtual std::string GetPlainText() = 0;
      };
    }
  }
}

#endif