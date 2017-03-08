/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "AnalyzerEditHighlighter.h"

namespace analyzer{
  namespace gui{
    namespace display{
      AnalyzerEditHighlighter::AnalyzerEditHighlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent), mode(Mode::DefaultMode)
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

      void AnalyzerEditHighlighter::SetFunctionalHighlightExpressions(const std::vector<std::string> & expressions)
      {
        for (auto& expression : expressions){
          HighlightingRule rule;
          rule.pattern = QRegExp(AnalyzerEditHighlighter::toRegExp(expression));
          rule.format = functionalFormat;
          this->rules.append(rule);
        }
      }

      void AnalyzerEditHighlighter::SetMode(const AnalyzerEditHighlighter::Mode & mode)
      {
        this->mode = mode;
      }

      void AnalyzerEditHighlighter::highlightBlock(const QString &text)
      {
        if (this->mode == Mode::xml){
          this->xmlMode(text);
        }
        else{
          foreach(const HighlightingRule &rule, rules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while (index >= 0) {
              int length = expression.matchedLength();
              setFormat(index, length, rule.format);
              index = expression.indexIn(text, index + length);
            }
          }
        }
        setCurrentBlockState(0);
      }

      void AnalyzerEditHighlighter::xmlMode(const QString &text)
      {
        bool insideXML = false;
        for (int i = 0; i < text.size(); ++i){
          if (text.at(i) == '<'){
            insideXML = true;
            int count = text.indexOf(QRegExp("[\\s>]"), i) - i;
            this->setFormat(i, count+1, functionalFormat);
            i += count;
          }
          if (text.at(i) == '>'){
            insideXML = false;
            this->setFormat(i, 1, functionalFormat);
            if (text.at(i - 1) == '/'){
              this->setFormat(i - 1, 1, functionalFormat);
            }
          }
          if (insideXML && text.at(i) == '"'){
            int count = text.indexOf(QRegExp("[\"]"), i + 1) - i;
            if (count < 0){
              break;
            }
            this->setFormat(i, count + 1, stringFormat);
            i += count;
          }
          if (i + 1 > text.size()){
            break;
          }
        }
      }

      QString AnalyzerEditHighlighter::toRegExp(const std::string & expression)
      {
        QString regexp("[");
        regexp += QString::fromLatin1(expression.c_str());
        regexp += "]{";
        regexp += QString::number(expression.size());
        regexp += "}";
        return regexp;
      }
    }
  }
}