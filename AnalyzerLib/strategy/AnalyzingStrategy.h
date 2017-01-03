#ifndef ANALYZINGSTRATEGY_H
#define ANALYZINGSTRATEGY_H

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\core\ByteCollection.h"

#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

namespace analyzer{
  namespace strategy{
    class AnalyzingStrategy
    {
    public:
      virtual ~AnalyzingStrategy();

      void SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource);
      bool HasDefinitionSource();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      bool HasData();

      void StartAnalyzing();
      bool IsAnalyzing();

    protected:
      AnalyzingStrategy();
      virtual void analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<analyzer::core::ByteCollection> & data) = 0;

    private:
      std::shared_ptr<definition::DefinitionSource> * defSource;
      std::shared_ptr<analyzer::core::ByteCollection> * data;

      std::thread * analyzingThread;
      std::recursive_mutex * sourceLock;
      std::recursive_mutex * dataLock;
      std::atomic<bool> * isAnalyzing;

      void analyzingRoutine();
    };
  }
}


#endif