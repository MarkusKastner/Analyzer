/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CHECKOBSERVER_H
#define CHECKOBSERVER_H

namespace analyzer {
  namespace checker {
    class CheckObserver
    {
    public:
      virtual void NotifyCheckRunFinished() = 0;
      virtual void NotifyCurrentIndex(const size_t & checkIndex) = 0;
      virtual void NotifyMarkedIndex(const size_t & markedIndex, const analyzer::base::AnalyzerRGB & color) = 0;
    };
  }
}
#endif