/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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