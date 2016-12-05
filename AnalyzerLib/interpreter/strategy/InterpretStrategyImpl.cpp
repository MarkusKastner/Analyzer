#include "InterpretStrategyImpl.h"

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      InterpretStrategyImpl::~InterpretStrategyImpl()
      {
      }

      std::string InterpretStrategyImpl::GetPlainText()
      {
        return std::string();
      }

      InterpretStrategyImpl::InterpretStrategyImpl()
        : data()
      {
      }

      InterpretStrategyImpl::InterpretStrategyImpl(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data)
        : data(data)
      {
      }

      std::vector<std::shared_ptr<analyzer::core::Byte>> & InterpretStrategyImpl::currentData()
      {
        return this->data;
      }
    }
  }
}