/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InterpreterDataImpl.h"

#include "error\InterpreterException.h"
#include "AnalyzerLib\interpreter\formatter\Formatter.h"

namespace analyzer{
  namespace interpreter{
    InterpreterDataImpl::InterpreterDataImpl()
      :InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(new analyzer::core::ByteCollection())), 
      dataLock(new std::recursive_mutex()), detailFormat(base::DetailFormat::unknown), formatter(new std::unique_ptr<Formatter>())
    {
    }

    InterpreterDataImpl::InterpreterDataImpl(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : InterpreterObserverImpl(), byteCollection(new std::shared_ptr<analyzer::core::ByteCollection>(byteCollection)), 
      dataLock(new std::recursive_mutex()), detailFormat(base::DetailFormat::unknown), formatter(new std::unique_ptr<Formatter>())
    {
    }

    InterpreterDataImpl::~InterpreterDataImpl()
    {
      delete this->byteCollection;
      delete this->dataLock;
      delete this->formatter;
    }

    bool InterpreterDataImpl::HasData()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      if (!(*this->byteCollection)){
        return false;
      }
      if ((*this->byteCollection)->GetSize() == 0){
        return false;
      }
      else{
        return true;
      }
    }

    void InterpreterDataImpl::ResetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      { std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      *this->byteCollection = data;
      }
    }

    void InterpreterDataImpl::ResetData(const std::vector<char> & data)
    {
      { std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      this->byteCollection->reset(new core::ByteCollection(data));
      }
    }

    std::shared_ptr<analyzer::core::ByteCollection> InterpreterDataImpl::GetData()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      return *this->byteCollection;
    }

    std::shared_ptr<std::wstring> InterpreterDataImpl::GetText()
    {
      return this->formatter->get()->GetText();
    }

    std::vector<std::wstring> InterpreterDataImpl::GetFunctionalHighlightExpressions()
    {
      return this->formatter->get()->GetFunctionalHighlightingExp();
    }

    void InterpreterDataImpl::SetDetailFormat(const base::DetailFormat & detailFormat, bool forceNotify)
    {
      if (this->detailFormat != detailFormat){
        this->detailFormat = detailFormat;
        this->setFormatter();
        this->NotifyTextChange();
      }
      else{
        if (forceNotify){
          this->NotifyTextChange();
        }
      }
    }

    std::shared_ptr<analyzer::core::ByteCollection> * InterpreterDataImpl::getByteCollection()
    {
      std::lock_guard<std::recursive_mutex> lock(*this->dataLock);
      return this->byteCollection;
    }

    base::DetailFormat InterpreterDataImpl::getDetailFormat()
    {
      return this->detailFormat;
    }

    void InterpreterDataImpl::setDetailFormatter(Formatter * formatter)
    {
      this->formatter->reset(formatter);
      this->formatter->get()->SetData(*this->byteCollection);
    }
  }
}