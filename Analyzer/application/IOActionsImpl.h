#include "IOActions.h"

#include <string>
#include <vector>

#include "IOActionObserver.h"

namespace analyzer{
  namespace app{
    class IOActionsImpl : public IOActions
    {
    public:
      IOActionsImpl();
      virtual ~IOActionsImpl();

      virtual void RegisterObserver(IOActionObserver * observer);
      virtual void UnregisterObserver(IOActionObserver * observer);

      virtual void ReadFile(const std::string & path);
      virtual const std::vector<char> & GetData();

    private:
      std::vector<char> currentData;
      std::vector<IOActionObserver*> actionObserver;

      void notifyNewData();
    };
  }
}