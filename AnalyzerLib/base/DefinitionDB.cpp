#include "DefinitionDB.h"

#include "my_global.h"

#include "error\DBException.h"

namespace analyzer{
  namespace base{
    DefinitionDB::DefinitionDB()
      :connection(nullptr)
    {
    }

    DefinitionDB::~DefinitionDB()
    {
      mysql_close(this->connection);
    }

    void DefinitionDB::Connect(const std::string & address, const int & port, const std::string & user, const std::string & password)
    {
      this->connection = mysql_init(NULL);
      if (nullptr == this->connection){
        throw DBException("Cannot initialize MySQL C-Connector");
      }

      if (mysql_real_connect(this->connection, address.c_str(), user.c_str(), password.c_str(), NULL, port, NULL, 0) == NULL){
        throw DBException(std::string(mysql_error(this->connection)));
      }
    }

    bool DefinitionDB::IsConnected()
    {
      if (this->connection != nullptr){
        return true;
      }
      else{
        return false;
      }
    }
  }
}