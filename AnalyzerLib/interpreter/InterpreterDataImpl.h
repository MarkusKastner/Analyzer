/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETERDATAIMPL_H
#define INTERPRETERDATAIMPL_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <mutex>

#include "InterpreterObserverImpl.h"

namespace analyzer{
  namespace interpreter{
    class Formatter;
    class IMEX InterpreterDataImpl : public InterpreterObserverImpl
    {
    private:
      InterpreterDataImpl(const InterpreterDataImpl&){}
      InterpreterDataImpl & operator=(const InterpreterDataImpl&){ return *this; }

    public:
      InterpreterDataImpl();
      explicit InterpreterDataImpl(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection);
      virtual ~InterpreterDataImpl();

      virtual bool HasData();
      virtual void ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      virtual void ResetData(const std::vector<char> & data);
      virtual std::shared_ptr<analyzer::core::ByteCollection> GetData();

      virtual std::shared_ptr<std::wstring> GetText();
      virtual std::vector<std::wstring> GetFunctionalHighlightExpressions();

      virtual void SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify = false);

    protected:
      std::shared_ptr<analyzer::core::ByteCollection> * getByteCollection();
      base::DetailFormat getDetailFormat();

      virtual void setFormatter() = 0;
      void setDetailFormatter(Formatter * formatter);

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * byteCollection;
      std::recursive_mutex * dataLock;

      base::DetailFormat detailFormat;
      std::unique_ptr<Formatter> * formatter;

    };
  }
}
#endif