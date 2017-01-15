/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TEXTCHANGEDOBSERVER_H
#define TEXTCHANGEDOBSERVER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

namespace analyzer{
  namespace interpreter{
    class IMEX TextChangedObserver
    {
    public:
      virtual void NotifyDataChanged() = 0;
    };
  }
}
#endif