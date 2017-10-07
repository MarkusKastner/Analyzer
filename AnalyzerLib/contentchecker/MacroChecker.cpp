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

        if (MacroChecker::isSyntax(currentIndex)) {
          this->SetSearchPos(currentIndex + this->lastFoundSyntaxOffset);
          return currentIndex;
        }
        currentIndex = this->StepUpSearchPos();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      return 0;
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

    bool MacroChecker::isSyntax(const size_t & offset)
    {
      switch (this->getData()->at(offset)) {
      case 'a':
        return false;
      case 'b':
        return false;
      case 'c':
        return false;
      case 'd':
        return false;
      case 'e':
        return false;
      case 'f':
        return false;
      case 'g':
        return false;
      case 'i':
        return this->isICaseSyntax(offset);
      default:
        return false;
      }
    }

    bool MacroChecker::isICaseSyntax(const size_t & offset)
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

    const std::string MacroChecker::KeyWord_if = "if";
    const std::string MacroChecker::KeyWord_implements = "implements";
    const std::string MacroChecker::KeyWord_import = "import";
    const std::string MacroChecker::KeyWord_in = "in";
    const std::string MacroChecker::KeyWord_instanceof = "instanceof";
    const std::string MacroChecker::KeyWord_int = "int";
    const std::string MacroChecker::KeyWord_interface = "interface";
  }
}