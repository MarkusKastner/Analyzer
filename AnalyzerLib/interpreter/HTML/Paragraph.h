#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <string>

#include "BodyElement.h"

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      class Paragraph : public BodyElement
      {
      public:
        Paragraph(const std::string & text) 
          : BodyElement(), text(text)
        {}
        virtual ~Paragraph() {}

        virtual std::string ToString() {
          return std::string("<p>" + this->text + "</p>");
        }
      private:
        std::string text;
      };
    }
  }
}
#endif