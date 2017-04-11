#include "CastFactory.h"

#include "Cast.h"
#include "EmptyCast.h"
#include "SingleByteCast.h"

namespace analyzer {
  namespace cast {
    CastFactory::CastFactory()
    {
    }

    CastFactory::~CastFactory()
    {
    }

    std::shared_ptr<Cast> CastFactory::CreateCast(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      if (CastFactory::instance == nullptr) {
        CastFactory::instance = new CastFactory();
      }
      return CastFactory::instance->createCast(data);
    }

    std::shared_ptr<Cast> CastFactory::createCast(const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      switch (data->size()) {
      case 1:
        return std::shared_ptr<Cast>(new SingleByteCast(data));
      default:
        return std::shared_ptr<Cast>(new EmptyCast());
      }
    }

    CastFactory * CastFactory::instance = nullptr;
  }
}