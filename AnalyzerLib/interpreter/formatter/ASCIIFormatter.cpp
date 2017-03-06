#include "ASCIIFormatter.h"

namespace analyzer {
  namespace interpreter {
    std::vector<std::string> ASCIIFormatter::Split(const std::string & text, const size_t & chunkSize)
    {
      std::vector<std::string> chunks;
      std::string chunk;
      for (auto& letter : text) {
        chunk += letter;
        if (chunk.size() == chunkSize) {
          chunks.push_back(chunk);
          chunk.clear();
        }
      }
      if (!chunk.empty()) {
        chunks.push_back(chunk);
      }
      return chunks;
    }
  }
}