#include "BinaryStyleInterpreter.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{

    BinaryStyleInterpreter::BinaryStyleInterpreter()
      :InterpreterDataImpl()
    {
    }

    BinaryStyleInterpreter::BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterDataImpl(byteCollection)
    {
    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {
    }

    std::string BinaryStyleInterpreter::GetPlainText()
    {
      std::string output;
      for (auto byte : *this->getByteCollection()->get()){
        output += byte->GetBitsAsString();
        output += " ";
      }
      output.pop_back();
      return output;
    }
  }
}