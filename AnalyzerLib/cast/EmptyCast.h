#ifndef EMPTYCAST_H
#define EMPTYCAST_H

#include "Cast.h"

#include <string>
#include <memory>
#include <vector>

namespace analyzer {
  namespace cast {
    class EmptyCast : public Cast
    {
    public:
      explicit EmptyCast() : Cast(std::shared_ptr<std::vector<unsigned char>>()) {}
      virtual ~EmptyCast() {}

      size_t GetByteSize() { return 0; }
    };
  }
}
#endif