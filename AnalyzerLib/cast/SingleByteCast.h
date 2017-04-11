#ifndef SINGLEBYTECAST_H
#define SINGLEBYTECAST_H

#include "Cast.h"

#include <string>
#include <memory>
#include <vector>

namespace analyzer {
  namespace cast {
    class SingleByteCast : public Cast
    {
    public:
      explicit SingleByteCast(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~SingleByteCast();
      virtual std::string AsIntegerExpression();
      virtual std::string AsOpcodeExpression();
    };
  }
}
#endif