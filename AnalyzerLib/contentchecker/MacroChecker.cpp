/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "MacroChecker.h"

namespace analyzer {
  namespace checker {
    MacroChecker::MacroChecker()
    {
    }

    MacroChecker::~MacroChecker()
    {
    }

    size_t MacroChecker::FindNextSyntaxHint()
    {
      size_t checkOffset = this->GetCheckOffest();

      for (size_t i = this->GetStartOffest(); i < checkOffset; ++i) {
        this->notifyClearWorkingMarkings();
        this->notifyMarkedIndex(i);

        if (MacroChecker::isSyntax(i)) {
          return i;
        }
      }
      return 0;
    }

    void MacroChecker::checkData()
    {
      auto data = this->getData();

      for (size_t i = this->GetStartOffest(); i < this->GetCheckOffest(); ++i) {
        if (!this->IsChecking()) {
          return;
        }
        this->notifyClearWorkingMarkings();
        this->notifyMarkedIndex(i);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_implements.size()).compare(MacroChecker::KeyWord_implements) == 0) {
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_import.size()).compare(MacroChecker::KeyWord_import) == 0) {
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_in.size()).compare(MacroChecker::KeyWord_in) == 0) {
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_instanceof.size()).compare(MacroChecker::KeyWord_instanceof) == 0) {
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_int.size()).compare(MacroChecker::KeyWord_int) == 0) {
        return true;
      }
      if (this->RangeToString(offset, MacroChecker::KeyWord_interface.size()).compare(MacroChecker::KeyWord_interface) == 0) {
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