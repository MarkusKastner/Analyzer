#include "Formatter.h"

namespace analyzer{
  namespace interpreter{
    Formatter::~Formatter()
    {
      delete this->data;
      delete this->functionalHighlightExpressions;
    }

    Formatter::Formatter()
      : data(new std::shared_ptr<analyzer::core::ByteCollection>()), 
      functionalHighlightExpressions(new std::vector<std::wstring>)
    {

    }

    void Formatter::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->data = data;
    }

    void Formatter::SetHighlightingExpressions()
    {
    }

    void Formatter::AddFunctionalHighlightingExp(const std::wstring & expression)
    {
      this->functionalHighlightExpressions->push_back(expression);
    }

    const std::vector<std::wstring> & Formatter::GetFunctionalHighlightingExp()
    {
      return *this->functionalHighlightExpressions;
    }

    const std::shared_ptr<analyzer::core::ByteCollection> & Formatter::getData()
    {
      return *this->data;
    }
  }
}