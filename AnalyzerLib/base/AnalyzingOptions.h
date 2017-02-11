#ifndef ANALYZINGOPTIONS_H
#define ANALYZINGOPTIONS_H

namespace analyzer {
  namespace base {
    struct AnalyzingOptions
    {
      AnalyzingOptions() 
        : Extraordinary(false), Executable(false), ExternalLinks(false), Macros(false)
      {}

      bool Extraordinary;
      bool Executable;
      bool ExternalLinks;
      bool Macros;
    };
  }
}
#endif