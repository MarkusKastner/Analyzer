#include "IOActions.h"

#include <string>
#include <vector>

namespace analyzer{
  namespace app{
    class IOActionsImpl : public IOActions
    {
    public:
      IOActionsImpl();
      virtual ~IOActionsImpl();

      virtual void ReadFile(const std::string & path);
      virtual const std::vector<char> & GetData();

    private:
      std::vector<char> currentData;
    };
  }
}