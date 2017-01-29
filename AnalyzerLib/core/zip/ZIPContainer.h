/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ZIPCONTAINER_H
#define ZIPCONTAINER_H

#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"

#include <string>
#include <vector>

#include "..\error\CoreException.h"
#include "AnalyzerLib\core\File.h"

namespace analyzer{
  namespace core{
    class ZIPContainer
    {
    private:
      class MiniZIP
      {
      public:
        explicit MiniZIP(const std::string & containerFile)
          : zip_archive({ 0 }), containerFile(containerFile)
        {
          this->open();
        }
        ~MiniZIP(){
          mz_zip_reader_end(&zip_archive);
        }

        std::vector<core::File> GetFiles(){
          void *p = nullptr;
          size_t uncomp_size;

          std::vector<core::File> files;
          unsigned int numFiles = mz_zip_reader_get_num_files(&zip_archive);

          for (unsigned int i = 0; i < numFiles; i++){
            std::vector<unsigned char> data;
            mz_zip_archive_file_stat file_stat;
            if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)){
              throw CoreException("mz_zip_reader_file_stat() failed!\n");
            }

            p = mz_zip_reader_extract_file_to_heap(&zip_archive, file_stat.m_filename, &uncomp_size, 0);
            if (!p){
              throw CoreException("mz_zip_reader_extract_file_to_heap() failed!\n");
            }
            data.resize(uncomp_size);
            if (memcpy(&data[0], p, uncomp_size) != &data[0]){
              mz_free(p);
              throw CoreException("mz_zip_reader_extract_file_to_heap() failed to extract the proper data\n");
            }

            files.push_back(core::File(file_stat.m_filename, data));
            mz_free(p);
          }
          return files;

        }
      private:
        mz_zip_archive zip_archive;
        std::string containerFile;

        void open(){
          memset(&zip_archive, 0, sizeof(zip_archive));

          if (!mz_zip_reader_init_file(&zip_archive, this->containerFile.c_str(), 0)){
            throw CoreException("mz_zip_reader_init_file() failed!\n");
          }
        }
      };

    public:
      ZIPContainer();
      ~ZIPContainer();

      bool HasContent();
      void Open(const std::string & containerFile);
      size_t GetFileCount();
      core::File GetFileAt(const size_t & index);

    private:
      std::vector<core::File> files;

    };
  }
}
#endif