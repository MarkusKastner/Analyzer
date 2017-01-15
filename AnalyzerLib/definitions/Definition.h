/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DEFINITION_H
#define DEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace definition{
    class IMEX Definition
    {
    private:
      Definition(){}
    public:
      virtual ~Definition();

      const unsigned int & GetID();

      void SetDescription(const std::string & description);
      const std::string & GetDescription();

    protected:
      explicit Definition(const unsigned int & id);

    private:
      unsigned int id;
      std::string * description;
    };
  }
}

#endif