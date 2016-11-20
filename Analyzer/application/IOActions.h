#include <string>

namespace analyzer{
  namespace app{
    class IOActions
    {
    public:
      virtual void ReadFile(const std::string & path) = 0;
    };
  }
}