/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "MacroChecker.h"

namespace analyzer {
  namespace checker {
    MacroChecker::MacroChecker()
      :ContentChecker(), lastFoundSyntaxOffset(0)
    {
    }

    MacroChecker::~MacroChecker()
    {
    }

    size_t MacroChecker::FindNextSyntaxHint()
    {
      size_t currentIndex = this->GetSearchPos();
      while(!this->SearchDone()) {
        this->notifyClearWorkingMarkings();
        this->notifyMarkedIndex(currentIndex);

        if (MacroChecker::IsSyntax(currentIndex)) {
          this->SetSearchPos(currentIndex + this->lastFoundSyntaxOffset);
          return currentIndex;
        }
        currentIndex = this->StepUpSearchPos();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      return 0;
    }

    bool MacroChecker::IsSyntax(const size_t & offset)
    {
      switch (this->getData()->at(offset)) {
      case 'a':
        return this->IsACaseSyntax(offset);
      case 'b':
        return this->IsBCaseSyntax(offset);
      case 'c':
        return this->IsCCaseSyntax(offset);
      case 'd':
        return this->IsDCaseSyntax(offset);
      case 'e':
        return false;
      case 'f':
        return false;
      case 'g':
        return false;
      case 'i':
        return this->IsICaseSyntax(offset);
      default:
        return false;
      }
    }

    bool MacroChecker::IsACaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_abstract.size()).compare(MacroChecker::KeyWord_abstract) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_abstract.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_arguments.size()).compare(MacroChecker::KeyWord_arguments) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_arguments.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_await.size()).compare(MacroChecker::KeyWord_await) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_await.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsICaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_if.size()).compare(MacroChecker::KeyWord_if) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_if.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_implements.size()).compare(MacroChecker::KeyWord_implements) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_implements.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_import.size()).compare(MacroChecker::KeyWord_import) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_import.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_in.size()).compare(MacroChecker::KeyWord_in) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_in.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_instanceof.size()).compare(MacroChecker::KeyWord_instanceof) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_instanceof.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_int.size()).compare(MacroChecker::KeyWord_int) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_int.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_interface.size()).compare(MacroChecker::KeyWord_interface) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_interface.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsBCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_boolean.size()).compare(MacroChecker::KeyWord_boolean) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_boolean.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_break.size()).compare(MacroChecker::KeyWord_break) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_break.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_byte.size()).compare(MacroChecker::KeyWord_byte) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_byte.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsCCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_case.size()).compare(MacroChecker::KeyWord_case) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_case.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_catch.size()).compare(MacroChecker::KeyWord_catch) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_catch.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_char.size()).compare(MacroChecker::KeyWord_char) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_char.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_class.size()).compare(MacroChecker::KeyWord_class) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_class.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_const.size()).compare(MacroChecker::KeyWord_const) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_const.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_continue.size()).compare(MacroChecker::KeyWord_continue) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_continue.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsDCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_debugger.size()).compare(MacroChecker::KeyWord_debugger) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_debugger.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_default.size()).compare(MacroChecker::KeyWord_default) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_default.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_delete.size()).compare(MacroChecker::KeyWord_delete) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_delete.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_double.size()).compare(MacroChecker::KeyWord_double) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_double.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_do.size()).compare(MacroChecker::KeyWord_do) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_do.size();
        return true;
      }
      return false;
    }

    const size_t & MacroChecker::GetLastFoundSyntaxOffset() const
    {
      return this->lastFoundSyntaxOffset;
    }

    void MacroChecker::checkData()
    {
      while (!this->SearchDone()) {
        if (!this->IsChecking()) {
          return;
        }
        size_t syntaxOffset = this->FindNextSyntaxHint();
        if (this->lastFoundSyntaxOffset > 0) {
          this->notifySuspectRange(syntaxOffset, this->lastFoundSyntaxOffset);
          this->lastFoundSyntaxOffset = 0;
        }
      }
    }

    const std::string MacroChecker::KeyWord_abstract = "abstract";
    const std::string MacroChecker::KeyWord_arguments = "arguments";
    const std::string MacroChecker::KeyWord_await = "await";

    const std::string MacroChecker::KeyWord_boolean = "boolean";
    const std::string MacroChecker::KeyWord_break = "break";
    const std::string MacroChecker::KeyWord_byte = "byte";

    const std::string MacroChecker::KeyWord_case = "case";
    const std::string MacroChecker::KeyWord_catch = "catch";
    const std::string MacroChecker::KeyWord_char = "char";
    const std::string MacroChecker::KeyWord_class = "class";
    const std::string MacroChecker::KeyWord_const = "const";
    const std::string MacroChecker::KeyWord_continue = "continue";

    const std::string MacroChecker::KeyWord_debugger = "debugger";
    const std::string MacroChecker::KeyWord_default = "default";
    const std::string MacroChecker::KeyWord_delete = "delete";
    const std::string MacroChecker::KeyWord_do = "do";
    const std::string MacroChecker::KeyWord_double = "double";

    const std::string MacroChecker::KeyWord_else = "else";
    const std::string MacroChecker::KeyWord_enum = "enum";
    const std::string MacroChecker::KeyWord_eval = "eval";
    const std::string MacroChecker::KeyWord_export = "export";
    const std::string MacroChecker::KeyWord_extends = "extends";

    const std::string MacroChecker::KeyWord_false = "false";
    const std::string MacroChecker::KeyWord_final = "final";
    const std::string MacroChecker::KeyWord_finally = "finally";
    const std::string MacroChecker::KeyWord_float = "float";
    const std::string MacroChecker::KeyWord_for = "for";
    const std::string MacroChecker::KeyWord_function = "function";

    const std::string MacroChecker::KeyWord_goto = "goto";

    const std::string MacroChecker::KeyWord_if = "if";
    const std::string MacroChecker::KeyWord_implements = "implements";
    const std::string MacroChecker::KeyWord_import = "import";
    const std::string MacroChecker::KeyWord_in = "in";
    const std::string MacroChecker::KeyWord_instanceof = "instanceof";
    const std::string MacroChecker::KeyWord_int = "int";
    const std::string MacroChecker::KeyWord_interface = "interface";
  }
}