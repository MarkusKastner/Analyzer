/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZEREDITHIGHLIGHTER_H
#define ANALYZEREDITHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <string>

class QTextDocument;

namespace analyzer{
  namespace gui{
    namespace display{
      class AnalyzerEditHighlighter : public QSyntaxHighlighter
      {
        Q_OBJECT

      public:
        enum Mode{
          DefaultMode = 0,
          xml
        };

        AnalyzerEditHighlighter(QTextDocument *parent = 0);
        void SetFunctionalHighlightExpressions(const std::vector<std::wstring> & expressions);
        void SetMode(const Mode & mode);

      protected:
        void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
        void xmlMode(const QString &text);

      private:
        struct HighlightingRule
        {
          QRegExp pattern;
          QTextCharFormat format;
        };
        QVector<HighlightingRule> rules;

        QTextCharFormat functionalFormat;
        QTextCharFormat warningFormat;
        QTextCharFormat alarmFormat;
        QTextCharFormat stringFormat;

        Mode mode;
        static QString toRegExp(const std::wstring & expression);
      };
    }
  }
}
#endif
