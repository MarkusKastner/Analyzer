#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>

#include "AnalyzerLib\core\ByteCollection.h"

namespace analyzer{
  namespace interpreter{
    class Interpreter
    {
    public:
      virtual bool HasData() = 0;
      virtual void ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data) = 0;
      virtual std::string GetPlainText() = 0;
    };
  }
}
#endif