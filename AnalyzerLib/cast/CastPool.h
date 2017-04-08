#ifndef CASTPOOL_H
#define CASTPOOL_H

#include <vector>
#include <memory>

namespace analyzer {
  namespace cast {
    class Cast;
    class CastPool
    {
    private:
      CastPool();
      CastPool(const CastPool &) {}
      CastPool & operator=(const CastPool &) { return *this; }

    public:
      virtual ~CastPool();
      
      static std::shared_ptr<Cast> GetCaster(const std::vector<unsigned char> & data);

    private:
      static CastPool * instance;
      std::vector<std::shared_ptr<Cast>> casts;

      std::shared_ptr<Cast> findOrCreateCast(const std::vector<unsigned char> & data);
    };
  }
}
#endif