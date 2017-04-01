/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ASCIIFormatter.h"

#include <bitset>
#include <sstream>
#include <iomanip>

#include "AnalyzerLib\interpreter\formatter\ASCIITable.h"

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

    std::string ASCIIFormatter::Text2BinaryExpression(const std::string & text)
    {
      std::string binString;
      for (auto& letter : text) {
        binString += std::bitset<8>(letter).to_string();
        binString += " ";
      }
      binString.pop_back();
      return binString;
    }

    std::string ASCIIFormatter::Text2NumericalExpression(const std::string & text)
    {
      std::string numString;
      for (auto& letter : text) {
        numString += std::to_string(static_cast<unsigned char>(letter));
        numString += " ";
      }
      numString.pop_back();
      return numString;
    }

    std::string ASCIIFormatter::Text2HexExpression(const std::string & text)
    {
      std::stringstream ss;
      ss << std::hex << std::setfill('0');
      for (int i = 0; i < text.size(); ++i){
        ss << std::setw(2) << static_cast<unsigned>(text[i]);
        ss << ' ';
      }
      std::string ret(ss.str());
      ret.pop_back();
      return ret;
    }

    std::string ASCIIFormatter::Bytes2BinaryExpression(const std::vector<unsigned char> & bytes)
    {
      std::string binString;
      for (auto& byte : bytes) {
        binString += std::bitset<8>(byte).to_string();
        binString += " ";
      }
      binString.pop_back();
      return binString;
    }

    std::string ASCIIFormatter::Bytes2NumericalExpression(const std::vector<unsigned char> & bytes)
    {
      std::stringstream ss;
      for (int i = 0; i < bytes.size(); ++i) {
        ss << std::setfill('0') << std::setw(2) << std::dec << static_cast<unsigned>(bytes[i]);
        ss << ' ';
      }
      std::string ret(ss.str());
      ret.pop_back();
      return ret;
    }

    std::string ASCIIFormatter::Bytes2HexExpression(const std::vector<unsigned char> & bytes)
    {
      std::stringstream ss;
      for (int i = 0; i < bytes.size(); ++i) {
        ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned>(bytes[i]);
        ss << ' ';
      }
      std::string ret(ss.str());
      ret.pop_back();
      return ret;
    }

    std::string ASCIIFormatter::Bytes2ASCIIExpression(const std::vector<unsigned char>& bytes)
    {
      std::stringstream ss;
      for (int i = 0; i < bytes.size(); ++i) {
        ss << ASCIITable::Byte2ASCIIExp(bytes[i]);
        ss << ' ';
      }
      std::string ret(ss.str());
      ret.pop_back();
      return ret;
    }
  }
}