#include "AnalyzerEditHighlighter.h"

namespace analyzer{
  namespace gui{
    namespace display{
      AnalyzerEditHighlighter::AnalyzerEditHighlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent)
      {
        functionalFormat.setForeground(Qt::blue);
        functionalFormat.setFontWeight(QFont::Bold);

        warningFormat.setForeground(Qt::GlobalColor::darkCyan);
        warningFormat.setFontWeight(QFont::Bold);

        alarmFormat.setForeground(Qt::GlobalColor::red);
        alarmFormat.setFontWeight(QFont::Bold);

        stringFormat.setForeground(Qt::GlobalColor::gray);
        stringFormat.setFontWeight(QFont::Weight::Normal);

        HighlightingRule stringRule;
        stringRule.pattern.setPatternSyntax(QRegExp::Wildcard);
        stringRule.pattern = QRegExp("\"([^\"]*)\"");
        stringRule.format = stringFormat;
        rules.append(stringRule);
      }

      void AnalyzerEditHighlighter::SetFunctionalHighlightExpressions(const std::vector<std::wstring> & expressions)
      {
        for (auto& expression : expressions){
          HighlightingRule rule;
          rule.pattern = QRegExp(AnalyzerEditHighlighter::toRegExp(expression));
          rule.format = functionalFormat;
          this->rules.append(rule);
        }
      }

      void AnalyzerEditHighlighter::highlightBlock(const QString &text)
      {
        foreach(const HighlightingRule &rule, rules) {
          QRegExp expression(rule.pattern);
          int index = expression.indexIn(text);
          while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
          }
        }
        setCurrentBlockState(0);
      }

      QString AnalyzerEditHighlighter::toRegExp(const std::wstring & expression)
      {
        QString regexp("[");
        regexp += QString::fromWCharArray(expression.c_str());
        regexp += "]{";
        regexp += QString::number(expression.size());
        regexp += "}";
        return regexp;
      }
    }
  }
}