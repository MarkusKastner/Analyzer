/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "ViewTab.h"

#include <QVBoxLayout>

#include "AnalyzerTab.h"

#include "display\maindisplay\AnalyzerEdit.h"
#include "display\maindisplay\HTMLOutput.h"
#include "display\maindisplay\HexBrowser.h"
#include "display\pdf\PDFBrowser.h"

#include "mainwindow\MainWindow.h"
#include "application\error\AppException.h"

namespace analyzer {
  namespace gui {
    ViewTab::ViewTab(AnalyzerTab * parent)
      :QWidget(parent), viewOutput(nullptr)
    {
      this->setup();
    }

    ViewTab::~ViewTab()
    {
    }

    void ViewTab::SetFile(core::File * file)
    {
      MainWindow* mainWnd = nullptr;
      if (dynamic_cast<MainWindow*>(this->parent()->parent()->parent())) {
        mainWnd = dynamic_cast<MainWindow*>(this->parent()->parent()->parent());
      }
      this->ClearFile();
      if (file->UseRichText()) {
        switch (file->GetFileFormat()){
          case core::FileFormat::bmp:
            this->viewOutput = new display::HTMPOutput(this);
            break;
          case core::FileFormat::winExec:
            this->viewOutput = new display::HTMPOutput(this);
            break;
          case core::FileFormat::pdf:
            this->viewOutput = new display::PDFBrowser(this);
            break;
          case core::FileFormat::empty:
            this->viewOutput = new display::HTMPOutput(this);
            break;
          case core::FileFormat::hex:
            this->viewOutput = new display::HexBrowser(this);
            if (mainWnd != nullptr) {
              connect(dynamic_cast<display::HexBrowser*>(this->viewOutput), &display::HexBrowser::SetBinaryOutput, mainWnd, &MainWindow::SetBinaryOutputFromBytes);
            }
            break;
        default:
          throw app::AppException("Unknown file format in ViewTab::SetFile()");
          break;
        }
      }
      else {
        this->viewOutput = new display::AnalyzerEdit(this);
        if (mainWnd != nullptr) {
          connect(dynamic_cast<display::AnalyzerEdit*>(this->viewOutput), &display::AnalyzerEdit::SetBinaryOutput, mainWnd, &MainWindow::SetBinaryOutputFromString);
        }
      }
      this->layout()->addWidget(dynamic_cast<QWidget*>(this->viewOutput));
      this->viewOutput->SetFile(file);
    }

    void ViewTab::ClearFile()
    {
      if (this->viewOutput != nullptr) {
        this->layout()->removeWidget(dynamic_cast<QWidget*>(this->viewOutput));
        delete this->viewOutput;
        this->viewOutput = nullptr;
      }
    }

    void ViewTab::NotifyCheckRunFinished()
    {
    }

    void ViewTab::NotifyCurrentIndex(const size_t & checkIndex)
    {
      if (dynamic_cast<display::HexBrowser*>(this->viewOutput)) {
        
      }
    }

    void ViewTab::NotifyMarkedIndex(const analyzer::base::Marking & marking)
    {
      if (dynamic_cast<display::HexBrowser*>(this->viewOutput)) {
        dynamic_cast<display::HexBrowser*>(this->viewOutput)->MarkIndex(marking);
      }
    }

    void ViewTab::NotifyClearColor(const base::AnalyzerRGB & color)
    {
      if (dynamic_cast<display::HexBrowser*>(this->viewOutput)) {
        dynamic_cast<display::HexBrowser*>(this->viewOutput)->DeleteColor(color);
      }
    }

    void ViewTab::NotifyMarkSuspectRange(const size_t & index, const size_t offset)
    {
      if (dynamic_cast<display::HexBrowser*>(this->viewOutput)) {
        dynamic_cast<display::HexBrowser*>(this->viewOutput)->MarkSuspectedRange(index, offset);
      }
    }

    void ViewTab::setup()
    {
      this->setLayout(new QVBoxLayout());
      this->layout()->setContentsMargins(1, 1, 1, 1);
    }
  }
}