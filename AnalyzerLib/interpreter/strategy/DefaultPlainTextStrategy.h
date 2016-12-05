#ifndef DEFAULTPLAINTEXTSTRATEGY_H
#define DEFAULTPLAINTEXTSTRATEGY_H

#include "InterpretStrategyImpl.h"

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      class DefaultPlainTextStrategy : public InterpretStrategyImpl
      {
      public:
        DefaultPlainTextStrategy();
        explicit DefaultPlainTextStrategy(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data);

        virtual ~DefaultPlainTextStrategy();

        virtual std::string GetPlainText();
      };
    }
  }
}
#endif