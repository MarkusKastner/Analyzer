/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ApplicationSettings.h"

namespace analyzer {
  namespace base {
    ApplicationSettings::ApplicationSettings()
      :appDir()
    {
    }

    ApplicationSettings::~ApplicationSettings()
    {
    }

    void ApplicationSettings::SetAppDir(const std::string & appDir)
    {
      this->appDir = appDir;
    }

    const std::string & ApplicationSettings::GetAppDir() const
    {
      return this->appDir;
    }
  }
}