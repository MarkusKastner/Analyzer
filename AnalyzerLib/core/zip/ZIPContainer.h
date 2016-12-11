#ifndef ZIPCONTAINER_H
#define ZIPCONTAINER_H

#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"

#include <string>
#include <vector>

#include "..\error\CoreException.h"

namespace analyzer{
  namespace core{
    class ZIPContainer
    {
    private:
      class MiniZIP
      {
      public:
        explicit MiniZIP(const std::string & containerFile)
          : zip_archive({ 0 })
        {
          this->open(containerFile);
        }
        ~MiniZIP(){
          mz_zip_reader_end(&zip_archive);
        }

        std::vector<std::string> GetfileNames(){
          std::vector<std::string> fileNames;
          for (int i = 0; i < (int)mz_zip_reader_get_num_files(&zip_archive); i++){
            mz_zip_archive_file_stat file_stat;
            if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)){
              mz_zip_reader_end(&zip_archive);
              throw CoreException("mz_zip_reader_file_stat() failed!\n");
            }

            fileNames.push_back(file_stat.m_filename);
          }
          return fileNames;
        }
      private:
        mz_zip_archive zip_archive;

        void open(const std::string & containerFile){
          memset(&zip_archive, 0, sizeof(zip_archive));

          if (!mz_zip_reader_init_file(&zip_archive, containerFile.c_str(), 0)){
            throw CoreException("mz_zip_reader_init_file() failed!\n");
          }
        }
      };

    public:
      ZIPContainer();
      ~ZIPContainer();

      bool HasContent();
      void Open(const std::string & containerFile);

    private:
      std::vector<std::string> fileNames;

    };
  }
}
#endif