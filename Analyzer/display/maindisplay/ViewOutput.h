/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef VIEWOUTPUT_H
#define VIEWOUTPUT_H

namespace analyzer {
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class ViewOutput
      {
      public:
        virtual ~ViewOutput() {}

        virtual void SetFile(core::File * file) = 0;
        virtual void ClearFile() = 0;
      };
    }
  }
}
#endif