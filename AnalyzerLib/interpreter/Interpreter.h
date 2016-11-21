#ifndef INTERPRETER_H
#define INTERPRETER_H

namespace analyzer{
  namespace interpreter{
    class Interpreter
    {
    public:
      virtual bool HasData() = 0;
    };
  }
}
#endif