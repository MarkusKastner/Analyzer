#include <string>

#include <vector>

namespace analyzer{
  namespace app{
    class IOActions
    {
    public:
      virtual void ReadFile(const std::string & path) = 0;
      virtual const std::vector<char> & GetData() = 0;
    };
  }
}