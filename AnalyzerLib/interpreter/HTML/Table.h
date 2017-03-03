#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>

#include "BodyElement.h"

namespace analyzer {
  namespace interpreter {
    namespace HTML {
      class Table : public BodyElement
      {
      public:
        Table(const int & border = 1, const int & cellpadding = 1, const int & cellspacing = 1)
          : BodyElement(), header(), lines(), text(), border(border), cellpadding(cellpadding), cellspacing(1), 
          emptyField("&nbsp;")
        {}
        virtual ~Table() {}

        void SetHeader(const std::vector<std::string> & header) {
          this->header = header;
        }

        void AddLine(const std::vector<std::string> & line) {
          this->lines.push_back(line);
        }

        virtual std::string ToString() {
          this->text.clear();
          this->text += this->createTableString();
          this->text += this->createHeaderString();
          this->text += this->createBodyString();
          this->text += "</table>";
          return this->text;
        }

      private:
        std::vector<std::string> header;
        std::vector<std::vector<std::string>> lines;
        std::string text;
        int border;
        int cellpadding;
        int cellspacing;
        std::string emptyField;
        

        std::string createTableString() {
          std::string tabStr("<table border=\"");
          tabStr += std::to_string(this->border);
          tabStr += "\" cellpadding=\"";
          tabStr += std::to_string(this->cellpadding);
          tabStr += "\" cellspacing=\"";
          tabStr += std::to_string(this->cellspacing);
          tabStr += "\" style=\"width: 500px\">";
          return tabStr;
        }

        std::string createHeaderString() {
          std::string headerStr("<thead><tr>");
          for (auto& entry : this->header) {
            headerStr += "<th scope=\"col\">";
            headerStr += this->createFieldText(entry);
            headerStr += "</th>";
          }
          headerStr += "</tr></thead>";
          return headerStr;
        }

        std::string createBodyString() {
          std::string bodyStr("<tbody>");
          for (auto& line : this->lines) {
            bodyStr += "<tr>";
            bodyStr += this->createLineString(line);
            bodyStr += "</tr>";
          }
          bodyStr += "</tbody>";
          return bodyStr;
        }

        std::string createLineString(const std::vector<std::string> & line) {
          std::string lineStr;
          for (auto& entry : line) {
            lineStr += "<td>";
            lineStr += this->createFieldText(entry);
            lineStr += "</td>";
          }
          return lineStr;
        }

        std::string createFieldText(const std::string & entry) {
          if (entry.empty()) {
            return emptyField;
          }
          else {
            return entry;
          }
        }
      };
    }
  }
}
#endif