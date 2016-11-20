#include "IOActions.h"

#include <string>

namespace analyzer{
  namespace app{
    class IOActionsImpl : public IOActions
    {
    public:
      IOActionsImpl();
      virtual ~IOActionsImpl();

      virtual void ReadFile(const std::string & path);
    };
  }
}