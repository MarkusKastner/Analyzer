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