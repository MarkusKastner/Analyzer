#include "ZIPContainer.h"

namespace analyzer{
  namespace core{

    ZIPContainer::ZIPContainer()
      :fileNames()
    {

    }

    ZIPContainer::~ZIPContainer()
    {

    }

    bool ZIPContainer::HasContent()
    {
      return !this->fileNames.empty();
    }

    void ZIPContainer::Open(const std::string & containerFile)
    {
      MiniZIP miniZip(containerFile);
      fileNames = miniZip.GetfileNames();
    }
  }
}