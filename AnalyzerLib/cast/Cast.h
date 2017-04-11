#ifndef CAST_H
#define CAST_H

#include <string>
#include <memory>
#include <vector>

namespace analyzer {
  namespace cast {
    class Cast
    {
    public:
      virtual ~Cast();
      virtual std::string AsIntegerExpression() { return ""; }
      virtual std::string AsDoubleExpression() { return ""; }
      virtual std::string AsWCharTExpression() { return ""; }
      virtual std::string AsOpcodeExpression() { return ""; }

      size_t GetDataSize();
      void ResetData(const std::shared_ptr<std::vector<unsigned char>> & data);

    protected:
      explicit Cast(const std::shared_ptr<std::vector<unsigned char>> & data);
      const std::shared_ptr<std::vector<unsigned char>> & getData() const;

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
    };
  }
}
#endif