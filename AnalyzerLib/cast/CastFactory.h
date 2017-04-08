#ifndef CASTFACTORY_H
#define CASTFACTORY_H

#include <vector>
#include <memory>

namespace analyzer {
  namespace cast {
    class Cast;
    class CastFactory
    {
    private:
      CastFactory();
      CastFactory(const CastFactory &) {}
      CastFactory & operator=(const CastFactory &) { return *this; }

    public:
      virtual ~CastFactory();

      static std::shared_ptr<Cast> CreateCast(const std::vector<unsigned char> & data);

    private:
      static CastFactory * instance;

      std::shared_ptr<Cast> createCast(const std::vector<unsigned char> & data);

    };
  }
}
#endif