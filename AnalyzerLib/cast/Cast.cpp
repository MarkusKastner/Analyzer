#include "Cast.h"

namespace analyzer {
  namespace cast {
    Cast::Cast(const std::shared_ptr<std::vector<unsigned char>> & data)
      :data(data)
    {
    }

    Cast::~Cast()
    {
    }

    size_t Cast::GetByteSize()
    {
      return this->data->size();
    }

    void Cast::ResetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (this->data->size() != data->size()) {
        throw std::exception("Invalid data size for this cast");
      }
      this->data = data;
    }
  }
}