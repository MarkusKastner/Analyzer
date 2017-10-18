/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ContentChecker.h"

#include "CheckObserver.h"
#include "AnalyzerLib/contentchecker/error/ContentCheckException.h"

namespace analyzer {
  namespace checker {
    ContentChecker::~ContentChecker()
    {
      this->StopCheck();
      if (this->checkThread && this->checkThread->joinable()) {
        this->checkThread->join();
      }
    }

    size_t ContentChecker::GetNumCheckObservers() const
    {
      return this->checkObservers.size();
    }

    void ContentChecker::RegisterCheckObserver(CheckObserver * observer)
    {
      for (auto& existing : this->checkObservers) {
        if (existing == observer) {
          return;
        }
      }
      this->checkObservers.push_back(observer);
    }

    void ContentChecker::UnregisterCheckObserver(CheckObserver * observer)
    {
      std::vector<CheckObserver*>::iterator end = this->checkObservers.end();

      for (auto it = this->checkObservers.begin(); it != end; ++it) {
        if ((*it) == observer) {
          it = this->checkObservers.erase(it);
          return;
        }
      }
    }

    void ContentChecker::SetWorkingColor(const base::AnalyzerRGB & color)
    {
      this->workingColor = color;
    }

    const base::AnalyzerRGB & ContentChecker::GetWorkingColor() const
    {
      return this->workingColor;
    }

    void ContentChecker::ClearWorkerMarkings()
    {
      this->notifyClearWorkingMarkings();
    }

    void ContentChecker::MarkSuspectRange(const size_t & index, const size_t & offset)
    {
      this->notifySuspectRange(index, offset);
    }

    bool ContentChecker::HasData()
    {
      return (this->data.get() != nullptr);
    }

    void ContentChecker::SetData(const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      this->data = data;
      this->checkOffest = this->data->size();
      this->dataSize = this->data->size();
    }

    void ContentChecker::ReleaseData()
    {
      if (this->data) {
        this->data.reset();
      }
    }

    void ContentChecker::SetCheckRange(const size_t & startOffset, const size_t & checkOffset)
    {
      this->startOffest = startOffset;
      this->checkOffest = checkOffset;
      this->searchPos = this->startOffest;
    }

    const size_t & ContentChecker::GetStartOffest() const
    {
      return this->startOffest;
    }

    const size_t & ContentChecker::GetCheckOffest() const
    {
      return this->checkOffest;
    }

    bool ContentChecker::IsChecking() const
    {
      return this->runCheck.load();
    }

    void ContentChecker::StartCheck()
    {
      if (!this->data || this->data->empty()) {
        throw ContentCheckException("Cannot start without data");
      }
      if (this->checkThread && this->checkThread->joinable()) {
        this->checkThread->join();
      }
      this->checkThread.reset(new std::thread(&ContentChecker::checkRoutine, this));
    }

    void ContentChecker::StopCheck()
    {
      this->runCheck = false;
      std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

    bool ContentChecker::IsFinished() const
    {
      return this->finished.load();
    }

    std::string ContentChecker::RangeToString(const size_t & offset, const size_t & length) const
    {
      return ContentChecker::RangeToString(offset, length, this->data);
    }

    std::string ContentChecker::RangeToString(const size_t & offset, const size_t & length, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      std::string strg;
      size_t endOffset = length + offset;
      if (endOffset > data->size()) {
        return strg;
      }
      for (size_t i = offset; i < endOffset; ++i) {
        strg.push_back(static_cast<char>(data->at(i)));
      }
      return strg;
    }

    const size_t & ContentChecker::GetSearchPos() const
    {
      return this->searchPos;
    }

    const size_t & ContentChecker::StepUpSearchPos()
    {
      ++this->searchPos;
      if (this->searchPos >= this->checkOffest) {
        this->searchPos = 0;
        this->searchDone = true;
        this->notifyProgress(-1);
      }
      return this->searchPos;
    }

    void ContentChecker::SetSearchPos(const size_t & searchPos)
    {
      this->searchPos = searchPos;
      if (this->searchPos == 0) {
        this->searchDone = false;
      }

      int percent = 100 * searchPos / this->dataSize;
      if (percent != this->currentProgress) {
        this->currentProgress = percent;
        this->notifyProgress(this->currentProgress.load());
      }
    }

    bool ContentChecker::SearchDone()
    {
      return this->searchDone;
    }

    ContentChecker::ContentChecker()
      :checkObservers(), workingColor({ 0,0,0 }), data(), dataSize(0),
      startOffest(0), checkOffest(0), runCheck(false), finished(false),
      searchPos(0), searchDone(false), currentProgress(-1)
    {
    }

    bool ContentChecker::HasPreByte(const size_t & offset)
    {
      return (offset >= 1);
    }

    bool ContentChecker::HasPostByte(const size_t & offset, const size_t & expressionLength, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      return (offset + expressionLength + 1 < data->size());
    }

    bool ContentChecker::IsByteSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      return ContentChecker::IsByteSpace(data->at(offset));
    }

    bool ContentChecker::IsByteSpace(const unsigned char & byte)
    {
      return (byte == ' ' || byte == '\r' || byte == '\n' || byte == '\t');
    }

    bool ContentChecker::IsByteABC(const unsigned char & byte)
    {
      return ((byte >= 65 && byte <= 90) || (byte >= 97 && byte <= 122));
    }

    bool ContentChecker::IsByteNum(const unsigned char & byte)
    {
      return (byte >= 48 && byte <= 57);
    }

    bool ContentChecker::IsByteBeforeSpace(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (ContentChecker::HasPreByte(offset)) {
        return ContentChecker::IsByteSpace(offset - 1, data);
      }
      return false;
    }

    bool ContentChecker::IsByteBefore(const unsigned char & value, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (ContentChecker::HasPreByte(offset)) {
        return data->at(offset - 1) == value;
      }
      return false;
    }

    bool ContentChecker::IsByteBeforeLineFeed(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      if (!ContentChecker::HasPreByte(offset)) {
        return false;
      }
      if (!(data->at(offset - 1) == '\n' && ContentChecker::HasPreByte(offset - 1))) {
        return false;
      }
      if (data->at(offset - 2) == '\r') {
        return true;
      }
      return false;
    }

    unsigned char ContentChecker::FindNextNoneSpacePrintable(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>> & data)
    {
      size_t size = data->size();
      for (size_t i = offset; i < size; ++i) {
        if (ContentChecker::IsNoneSpacePrintable(data->at(i))) {
          return data->at(i);
        }
      }
      return 0;
    }

    std::string ContentChecker::FindWordBeforeOffset(const size_t numWordsBefore, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      std::string foundWord;
      bool assemblingWordActive = false;
      size_t wordCounter = 0;
      for (size_t i = offset - 1; i != 0; --i) {
        if (!ContentChecker::IsByteSpace(i, data)) {
          if (!assemblingWordActive) {
            wordCounter++;
          }
          assemblingWordActive = true;
        }
        else {
          if (assemblingWordActive && wordCounter >= numWordsBefore) {
            break;
          }
          assemblingWordActive = false;
          foundWord = "";
        }
        if (assemblingWordActive) {
          foundWord.insert(foundWord.begin(), data->at(i));
        }
      }
      return foundWord;
    }

    bool ContentChecker::LastByteInLineIs(const unsigned char value, const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data)
    {
      auto lineBytes(ContentChecker::GetRestOfLineWithoutLF(offset, data, true));
      if (!lineBytes.empty()) {
        return lineBytes.back() == value;
      }
      return false;
    }

    std::vector<unsigned char> ContentChecker::GetRestOfLineWithoutLF(const size_t & offset, const std::shared_ptr<std::vector<unsigned char>>& data, const bool & skipSpaces)
    {
      std::vector<unsigned char> lineBytes;
      auto size = data->size();
      for (size_t i = offset; i < size; ++i) {
        char currentByte = data->at(i);
        if (currentByte != '\r') {
          if (skipSpaces && ContentChecker::IsByteSpace(currentByte)) {
            continue;
          }
          else {
            lineBytes.push_back(currentByte);
          }
        }
        else {
          break;
        }
      }
      return lineBytes;
    }

    bool ContentChecker::IsNoneSpacePrintable(const unsigned char & byte)
    {
      if ((byte >= 33 && byte <= 126) ||
        (byte >= 128 && byte <= 159) ||
        (byte >= 161 && byte <= 172) ||
        (byte >= 147 && byte <= 255)
        ) {
        return true;
      }
      return false;
    }

    const std::shared_ptr<std::vector<unsigned char>> & ContentChecker::getData()
    {
      return this->data;
    }

    void ContentChecker::notifyCurrentIndex(const size_t index)
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyCurrentIndex(index);
      }
    }

    void ContentChecker::notifyMarkedIndex(const size_t index)
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyMarkedIndex({ index, this->workingColor });
      }
    }

    void ContentChecker::notifyClearWorkingMarkings()
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyClearColor( this->workingColor );
      }
    }

    void ContentChecker::notifySuspectRange(const size_t & index, const size_t & offset)
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyMarkSuspectRange(index, offset);
      }
    }

    void ContentChecker::notifyProgress(const int percent)
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyProgress(percent);
      }
    }

    void ContentChecker::checkRoutine()
    {
      this->finished = false;
      this->runCheck = true;
      this->checkData();
      this->runCheck = false;
      this->finished = true;
      this->notifyCheckFinished();
    }

    void ContentChecker::notifyCheckFinished()
    {
      for (auto& observer : this->checkObservers) {
        observer->NotifyCheckRunFinished();
      }
    }
  }
}