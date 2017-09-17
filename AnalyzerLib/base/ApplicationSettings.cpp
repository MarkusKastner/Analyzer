/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ApplicationSettings.h"

#include <filesystem>

#include "AnalyzerLib/base/error/AnalyzerBaseException.h"

namespace fs = std::tr2::sys;

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

    const std::string & ApplicationSettings::GetAppDir()
    {
      this->assertAppDir();
      return this->appDir;
    }

    void ApplicationSettings::assertAppDir()
    {
      if (!fs::exists(fs::path(this->appDir))) {
        throw AnalyzerBaseException(AnalyzerBaseException::ErrorCode::ApplicationPathNotSet);
      }
    }
  }
}