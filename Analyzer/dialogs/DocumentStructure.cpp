#include "DocumentStructure.h"

#include <QApplication>
#include <QVBoxLayout>

namespace analyzer{
  namespace gui{
    DocumentStructure::DocumentStructure(const QString & title, QWidget * parent)
      :QDockWidget(title, parent), baseWidget(nullptr), fileTree(nullptr)
    {
      this->setup();
    }

    DocumentStructure::~DocumentStructure()
    {

    }

    void DocumentStructure::SetFiles(const std::vector<std::string> files)
    {
      QApplication::postEvent(this, new FilesEvent(files));
    }

    void DocumentStructure::customEvent(QEvent * evt)
    {
      if (dynamic_cast<FilesEvent*>(evt)){
        this->setFiles(dynamic_cast<FilesEvent*>(evt)->GetFiles());
      }
    }

    void DocumentStructure::setup()
    {
      this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
      this->baseWidget = new QWidget();
      this->setWidget(this->baseWidget);
      this->baseWidget->setLayout(new QVBoxLayout());

      this->fileTree = new QTreeWidget(this->baseWidget);
      this->baseWidget->layout()->addWidget(this->fileTree);

      connect(this->fileTree, &QTreeWidget::clicked, this, &DocumentStructure::onFileChange);
    }

    void DocumentStructure::setFiles(const std::vector<std::string> files)
    {
      this->fileTree->clear();
      QStringList fileNames;
      for each (auto& file in files){
        fileNames.push_back(file.c_str());
      }

      QTreeWidgetItem *topLevelItem = NULL;
      foreach(const QString &fileName, fileNames){
        QStringList splitFileName = fileName.split("/");
        
        if (this->fileTree->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty()){
          topLevelItem = new QTreeWidgetItem;
          topLevelItem->setText(0, splitFileName[0]);
          this->fileTree->addTopLevelItem(topLevelItem);
        }

        QTreeWidgetItem *parentItem = topLevelItem;

        for (int i = 1; i < splitFileName.size() - 1; ++i){
          bool thisDirectoryExists = false;
          for (int j = 0; j < parentItem->childCount(); ++j){
            if (splitFileName[i] == parentItem->child(j)->text(0)){
              thisDirectoryExists = true;
              parentItem = parentItem->child(j);
              break;
            }
          }

          if (!thisDirectoryExists){
            parentItem = new QTreeWidgetItem(parentItem);
            parentItem->setText(0, splitFileName[i]);
          }
        }
        QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
        childItem->setText(0, splitFileName.last());
      }
    }

    void DocumentStructure::onFileChange(const QModelIndex & index)
    {
      QVariant data = index.data();
      std::string file = data.toString().toStdString();
      std::string test;
    }
  }
}