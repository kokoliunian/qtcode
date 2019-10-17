#include "loghighlighter.h"
#include <QMessageBox>
#define LOG_FONT_SIZE 13
logHighlighter::logHighlighter(QTextDocument* parent):QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    //设置报警显示规则，颜色，字体
    singleLineCommentFormatAlarm.setForeground(Qt::red);
    singleLineCommentFormatAlarm.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("[^\n]*<警告>[^\n]*");
    rule.format = singleLineCommentFormatAlarm;
    highlightingRules.append(rule);

    singleLineCommentFormatAlarm1.setForeground(Qt::black);
    singleLineCommentFormatAlarm1.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("[^\n]*<运行>[^\n]*");
    rule.format = singleLineCommentFormatAlarm1;
    highlightingRules.append(rule);

    //设置搜救日志显示规则，字体和颜色
    singleLineCommentFormatSearch.setForeground(Qt::green);
    singleLineCommentFormatSearch.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("[^\n]*<记录>[^\n]*");
    rule.format = singleLineCommentFormatSearch;
    highlightingRules.append(rule);

    singleLineCommentFormatSearch1.setForeground(Qt::green);
    singleLineCommentFormatSearch1.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("<SH>[^\n]*");
    rule.format = singleLineCommentFormatSearch1;
    highlightingRules.append(rule);


    //设置撤离日志显示规则
    singleLineCommentFormatRetrate.setForeground(QColor(255,140,0));
    singleLineCommentFormatRetrate.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("[^\n]*<注意>[^\n]*");
    rule.format=singleLineCommentFormatRetrate;
    highlightingRules.append(rule);

    singleLineCommentFormatRetrate1.setForeground(QColor(222,134,0));
    singleLineCommentFormatRetrate1.setFont(QFont("Arial",LOG_FONT_SIZE,QFont::Normal));
    rule.pattern = QRegExp("<WD>[^\n]*");
    rule.format=singleLineCommentFormatRetrate1;
    highlightingRules.append(rule);

}

void logHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
