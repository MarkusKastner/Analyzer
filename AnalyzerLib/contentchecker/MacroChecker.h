/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MACROCHECKER_H
#define MACROCHECKER_H

#include "ContentChecker.h"

namespace analyzer {
  namespace checker {
    class MacroChecker : public ContentChecker
    {
    public:
      MacroChecker();
      virtual ~MacroChecker();

      size_t FindNextSyntaxHint();
      bool IsSyntax(const size_t & offset);
      bool IsACaseSyntax(const size_t & offset);
      bool IsICaseSyntax(const size_t & offset);
      bool IsBCaseSyntax(const size_t & offset);
      bool IsCCaseSyntax(const size_t & offset);
      const size_t & GetLastFoundSyntaxOffset() const;

    protected:
      virtual void checkData();

    private:
      size_t lastFoundSyntaxOffset;

    public:
      static const std::string KeyWord_abstract;
      static const std::string KeyWord_arguments;
      static const std::string KeyWord_await;

      static const std::string KeyWord_boolean;
      static const std::string KeyWord_break;
      static const std::string KeyWord_byte;

      static const std::string KeyWord_case;
      static const std::string KeyWord_catch;
      static const std::string KeyWord_char;
      static const std::string KeyWord_class;
      static const std::string KeyWord_const;
      static const std::string KeyWord_continue;

      static const std::string KeyWord_debugger;
      static const std::string KeyWord_default;
      static const std::string KeyWord_delete;
      static const std::string KeyWord_do;
      static const std::string KeyWord_double;

      static const std::string KeyWord_else;
      static const std::string KeyWord_enum;
      static const std::string KeyWord_eval;
      static const std::string KeyWord_export;
      static const std::string KeyWord_extends;

      static const std::string KeyWord_false;
      static const std::string KeyWord_final;
      static const std::string KeyWord_finally;
      static const std::string KeyWord_float;
      static const std::string KeyWord_for;
      static const std::string KeyWord_function;

      static const std::string KeyWord_goto;

      static const std::string KeyWord_if;
      static const std::string KeyWord_implements;
      static const std::string KeyWord_import;
      static const std::string KeyWord_in;
      static const std::string KeyWord_instanceof;
      static const std::string KeyWord_int;
      static const std::string KeyWord_interface;

      /*


static const std::string KeyWord_let
static const std::string KeyWord_long	
static const std::string KeyWord_native	
static const std::string KeyWord_new
static const std::string KeyWord_null	
static const std::string KeyWord_package	
static const std::string KeyWord_private	
static const std::string KeyWord_protected
static const std::string KeyWord_public	
static const std::string KeyWord_return	
static const std::string KeyWord_short	
static const std::string KeyWord_static
static const std::string KeyWord_super
static const std::string KeyWord_switch	
static const std::string KeyWord_synchronized	
static const std::string KeyWord_this
static const std::string KeyWord_throw	
static const std::string KeyWord_throws	
static const std::string KeyWord_transient	
static const std::string KeyWord_true
static const std::string KeyWord_try	
static const std::string KeyWord_typeof	
static const std::string KeyWord_var	
static const std::string KeyWord_void
static const std::string KeyWord_volatile	
static const std::string KeyWord_while	
static const std::string KeyWord_with	
static const std::string KeyWord_yield
      
      */
    };
  }
}
#endif