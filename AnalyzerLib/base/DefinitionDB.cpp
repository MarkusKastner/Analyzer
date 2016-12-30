#include "DefinitionDB.h"

#include "my_global.h"

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
        throw - 1;
      }

      if (mysql_real_connect(this->connection, address.c_str(), user.c_str(), password.c_str(), NULL, port, NULL, 0) == NULL){
        //fprintf(stderr, "%s\n", mysql_error(this->connection));
        throw - 1;
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