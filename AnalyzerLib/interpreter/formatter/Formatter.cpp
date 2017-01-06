#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    Formatter::~Formatter()
    {
      delete this->data;
    }

    Formatter::Formatter()
      : data(new std::shared_ptr<analyzer::core::ByteCollection>())
    {

    }

    void Formatter::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->data = data;
    }

    const std::shared_ptr<analyzer::core::ByteCollection> & Formatter::getData()
    {
      return *this->data;
    }
  }
}