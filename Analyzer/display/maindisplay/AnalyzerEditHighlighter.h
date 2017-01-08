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
        AnalyzerEditHighlighter(QTextDocument *parent = 0);
        void SetFunctionalHighlightExpressions(const std::vector<std::wstring> & expressions);

      protected:
        void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

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

        std::vector<std::wstring> getFunctionalExps();
        std::vector<std::wstring> getWarningExps();
        std::vector<std::wstring> getAlarmExps();
        std::wstring getCommentStartExp();
        std::wstring getCommentEndExp();
      };
    }
  }
}
#endif
