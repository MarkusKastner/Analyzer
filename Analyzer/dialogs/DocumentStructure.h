/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DOCUMENTSTRUCTURE_H
#define DOCUMENTSTRUCTURE_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QEvent>

namespace analyzer{
  namespace gui{
    class DocumentStructure : public QDockWidget
    {
      Q_OBJECT

    public:
      DocumentStructure(const QString & title,  QWidget * parent = 0);
      virtual ~DocumentStructure();
      void SetFiles(const std::vector<std::string> files);
      void AddFile(const std::string & file);

    signals:
      void ActiveFileChanged(const std::string & fileName);

    protected:
      void customEvent(QEvent * evt);

    private:
      QTreeWidget * fileTree;

      void setup();
      void setFiles(const std::vector<std::string> files);
      void addFile(const std::string & file);
      QTreeWidgetItem * checkDir(const std::string & file);
      QTreeWidgetItem * createFileItem(const std::string & file);
      void addTreeItem(QTreeWidgetItem * item);
      void addTreeItem(QTreeWidgetItem * parent, QTreeWidgetItem * item);

      std::vector<std::string> getSplittedDir(const std::string & dir);
      std::string getFileName(const std::string & file);

      void onItemChanged(QTreeWidgetItem * item, int col);

      class FilesEvent : public QEvent
      {
      public:
        explicit FilesEvent(const std::vector<std::string> & files)
          :QEvent(static_cast<QEvent::Type>(Type::User + 1)), files(files)
        {}
        virtual ~FilesEvent() {}
        const std::vector<std::string> & GetFiles() { return this->files; }

      private:
        std::vector<std::string> files;
      };

      class AddFileEvent : public QEvent
      {
      public:
        explicit AddFileEvent(const std::string & file)
          :QEvent(static_cast<QEvent::Type>(Type::User + 2)), file(file)
        {}
        virtual ~AddFileEvent() {}
        const std::string & GetFile() { return this->file; }

      private:
        std::string file;
      };

      class FileItem : public QTreeWidgetItem
      {
      public:
        explicit FileItem(QTreeWidgetItem * parent = nullptr)
          :QTreeWidgetItem(parent)
        {}
        virtual ~FileItem() {}
        void SetFilePath(const std::string & filePath) { this->filePath = filePath; }
        const std::string & GetFilePath() { return this->filePath; }
      private:
        std::string filePath;
      };
    };
  }
}

#endif