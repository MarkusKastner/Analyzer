/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZINGSTRATEGY_H
#define ANALYZINGSTRATEGY_H

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "Result.h"

#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

namespace analyzer{
  namespace strategy{
    class AnalyzingStrategy
    {
    private:
      AnalyzingStrategy(const AnalyzingStrategy&);
      AnalyzingStrategy & operator=(const AnalyzingStrategy&);

    public:
      virtual ~AnalyzingStrategy();

      void SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource);
      bool HasDefinitionSource();

      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      bool HasData();

      void StartAnalyzing();
      bool IsAnalyzing();

      const std::vector<std::shared_ptr<Result>> & GetResults();

    protected:
      AnalyzingStrategy();
      virtual void analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<std::vector<unsigned char>> & data) = 0;
      virtual bool compareResult(const std::shared_ptr<Result> & result1, const std::shared_ptr<Result> & result2) = 0;

      void addResult(const std::shared_ptr<Result> & result);

    private:
      std::shared_ptr<definition::DefinitionSource> defSource;
      std::shared_ptr<std::vector<unsigned char>> data;
      std::vector<std::shared_ptr<Result>> results;

      std::thread * analyzingThread;
      std::atomic<bool> isAnalyzing;

      std::recursive_mutex sourceLock;
      std::recursive_mutex dataLock;
      std::recursive_mutex resultLock;

      void analyzingRoutine();
      bool hasResult(const std::shared_ptr<Result> & result);
    };
  }
}


#endif