/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERBASEOBSERVER_H
#define ANALYZERBASEOBSERVER_H

namespace analyzer{
  namespace base{
    class AnalyzerBaseObserver
    {
    public:
      virtual void NotifyInterprterChange() = 0;
      virtual void NotifyDocumentChange() = 0;
    };
  }
}
#endif