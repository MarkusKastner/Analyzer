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

      private:
        std::string docString;
        std::string title;
        std::vector<std::shared_ptr<BodyElement>> bodyElements;

        void assemble();
      };
    }
  }
}
#endif