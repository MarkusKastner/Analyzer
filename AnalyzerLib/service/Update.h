#ifndef UPDATE_H
#define UPDATE_H

#include <string>

namespace analyzer{
  namespace service{
    class Update
    {
    public:
      Update();
      ~Update();

      bool Connect(const std::string & url, const unsigned int & port);
    };
  }
}
#endif