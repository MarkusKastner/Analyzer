/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef XMLINTERPRETER_H
#define XMLINTERPRETER_H

#include "Interpreter.h"

namespace analyzer {
  namespace interpreter {
    class XMLInterpreter : public Interpreter
    {
    public:
      XMLInterpreter();
      explicit XMLInterpreter(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual ~XMLInterpreter();

      virtual bool HasData();
      virtual void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      virtual const std::string & GetText();
      virtual core::FileFormat GetFileFormat();

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
      std::string text;
      std::string tabs;

      void format();
      void increaseTabs();
      void decreaseTabs();
    };
  }
}

#endif