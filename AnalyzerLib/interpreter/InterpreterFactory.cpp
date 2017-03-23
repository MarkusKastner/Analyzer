/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InterpreterFactory.h"
#include "AnalyzerLib\core\TypeAnalyzer.h"

#include "ASCIIInterpreter.h"
#include "XMLInterpreter.h"
#include "BMPInterpreter.h"
#include "pdf/PDFInterpreter.h"
#include "HEXInterpreter.h"

namespace analyzer {
  namespace interpreter {
    InterpreterFactory::InterpreterFactory()
    {
    }

    InterpreterFactory::~InterpreterFactory()
    {
    }

    InterpreterFactory * InterpreterFactory::GetInstance()
    {
      if (nullptr == InterpreterFactory::instance) {
        InterpreterFactory::instance = new InterpreterFactory();
      }
      return InterpreterFactory::instance;
    }

    std::shared_ptr<Interpreter> InterpreterFactory::CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      auto fileInfo = analyzer::core::TypeAnalyzer::GetInstance()->GetFileInfo(data);

      switch (fileInfo.Format) {
      case core::FileFormat::empty:
        return std::shared_ptr<Interpreter>();
      case core::FileFormat::unknown:
        return std::shared_ptr<Interpreter>(new HEXInterpreter(data));
      case core::FileFormat::ascii:
        return std::shared_ptr<Interpreter>(new ASCIIInterpreter(data));
      case core::FileFormat::xml:
        return std::shared_ptr<Interpreter>(new XMLInterpreter(data));
      case core::FileFormat::bmp:
        return std::shared_ptr<Interpreter>(new BMPInterpreter(data));
      case core::FileFormat::pdf:
        return std::shared_ptr<Interpreter>(new PDFInterpreter(data));
      default:
        return std::shared_ptr<Interpreter>(new HEXInterpreter(data));
      }
    }

    std::shared_ptr<Interpreter> InterpreterFactory::CreateInterpreter(const std::shared_ptr<std::vector<unsigned char>>& data, const size_t & indexBegin, const size_t & offset)
    {
      auto fileInfo = analyzer::core::TypeAnalyzer::GetInstance()->GetFileInfo(data, indexBegin, offset);

      switch (fileInfo.Format) {
      case core::FileFormat::empty:
        return std::shared_ptr<Interpreter>();
      case core::FileFormat::unknown:
        return std::shared_ptr<Interpreter>(new HEXInterpreter(data, indexBegin, offset));
      case core::FileFormat::ascii:
        return std::shared_ptr<Interpreter>(new ASCIIInterpreter(data, indexBegin, offset));
      case core::FileFormat::xml:
        return std::shared_ptr<Interpreter>(new XMLInterpreter(data, indexBegin, offset));
      case core::FileFormat::bmp:
        return std::shared_ptr<Interpreter>(new BMPInterpreter(data, indexBegin, offset));
      case core::FileFormat::pdf:
        return std::shared_ptr<Interpreter>(new PDFInterpreter(data, indexBegin, offset));
      default:
        return std::shared_ptr<Interpreter>(new HEXInterpreter(data, indexBegin, offset));
      }
    }

    InterpreterFactory * InterpreterFactory::instance = nullptr;
  }
}