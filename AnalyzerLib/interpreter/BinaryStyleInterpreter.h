#ifndef BINARYSTYLEINTERPRETER_H
#define BINARYSTYLEINTERPRETER_H

#include <memory>

#include "Interpreter.h"
#include "..\core\ByteCollection.h"

namespace analyzer{
  namespace interpreter{
    class BinaryStyleInterpreter : public Interpreter
    {
    public:
      BinaryStyleInterpreter();
      explicit BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~BinaryStyleInterpreter();

      virtual bool HasData();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> byteCollection;
    };
  }
}

#endif