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
  }
}