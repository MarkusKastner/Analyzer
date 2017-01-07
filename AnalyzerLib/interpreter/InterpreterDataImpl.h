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

      virtual void SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify = false);

    protected:
      std::shared_ptr<analyzer::core::ByteCollection> * getByteCollection();

      base::DetailFormat getDetailFormat();

    private:
      std::shared_ptr<analyzer::core::ByteCollection> * byteCollection;

      std::recursive_mutex * dataLock;

      base::DetailFormat detailFormat;
    };
  }
}
#endif