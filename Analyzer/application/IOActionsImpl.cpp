#include "IOActionsImpl.h"

#include "error\AppException.h"

#include <fstream>

namespace analyzer{
  namespace app{

      IOActionsImpl::IOActionsImpl()
      {

      }
      
      IOActionsImpl::~IOActionsImpl()
      {

      }

      void IOActionsImpl::ReadFile(const std::string & path)
      {
        std::ifstream file(path.c_str(), std::ios::binary | std::ios::in);
        if (file.bad() || !file.is_open()){
          throw AppException("Cannot open " + path);
        }
      }
    
  }
}