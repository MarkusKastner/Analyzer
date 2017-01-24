/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "BinaryStyleInterpreter.h"

#include "error\InterpreterException.h"

#include "AnalyzerLib\interpreter\formatter\BitFormatter.h"
#include "AnalyzerLib\interpreter\formatter\HexFormatter.h"

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
        this->setDetailFormatter(new HexFormatter());
        break;
      default:
        this->setDetailFormatter(new BitFormatter());
      }
    }
  }
}