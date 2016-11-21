#include "BinaryStyleInterpreter.h"

namespace analyzer{
  namespace interpreter{

    BinaryStyleInterpreter::BinaryStyleInterpreter()
      : byteCollection()
    {

    }

    BinaryStyleInterpreter::BinaryStyleInterpreter(const std::shared_ptr<analyzer::core::ByteCollection> & byteCollection)
      : byteCollection(byteCollection)
    {

    }

    BinaryStyleInterpreter::~BinaryStyleInterpreter()
    {

    }

    bool BinaryStyleInterpreter::HasData()
    {
      if (!this->byteCollection){
        return false;
      }
      if (this->byteCollection->GetSize() == 0){
        return false;
      }
      else{
        return true;
      }
    }
    
  }
}