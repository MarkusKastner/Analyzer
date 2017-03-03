/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <memory>

#include "BodyElement.h"
#include "Heading.h"
#include "Paragraph.h"
#include "Table.h"

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      
      class Document
      {
      public:
        Document();
        virtual ~Document();

        std::string GetString();
        void SetTitle(const std::string & title);
        void AddHeading(const analyzer::interpreter::HTML::Heading & heading);
        void AddParagraph(const analyzer::interpreter::HTML::Paragraph & paragraph);
        void AddTable(const analyzer::interpreter::HTML::Table & table);
        void AddLineFeed();

      private:
        std::string docString;
        std::string title;
        std::vector<std::shared_ptr<BodyElement>> bodyElements;

        void assemble();

        class LineFeed : public BodyElement
        {
        public:
          LineFeed() {}
          virtual ~LineFeed() {}
          virtual std::string ToString() {
            return "<br>";
          }
        };
      };
    }
  }
}
#endif