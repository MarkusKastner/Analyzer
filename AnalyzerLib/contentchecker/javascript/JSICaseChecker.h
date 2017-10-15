/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef JSICASEHECKER_H
#define JSICASEHECKER_H

#include <memory>
#include <vector>

namespace analyzer {
  namespace checker {
    class JSICaseChecker
    {
    public:
      JSICaseChecker() = delete;
      explicit JSICaseChecker(const std::shared_ptr<std::vector<unsigned char>> & data);
      ~JSICaseChecker();
      bool HasData() const;
      void SetData(const std::shared_ptr<std::vector<unsigned char>> & data);
      void ReleaseData();

      bool IsMyCase(const size_t & offset);

    private:
      std::shared_ptr<std::vector<unsigned char>> data;
    };
  }
}
#endif