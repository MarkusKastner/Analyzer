/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <string>

namespace analyzer {
  namespace base {
    class ApplicationSettings
    {
    public:
      ApplicationSettings();
      ~ApplicationSettings();

      void SetAppDir(const std::string & appDir);
      const std::string & GetAppDir();

      void SetLastOpenDir(const std::string & lastOpenDir);
      const std::string & GetLastOpenDir() const;

      void Serialize();

    private:
      std::string appDir;
      std::string lastOpenDir;

      void assertAppDir();

      static std::string fileName;
    };
  }
}
#endif