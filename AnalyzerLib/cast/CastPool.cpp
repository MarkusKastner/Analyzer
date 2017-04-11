#include "CastPool.h"

#include "Cast.h"
#include "CastFactory.h"

namespace analyzer{
  namespace cast{
    CastPool::CastPool()
      :casts()
    {
    }

    CastPool::~CastPool()
    {
    }

    std::shared_ptr<Cast> CastPool::GetCaster(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      if (CastPool::instance == nullptr) {
        CastPool::instance = new CastPool();
      }
      return CastPool::instance->findOrCreateCast(data);
    }

    std::shared_ptr<Cast> CastPool::findOrCreateCast(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      for (auto& cast : this->casts) {
        if (cast->GetDataSize() == data->size()) {
          return cast;
        }
      }
      auto cast = CastFactory::CreateCast(data);
      this->casts.push_back(cast);
      return cast;
    }

    CastPool * CastPool::instance = nullptr;
  }
}
