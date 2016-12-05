#include <string>

#include <vector>

namespace analyzer{
  namespace app{
    class IOActionObserver;
    class IOActions
    {
    public:
      virtual void RegisterObserver(IOActionObserver * observer) = 0;
      virtual void UnregisterObserver(IOActionObserver * observer) = 0;

      virtual void ReadFile(const std::string & path) = 0;
      virtual const std::vector<char> & GetData() = 0;
    };
  }
}