/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "InterpreterDataImpl.h"

#include "error\InterpreterException.h"

namespace analyzer{
  namespace interpreter{
    InterpreterDataImpl::InterpreterDataImpl()
      :InterpreterObserverImpl(), data(new std::vector<unsigned char>()),
      dataLock(), detailFormat(base::DetailFormat::unknown), formatter()
    {
    }

    InterpreterDataImpl::InterpreterDataImpl(const std::shared_ptr<std::vector<unsigned char>> & data)
      : InterpreterObserverImpl(), data(data),
      dataLock(), detailFormat(base::DetailFormat::unknown), formatter()
    {
    }

    InterpreterDataImpl::~InterpreterDataImpl()
    {
    }

    bool InterpreterDataImpl::HasData()
    {
      std::lock_guard<std::recursive_mutex> lock(this->dataLock);
      if (!(this->data)){
        return false;
      }
      if ((this->data)->size() == 0){
        return false;
      }
      else{
        return true;
      }
    }

    void InterpreterDataImpl::ResetData(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      { std::lock_guard<std::recursive_mutex> lock(this->dataLock);
      this->data = data;
      this->formatter->SetData(this->data);
      }
    }

    std::shared_ptr<std::vector<unsigned char>> InterpreterDataImpl::GetData()
    {
      std::lock_guard<std::recursive_mutex> lock(this->dataLock);
      return this->data;
    }

    std::shared_ptr<std::wstring> InterpreterDataImpl::GetText()
    {
      return this->formatter->GetText();
    }

    std::vector<std::wstring> InterpreterDataImpl::GetFunctionalHighlightExpressions()
    {
      return this->formatter->GetFunctionalHighlightingExp();
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

    base::DetailFormat InterpreterDataImpl::getDetailFormat()
    {
      return this->detailFormat;
    }

    void InterpreterDataImpl::setDetailFormatter(Formatter * formatter)
    {
      this->formatter.reset(formatter);
      this->formatter->SetData(this->data);
    }
  }
}