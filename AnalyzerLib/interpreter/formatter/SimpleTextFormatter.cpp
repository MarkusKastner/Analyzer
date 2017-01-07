#include "SimpleTextFormatter.h"

#include <locale>
#include <codecvt>
#include <string>

namespace analyzer{
  namespace interpreter{

    SimpleTextFormatter::SimpleTextFormatter()
      :Formatter()
    {

    }

    SimpleTextFormatter::~SimpleTextFormatter()
    {
    }

    std::wstring SimpleTextFormatter::GetText()
    {
      std::string asString;
      auto& data = (*this->getData());
      for (auto& byte : data){
        asString.push_back(static_cast<char>(byte->GetValue()));
      }
      std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
      std::wstring text(converter.from_bytes(asString));
      return text;
    }
  }
}

/*



std::string narrow = converter.to_bytes(wide_utf16_source_string);
std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
*/