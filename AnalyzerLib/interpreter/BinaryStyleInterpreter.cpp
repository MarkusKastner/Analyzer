#include "BinaryStyleInterpreter.h"

#include "error\InterpreterException.h"

#include "AnalyzerLib\interpreter\formatter\BitFormatter.h"

namespace analyzer{
  namespace interpreter{

    BinaryStyleInterpreter::BinaryStyleInterpreter()
      :InterpreterDataImpl()
    {
      this->setDetailFormatter(new BitFormatter());
    }

    BinaryStyleInterpreter::BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterDataImpl(byteCollection)
    {
      this->setDetailFormatter(new BitFormatter());
    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {
    }

    void BinaryStyleInterpreter::setFormatter()
    {
      switch (this->getDetailFormat()){
      case analyzer::base::DetailFormat::bits:
        this->setDetailFormatter(new BitFormatter());
        break;
      case analyzer::base::DetailFormat::hex:
        this->setDetailFormatter(new BitFormatter());
        break;
      default:
        this->setDetailFormatter(new BitFormatter());
      }
    }
  }
}