#ifndef HEADING_H
#define HEADING_H

#include <string>

#include "BodyElement.h"

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      class Heading : public BodyElement
      {
      public:
        Heading(const std::string & text, const unsigned int & level)
          : BodyElement(), text(text), level(level)
        {}
        virtual ~Heading() {}

        virtual std::string ToString() {
          return std::string("<h" + std::to_string(this->level) + ">" + this->text + "</h" + std::to_string(this->level) + ">");
        }

      private:
        std::string text;
        unsigned int level;
      };
    }
  }
}
#endif