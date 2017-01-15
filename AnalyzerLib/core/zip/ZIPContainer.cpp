/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ZIPContainer.h"

namespace analyzer{
  namespace core{

    ZIPContainer::ZIPContainer()
      :files()
    {

    }

    ZIPContainer::~ZIPContainer()
    {

    }

    bool ZIPContainer::HasContent()
    {
      return !this->files.empty();
    }

    void ZIPContainer::Open(const std::string & containerFile)
    {
      MiniZIP miniZip(containerFile);
      this->files = miniZip.GetFiles();
    }

    size_t ZIPContainer::GetFileCount()
    {
      return this->files.size();
    }

    core::File ZIPContainer::GetFileAt(const size_t & index)
    {
      return this->files.at(index);
    }
  }
}