/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include <memory>

#include <QDockWidget>
#include <QTabWidget>

#include "Actions.h"
#include "AnalyzerLib\base\AnalyzerBase.h"
#include "AnalyzerLib\base\AnalyzerBaseObserver.h"

namespace analyzer{
  namespace gui{
    class DocumentStructure;
    class AnalyzeDock;
    class BinaryDock;
    class OutputDock;
    class AnalyzerTab;
    class MainWindow : public QMainWindow, public base::AnalyzerBaseObserver
    {
      Q_OBJECT

    public:
      MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent = 0);
      ~MainWindow();

      virtual void NotifyDocumentChange();
      virtual void AddBinaryLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical);
      virtual void ClearBinaryView();
      virtual void AddOutputMessage(const std::string & message);
      virtual void SetAvailableAnalyzingOptions(const base::AnalyzingOptions & analyzingOptions);
      virtual void FileChange();

      void SetBinaryOutputFromString(const QString & binary);
      void SetBinaryOutputFromBytes(const std::vector<unsigned char> & data);

    private:
      Ui::MainWindow ui;
      std::unique_ptr<Actions> actions;
      base::AnalyzerBase & analyzerBase;
      AnalyzerTab * tabWidget;

      AnalyzeDock * analyzeDock;
      OutputDock * outputDock;
      BinaryDock * binaryDock;
      DocumentStructure * documentStructure;

      std::shared_ptr<core::File> hexFile;

      void setup();
      void setupDialogs();

      void connectUI();

      void activeFileChanged(const std::string & fileName);
      void onDocStructureToggled(bool visible);
      void onOutputToggled(bool visible);
      void onAnalyzeToggled(bool visible);
      void onBinViewToggled(bool visible);
      void onDocViewVisibility(bool visible);
      void onOutputViewVisibility(bool visible);
      void onAnalyzeViewVisibility(bool visible);
      void onBinaryViewVisibility(bool visible);

      void onShowHex();
    };
  }
}
#endif 
