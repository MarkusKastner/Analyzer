#include "DocumentStructure.h"

namespace analyzer{
  namespace gui{
    DocumentStructure::DocumentStructure(QWidget * parent)
      :QWidget(parent), fileTree(nullptr)
    {
      this->setup();
    }

    DocumentStructure::~DocumentStructure()
    {

    }

    void DocumentStructure::SetFiles(const std::vector<std::string> files)
    {
      QStringList fileNames;
      for each (auto& file in files)
      {
        fileNames.push_back(file.c_str());
      }

      QTreeWidgetItem *topLevelItem = NULL;
      foreach(const QString &fileName, fileNames)
      {
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

    void DocumentStructure::setup()
    {
      this->fileTree = new QTreeWidget(this);
    }
  }
}