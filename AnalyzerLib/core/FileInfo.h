/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILEINFO_H
#define FILEINFO_H

namespace analyzer {
  namespace core {

    typedef enum {
      empty = 0,
      unknown,
      ascii,
      xml,
      pdf,
      winExec,
      bmp
    } FileFormat;

    struct FileInfo 
    {
      FileInfo() : Format(empty) {}
      FileFormat Format;
    };
  }
}

#endif