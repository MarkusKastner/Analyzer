#include "IOActionsImpl.h"

#include "error\AppException.h"

#include <fstream>

namespace analyzer{
  namespace app{

    IOActionsImpl::IOActionsImpl()
     : currentData(), actionObserver()
    {

    }
      
    IOActionsImpl::~IOActionsImpl()
    {

    }

    void IOActionsImpl::RegisterObserver(IOActionObserver * observer)
    {
      for (auto it = this->actionObserver.begin(); it != this->actionObserver.end(); ++it){
        if ((*it) == observer){
          return;
        }
      }
      this->actionObserver.push_back(observer);
    }

    void IOActionsImpl::UnregisterObserver(IOActionObserver * observer)
    {
      for (auto it = this->actionObserver.begin(); it != this->actionObserver.end(); ++it){
        if ((*it) == observer){
          this->actionObserver.erase(it);
          return;
        }
      }
    }

    void IOActionsImpl::ReadFile(const std::string & path)
    {
      std::ifstream file(path.c_str(), std::ios::binary);
      if (file.bad() || !file.is_open()){
        throw AppException("Cannot open " + path);
      }

      this->currentData.clear();
      
      long fileSize = 0;
      file.seekg(0, std::ios::end);
      fileSize = file.tellg();
      file.seekg(0, std::ios::beg);

      this->currentData.reserve(fileSize);
      this->currentData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
      this->notifyNewData();
    }

    const std::vector<char> & IOActionsImpl::GetData()
    {
      return this->currentData;
    }

    void IOActionsImpl::notifyNewData()
    {
      for (auto it = this->actionObserver.begin(); it != this->actionObserver.end(); ++it){
        (*it)->NotifyDataLoad();
      }
    }
  }
}