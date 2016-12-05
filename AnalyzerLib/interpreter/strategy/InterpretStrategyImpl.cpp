#include "InterpretStrategyImpl.h"

namespace analyzer{
  namespace interpreter{
    namespace strategy{
      InterpretStrategyImpl::~InterpretStrategyImpl()
      {
        delete this->data;
      }

      std::string InterpretStrategyImpl::GetPlainText()
      {
        return std::string();
      }

      InterpretStrategyImpl::InterpretStrategyImpl()
        : data(new std::vector<std::shared_ptr<analyzer::core::Byte>>())
      {
      }

      InterpretStrategyImpl::InterpretStrategyImpl(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data)
        : data(new std::vector<std::shared_ptr<analyzer::core::Byte>>(data))
      {
      }

      std::vector<std::shared_ptr<analyzer::core::Byte>> & InterpretStrategyImpl::currentData()
      {
        return *this->data;
      }
    }
  }
}