#ifndef XMLFORMATTER_H
#define XMLFORMATTER_H

#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    class XMLFormatter : public Formatter
    {
    public:

      class XMLToken{
      public:
        enum Type { Open, Close, Inline, Comment, Value };
        XMLToken(const std::wstring & text, const Type & tokenType)
          :text(new std::wstring(text)), tokenType(tokenType)
        {}
        XMLToken(const XMLToken & other)
          :text(new std::wstring(*other.text)), tokenType(other.tokenType)
        {}

        ~XMLToken(){
          delete this->text;
        }

        Type GetTokenType() { return this->tokenType; }
        const std::wstring & GetText() { return *this->text; }

      private:
        std::wstring * text;
        Type tokenType;
      };

      XMLFormatter();
      virtual ~XMLFormatter();

      virtual std::wstring GetText();
      std::vector<XMLToken> GetXMLToken();
      XMLToken CreateToken(const std::wstring & token);

    private:
      std::wstring getDataAsWString();
      
      bool isOpenToken(const std::wstring & text);
      bool isClosingToken(const std::wstring & text);

    };
  }
}

#endif