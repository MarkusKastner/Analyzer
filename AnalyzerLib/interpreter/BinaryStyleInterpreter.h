#ifndef BINARYSTYLEINTERPRETER_H
#define BINARYSTYLEINTERPRETER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>

#include "InterpreterDataImpl.h"

namespace analyzer{
  namespace interpreter{
    class IMEX BinaryStyleInterpreter : public InterpreterDataImpl
    {
    private:
      BinaryStyleInterpreter(const BinaryStyleInterpreter&){}
      BinaryStyleInterpreter & operator=(const BinaryStyleInterpreter&){ return *this; }

    public:
      BinaryStyleInterpreter();
      explicit BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~BinaryStyleInterpreter();

      virtual std::string GetPlainText();
      virtual std::wstring GetFormatedText();

    protected:
      virtual void setFormatter();

    };
  }
}

#endif