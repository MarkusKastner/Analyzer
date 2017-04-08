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

      size_t GetByteSize();
      void ResetData(const std::shared_ptr<std::vector<unsigned char>> & data);

    protected:
      explicit Cast(const std::shared_ptr<std::vector<unsigned char>> & data);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
    };
  }
}
#endif