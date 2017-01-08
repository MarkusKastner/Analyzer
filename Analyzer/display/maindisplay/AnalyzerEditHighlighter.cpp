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


        //for (auto& functional : functionals){
        //  HighlightingRule rule;
        //  rule.pattern = QRegExp(QString::fromWCharArray(functional.c_str()));
        //  rule.format = functionalFormat;
        //  this->rules.append(rule);
        //}
        //for (auto& warning : warnings){
        //  HighlightingRule rule;
        //  rule.pattern = QRegExp(QString::fromWCharArray(warning.c_str()));
        //  rule.format = warningFormat;
        //  this->rules.append(rule);
        //}
        //for (auto& alarm : alarms){
        //  HighlightingRule rule;
        //  rule.pattern = QRegExp(QString::fromWCharArray(alarm.c_str()));
        //  rule.format = alarmFormat;
        //  this->rules.append(rule);
        //}

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
          rule.pattern = QRegExp(QString::fromWCharArray(expression.c_str()));
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

      std::vector<std::wstring> AnalyzerEditHighlighter::getFunctionalExps()
      {
        std::vector<std::wstring> exps;
        exps.push_back(L"<");
        exps.push_back(L">");
        exps.push_back(L"/>");
        exps.push_back(L"</");
        exps.push_back(L"Types");
        return exps;
      }

      std::vector<std::wstring> AnalyzerEditHighlighter::getWarningExps()
      {
        std::vector<std::wstring> exps;
        exps.push_back(L"Default Extension");
        return exps;
      }

      std::vector<std::wstring> AnalyzerEditHighlighter::getAlarmExps()
      {
        std::vector<std::wstring> exps;
        exps.push_back(L"Override PartName");
        return exps;
      }

      std::wstring AnalyzerEditHighlighter::getCommentStartExp()
      {
        return L"<!--";
      }

      std::wstring AnalyzerEditHighlighter::getCommentEndExp()
      {
        std::vector<std::wstring> exps;

        return L"-->";
      }

    }
  }
}
