#ifndef LOGHIGHLIGHTER_H
#define LOGHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTimer>
//日志显示高亮格式化规则，可以突出显示某些关键字，特殊行高亮显示，多行高亮显示等
class logHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    bool    m_bFlush;
    logHighlighter(QTextDocument* parent=0);
    void highlightBlock(const QString &text);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;       //高亮规则，所有规则都保存到本链表当中
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;                       //关键字,可以是多个
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormatSearch;      //搜救格式
    QTextCharFormat singleLineCommentFormatAlarm;       //报警格式
    QTextCharFormat singleLineCommentFormatRetrate;     //撤退格式
    QTextCharFormat singleLineCommentFormatSearch1;      //搜救格式，英文
    QTextCharFormat singleLineCommentFormatAlarm1;       //报警格式，英文
    QTextCharFormat singleLineCommentFormatRetrate1;     //撤退格式，英文
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // LOGHIGHLIGHTER_H
