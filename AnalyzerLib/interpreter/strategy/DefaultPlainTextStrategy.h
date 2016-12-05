#ifndef DEFAULTPLAINTEXTSTRATEGY_H
#define DEFAULTPLAINTEXTSTRATEGY_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)

#endif
#include "InterpretStrategyImpl.h"

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      class IMEX DefaultPlainTextStrategy : public InterpretStrategyImpl
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