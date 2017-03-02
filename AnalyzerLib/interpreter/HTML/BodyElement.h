#ifndef BODYELEMENT_H
#define BODYELEMENT_H

#include <string>

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      class BodyElement
      {
      public:
        virtual std::string ToString() = 0;
      };
    }
  }
}
#endif