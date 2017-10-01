/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerTab.h"
#include "ViewTab.h"
#include "AnalyzeResultTab.h"
#include "mainwindow\MainWindow.h"
#include "AnalyzerLib/base/AnalyzerBase.h"

namespace analyzer {
  namespace gui {
    AnalyzerTab::AnalyzerTab(QWidget * parent)
     : QTabWidget(parent), viewTab(nullptr), resultTab(nullptr), hexTab(nullptr)
    {
      this->setup();
    }

    AnalyzerTab::~AnalyzerTab()
    {
    }

    ViewTab * AnalyzerTab::GetViewTab()
    {
      return this->viewTab;
    }

    QTextEdit * AnalyzerTab::GetResultTextEdit()
    {
      return this->resultTab->GetResultTextEdit();
    }

    ViewTab * AnalyzerTab::AddHexTab()
    {
      if (this->hexTab == nullptr) {
        this->hexTab = new ViewTab(this);
        this->addTab(this->hexTab, tr("Hex"));
        if (dynamic_cast<MainWindow*>(this->parent())) {
          dynamic_cast<MainWindow*>(this->parent())->GetAnalyzerBase().GetContentCheckerVault().RegisterCheckObserver(this->hexTab);
        }
      }
      return this->hexTab;
    }

    void AnalyzerTab::ClearHexTab()
    {
      if (this->hexTab == nullptr) {
        return;
      }
      for (int i = 0; i < this->count(); i++) {
        if (this->widget(i)->windowTitle().compare("Hex") == 0) {
          this->removeTab(i);
        }
      }
      delete this->hexTab;
      this->hexTab = nullptr;
    }

    bool AnalyzerTab::HasHexTab() const
    {
      for (int i = 0; i < this->count(); i++) {
        if (this->widget(i)->windowTitle().compare("Hex") == 0) {
          return true;
        }
      }
      return false;
    }

    ViewTab * AnalyzerTab::GetHexTab()
    {
      return nullptr;
    }

    bool AnalyzerTab::IsAnalyzeResultTabInitialized() const
    {
      if (this->resultTab == nullptr) {
        return false;
      }
      else {
        return true;
      }
    }

    AnalyzeResultTab * AnalyzerTab::GetAnalyzeResultTab() const
    {
      this->assertAnalyzeResultTab();
      return this->resultTab;
    }

    void AnalyzerTab::AddAnalyzeResultTab()
    {
      this->resultTab = new AnalyzeResultTab(this);
      this->addTab(this->resultTab, tr("Analyze Result"));
    }
    
    void AnalyzerTab::setup()
    {
      this->setTabsClosable(true);
      connect(this, &AnalyzerTab::tabCloseRequested, this, &AnalyzerTab::onCloseTab);

      this->viewTab = new ViewTab(this);
      this->addTab(this->viewTab, tr("View"));
    }

    void AnalyzerTab::onCloseTab(const int & index)
    {
      if (this->tabText(index).compare("Hex") == 0) {
        this->ClearHexTab();
        return;
      }
      if (dynamic_cast<AnalyzeResultTab*>(this->widget(index))) {
        this->removeTab(index);
        delete this->resultTab;
        this->resultTab = nullptr;
      }
    }

    void AnalyzerTab::assertAnalyzeResultTab() const
    {
      if (this->resultTab == nullptr) {
        throw std::exception("Invalid analyze result tab");
      }
    }
  }
}
