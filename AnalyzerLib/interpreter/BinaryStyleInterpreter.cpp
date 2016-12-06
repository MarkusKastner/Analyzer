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
      this->createGlyphs();
    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {
    }

    std::string BinaryStyleInterpreter::GetPlainText()
    {
      std::string output;
      if (this->HasData()){
        for (auto byte : *this->getByteCollection()->get()){
          output += byte->GetBitsAsString();
          output += " ";
        }
        output.pop_back();
      }
      return output;
    }
  }
}