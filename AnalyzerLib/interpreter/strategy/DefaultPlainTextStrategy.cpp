#include "DefaultPlainTextStrategy.h"

namespace analyzer{
  namespace interpreter{
    namespace strategy{

      DefaultPlainTextStrategy::DefaultPlainTextStrategy()
        : analyzer::interpreter::strategy::InterpretStrategyImpl()
      {
      }

      DefaultPlainTextStrategy::DefaultPlainTextStrategy(const std::vector<std::shared_ptr<analyzer::core::Byte>> & data)
        : analyzer::interpreter::strategy::InterpretStrategyImpl(data)
      {
      }

      DefaultPlainTextStrategy::~DefaultPlainTextStrategy()
      {
      }

      std::string DefaultPlainTextStrategy::GetPlainText()
      {
        std::string text;
        for (auto& byte : this->currentData()){
          text += std::to_string(byte->GetValue());
        }
        return text;
      }
    }
  }
}