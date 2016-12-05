#include "ByteCollection.h"

#include "error\CoreException.h"

namespace analyzer{
  namespace core{

    ByteCollection::ByteCollection()
      :data(new std::vector<std::shared_ptr<Byte>>())
    {

    }

    ByteCollection::ByteCollection(const char *  data, const size_t & size)
      : data(new std::vector<std::shared_ptr<Byte>>())
    {
      for (size_t i = 0; i < size; i++){
        this->data->push_back(std::shared_ptr<Byte>(new Byte(data[i])));
      }
    }

    ByteCollection::ByteCollection(const std::vector<char> data)
      : data(new std::vector<std::shared_ptr<Byte>>())
    {
      for (auto& byte : data){
        this->data->push_back(std::shared_ptr<Byte>(new Byte(byte)));
      }
    }

    ByteCollection::~ByteCollection()
    {
      delete this->data;
    }

    size_t ByteCollection::GetSize() const
    {
      return data->size();
    }

    const std::shared_ptr<Byte> & ByteCollection::GetByteAt(const size_t & index)
    {
      if (index > this->data->size() - 1){
        throw CoreException("Byte index out of range");
      }
      return this->data->at(index);
    }

    std::vector<std::shared_ptr<Byte>>::iterator ByteCollection::begin()
    {
      return this->data->begin();
    }

    std::vector<std::shared_ptr<Byte>>::iterator ByteCollection::end()
    {
      return this->data->end();
    }
  }
}
