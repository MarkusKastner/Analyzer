/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "MacroChecker.h"

namespace analyzer {
  namespace checker {
    MacroChecker::MacroChecker()
      :ContentChecker(), lastFoundSyntaxOffset(0), jsChecker()
    {
    }

    MacroChecker::~MacroChecker()
    {
    }

    void MacroChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      ContentChecker::SetData(data);
      this->jsChecker.SetData(data);
    }

    void MacroChecker::ReleaseData()
    {
      ContentChecker::ReleaseData();
      this->jsChecker.ReleaseData();
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
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
        return this->IsECaseSyntax(offset);
      case 'f':
        return this->IsFCaseSyntax(offset);
      case 'g':
        return this->IsGCaseSyntax(offset);
      case 'i':
        return this->IsICaseSyntax(offset);
      case 'l':
        return this->IsLCaseSyntax(offset);
      case 'n':
        return this->IsNCaseSyntax(offset);
      case 'p':
        return this->IsPCaseSyntax(offset);
      case 'r':
        return this->IsRCaseSyntax(offset);
      case 's':
        return this->IsSCaseSyntax(offset);
      case 't':
        return this->IsTCaseSyntax(offset);
      case 'v':
        return this->IsVCaseSyntax(offset);
      case 'w':
        return this->IsWCaseSyntax(offset);
      case 'y':
        return this->IsYCaseSyntax(offset);
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
      if (this->jsChecker.IsICaseSyntax(offset)) {
        this->lastFoundSyntaxOffset = this->jsChecker.GetLastFoundSyntaxOffset();;
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_instanceof.size()).compare(MacroChecker::KeyWord_instanceof) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_instanceof.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_interface.size()).compare(MacroChecker::KeyWord_interface) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_interface.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_int.size()).compare(MacroChecker::KeyWord_int) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_int.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_in.size()).compare(MacroChecker::KeyWord_in) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_in.size();
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

    bool MacroChecker::IsECaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_else.size()).compare(MacroChecker::KeyWord_else) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_else.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_enum.size()).compare(MacroChecker::KeyWord_enum) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_enum.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_eval.size()).compare(MacroChecker::KeyWord_eval) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_eval.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_export.size()).compare(MacroChecker::KeyWord_export) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_export.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_extends.size()).compare(MacroChecker::KeyWord_extends) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_extends.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsFCaseSyntax(const size_t & offset)
    {
      if (this->jsChecker.IsFCaseSyntax(offset)) {
        this->lastFoundSyntaxOffset = this->jsChecker.GetLastFoundSyntaxOffset();;
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_false.size()).compare(MacroChecker::KeyWord_false) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_false.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_finally.size()).compare(MacroChecker::KeyWord_finally) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_finally.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_final.size()).compare(MacroChecker::KeyWord_final) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_final.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_float.size()).compare(MacroChecker::KeyWord_float) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_float.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_function.size()).compare(MacroChecker::KeyWord_function) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_function.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsGCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_goto.size()).compare(MacroChecker::KeyWord_goto) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_goto.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsLCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_let.size()).compare(MacroChecker::KeyWord_let) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_let.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_long.size()).compare(MacroChecker::KeyWord_long) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_long.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsNCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_native.size()).compare(MacroChecker::KeyWord_native) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_native.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_new.size()).compare(MacroChecker::KeyWord_new) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_new.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_null.size()).compare(MacroChecker::KeyWord_null) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_null.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsPCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_package.size()).compare(MacroChecker::KeyWord_package) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_package.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_private.size()).compare(MacroChecker::KeyWord_private) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_private.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_protected.size()).compare(MacroChecker::KeyWord_protected) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_protected.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_public.size()).compare(MacroChecker::KeyWord_public) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_public.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsRCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_return.size()).compare(MacroChecker::KeyWord_return) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_return.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsSCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_short.size()).compare(MacroChecker::KeyWord_short) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_short.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_static.size()).compare(MacroChecker::KeyWord_static) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_static.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_super.size()).compare(MacroChecker::KeyWord_super) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_super.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_switch.size()).compare(MacroChecker::KeyWord_switch) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_switch.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_synchronized.size()).compare(MacroChecker::KeyWord_synchronized) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_synchronized.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsTCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_this.size()).compare(MacroChecker::KeyWord_this) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_this.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_throws.size()).compare(MacroChecker::KeyWord_throws) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_throws.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_throw.size()).compare(MacroChecker::KeyWord_throw) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_throw.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_transient.size()).compare(MacroChecker::KeyWord_transient) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_transient.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_true.size()).compare(MacroChecker::KeyWord_true) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_true.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_try.size()).compare(MacroChecker::KeyWord_try) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_try.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_typeof.size()).compare(MacroChecker::KeyWord_typeof) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_typeof.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsVCaseSyntax(const size_t & offset)
    {
      if (this->jsChecker.IsVCaseSyntax(offset)) {
        this->lastFoundSyntaxOffset = this->jsChecker.GetLastFoundSyntaxOffset();;
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_void.size()).compare(MacroChecker::KeyWord_void) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_void.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_volatile.size()).compare(MacroChecker::KeyWord_volatile) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_volatile.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsWCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_while.size()).compare(MacroChecker::KeyWord_while) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_while.size();
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_with.size()).compare(MacroChecker::KeyWord_with) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_with.size();
        return true;
      }
      return false;
    }

    bool MacroChecker::IsYCaseSyntax(const size_t & offset)
    {
      if (this->RangeToString(offset, MacroChecker::KeyWord_yield.size()).compare(MacroChecker::KeyWord_yield) == 0) {
        this->lastFoundSyntaxOffset = MacroChecker::KeyWord_yield.size();
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
    const std::string MacroChecker::KeyWord_function = "function";

    const std::string MacroChecker::KeyWord_goto = "goto";

    const std::string MacroChecker::KeyWord_in = "in";
    const std::string MacroChecker::KeyWord_instanceof = "instanceof";
    const std::string MacroChecker::KeyWord_int = "int";
    const std::string MacroChecker::KeyWord_interface = "interface";

    const std::string MacroChecker::KeyWord_let = "let";
    const std::string MacroChecker::KeyWord_long = "long";

    const std::string MacroChecker::KeyWord_native = "native";
    const std::string MacroChecker::KeyWord_new = "new";
    const std::string MacroChecker::KeyWord_null = "null";

    const std::string MacroChecker::KeyWord_package = "package";
    const std::string MacroChecker::KeyWord_private = "private";
    const std::string MacroChecker::KeyWord_protected = "protected";
    const std::string MacroChecker::KeyWord_public = "public";

    const std::string MacroChecker::KeyWord_return = "return";

    const std::string MacroChecker::KeyWord_short = "short";
    const std::string MacroChecker::KeyWord_static = "static";
    const std::string MacroChecker::KeyWord_super = "super";
    const std::string MacroChecker::KeyWord_switch = "switch";
    const std::string MacroChecker::KeyWord_synchronized = "synchronized";

    const std::string MacroChecker::KeyWord_this = "this";
    const std::string MacroChecker::KeyWord_throw = "throw";
    const std::string MacroChecker::KeyWord_throws = "throws";
    const std::string MacroChecker::KeyWord_transient = "transient";
    const std::string MacroChecker::KeyWord_true = "true";
    const std::string MacroChecker::KeyWord_try = "try";
    const std::string MacroChecker::KeyWord_typeof = "typeof";

    const std::string MacroChecker::KeyWord_void = "void";
    const std::string MacroChecker::KeyWord_volatile = "volatile";

    const std::string MacroChecker::KeyWord_while = "while";
    const std::string MacroChecker::KeyWord_with = "with";

    const std::string MacroChecker::KeyWord_yield = "yield";
  }
}