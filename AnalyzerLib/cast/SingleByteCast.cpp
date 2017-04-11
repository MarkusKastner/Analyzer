#include "SingleByteCast.h"

namespace analyzer {
  namespace cast {
    SingleByteCast::SingleByteCast(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Cast(data)
    {
    }

    SingleByteCast::~SingleByteCast()
    {
    }

    std::string SingleByteCast::AsIntegerExpression()
    {
      return std::to_string(static_cast<int>(this->getData().get()->at(0)));
    }

    std::string SingleByteCast::AsOpcodeExpression()
    {
      return std::string();
    }
  }
}
