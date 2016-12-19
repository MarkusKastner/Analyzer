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
    private:
      class FilesEvent : public QEvent
      {
      public:
        explicit FilesEvent(const std::vector<std::string> & files)
          :QEvent(Type::User), files(files)
        {}
        virtual ~FilesEvent(){}
        const std::vector<std::string> & GetFiles(){ return this->files; }

      private:
        std::vector<std::string> files;
      };

    public:
      DocumentStructure(const QString & title,  QWidget * parent = 0);
      virtual ~DocumentStructure();
      void SetFiles(const std::vector<std::string> files);

    signals:
      void ActiveFileChanged(const std::string & fileName);

    protected:
      void customEvent(QEvent * evt);

    private:
      QWidget * baseWidget;
      QTreeWidget * fileTree;

      void setup();
      void setFiles(const std::vector<std::string> files);
      void onFileChange(const QModelIndex & index);
    };
  }
}

#endif