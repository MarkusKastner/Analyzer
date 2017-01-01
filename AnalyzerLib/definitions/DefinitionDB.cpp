#include "DefinitionDB.h"

#include "my_global.h"

#include "AnalyzerLib\base\error\DBException.h"

namespace analyzer{
  namespace definition{
    DefinitionDB::DefinitionDB()
      :DefinitionSource(), connection(nullptr)
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
        throw base::DBException("Cannot initialize MySQL C-Connector");
      }

      if (mysql_real_connect(this->connection, address.c_str(), user.c_str(), password.c_str(), NULL, port, NULL, 0) == NULL){
        throw base::DBException(std::string(mysql_error(this->connection)));
      }
    }

    bool DefinitionDB::IsInitialized()
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