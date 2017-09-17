/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ApplicationSettings.h"

#include <filesystem>
#include <fstream>

#include "AnalyzerLib/base/error/AnalyzerBaseException.h"

namespace fs = std::tr2::sys;

namespace analyzer {
  namespace base {
    ApplicationSettings::ApplicationSettings()
      :appDir(), lastOpenDir()
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

    void ApplicationSettings::SetLastOpenDir(const std::string & lastOpenDir)
    {
      this->lastOpenDir = lastOpenDir;
    }

    std::string ApplicationSettings::GetLastOpenDir() const
    {
      if (fs::exists(fs::path(this->lastOpenDir))) {
        return this->lastOpenDir;
      }
      return std::string();
    }

    void ApplicationSettings::Serialize()
    {
      this->assertAppDir();

      std::string filePath(this->appDir + "/" + ApplicationSettings::fileName);
      std::ofstream out(filePath, std::ios::out | std::ios::trunc);

      if (!out.is_open() || out.bad()) {
        throw AnalyzerBaseException(AnalyzerBaseException::ErrorCode::CannotOpenOrCreateSettingsFile);
      }

      out << lastOpenDirTag << "=" << this->lastOpenDir << std::endl;

      out.flush();
    }

    void ApplicationSettings::Deserialize()
    {
      this->assertAppDir();

      std::string filePath(this->appDir + "/" + ApplicationSettings::fileName);
      std::ifstream in(filePath, std::ios::in);

      if (!in.is_open() || in.bad()) {
        throw AnalyzerBaseException(AnalyzerBaseException::ErrorCode::CannotOpenOrCreateSettingsFile);
      }

      std::string line;
      while (std::getline(in, line))
      {
        std::string tag(ApplicationSettings::parseTag(line));

        if (tag.compare(ApplicationSettings::lastOpenDirTag) == 0) {
          this->lastOpenDir = ApplicationSettings::parseValue(line);
        }
      }
      
    }

    void ApplicationSettings::assertAppDir()
    {
      if (!fs::exists(fs::path(this->appDir))) {
        throw AnalyzerBaseException(AnalyzerBaseException::ErrorCode::ApplicationPathNotSet);
      }
    }

    std::string ApplicationSettings::parseTag(const std::string & line)
    {
      size_t splittOffset = line.find_first_of('=');
      if (splittOffset > line.size() + 1) {
        return std::string();
      }
      std::string tag(line.substr(0, splittOffset));
      return tag;
    }

    std::string ApplicationSettings::parseValue(const std::string & line)
    {
      size_t splittOffset = line.find_first_of('=');
      if (splittOffset > line.size() + 1) {
        return std::string();
      }
      std::string val(line.substr(splittOffset + 1, line.size() - splittOffset));
      return val;
    }

    std::string ApplicationSettings::fileName = "analyzer.config";
    std::string ApplicationSettings::lastOpenDirTag = "LastOpenDirectory";
  }
}