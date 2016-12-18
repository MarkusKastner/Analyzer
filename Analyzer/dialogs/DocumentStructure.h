#ifndef DOCUMENTSTRUCTURE_H
#define DOCUMENTSTRUCTURE_H

#include <QWidget>
#include <QTreeWidget>

namespace analyzer{
  namespace gui{
    class DocumentStructure : public QWidget
    {
    public:
      DocumentStructure(QWidget * parent = 0);
      virtual ~DocumentStructure();
      void SetFiles(const std::vector<std::string> files);

    private:
      QTreeWidget * fileTree;

      void setup();
    };
  }
}

#endif