/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef FILEINFO_H
#define FILEINFO_H

namespace analyzer {
  namespace core {
    enum MajorType
    {
      text = 0,
      binary,
      mixed,
      empty
    };

    enum MinorType
    {
      ascii = 0,
      xml,
      unknown
    };

    struct FileInfo 
    {
      FileInfo() : majorType(MajorType::mixed), minorType(MinorType::unknown){}
      MajorType majorType;
      MinorType minorType;
    };
  }
}

#endif