#include "Cast.h"

namespace analyzer {
  namespace cast {
    Cast::Cast(const std::shared_ptr<std::vector<unsigned char>> & data)
      :data(data)
    {
    }

    const std::shared_ptr<std::vector<unsigned char>>& Cast::getData() const
    {
      return this->data;
    }

    Cast::~Cast()
    {
    }

    size_t Cast::GetDataSize()
    {
      if (this->data) {
        return this->data->size();
      }
      else {
        return 0;
      }
    }

    void Cast::ResetData(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      if (this->data->size() != data->size()) {
        throw std::exception("Invalid data size for this cast");
      }
      this->data = data;
    }
  }
}