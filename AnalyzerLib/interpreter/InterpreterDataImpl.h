/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef INTERPRETERDATAIMPL_H
#define INTERPRETERDATAIMPL_H

#include <memory>
#include <mutex>

#include "InterpreterObserverImpl.h"
#include "AnalyzerLib\interpreter\formatter\Formatter.h"

namespace analyzer{
  namespace interpreter{
    class Formatter;
    class InterpreterDataImpl : public InterpreterObserverImpl
    {
    private:
      InterpreterDataImpl(const InterpreterDataImpl&){}
      InterpreterDataImpl & operator=(const InterpreterDataImpl&){ return *this; }

    public:
      InterpreterDataImpl();
      explicit InterpreterDataImpl(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~InterpreterDataImpl();

      virtual bool HasData();

      virtual void ResetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual std::shared_ptr<std::vector<unsigned char>> GetData();

      virtual std::shared_ptr<std::wstring> GetText();
      virtual std::vector<std::wstring> GetFunctionalHighlightExpressions();

      virtual void SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify = false);

    protected:
      base::DetailFormat getDetailFormat();

      virtual void setFormatter() = 0;
      void setDetailFormatter(Formatter * formatter);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::recursive_mutex dataLock;

      base::DetailFormat detailFormat;
      std::unique_ptr<Formatter> formatter;

    };
  }
}
#endif