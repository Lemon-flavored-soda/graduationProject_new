//
// Created by 86157 on 2026/3/31.
//

#ifndef CLIENT_TEXTBUBBLE_H
#define CLIENT_TEXTBUBBLE_H


#include <QTextEdit>
#include "BubbleFrame.h"
#include <QHBoxLayout>
//文本气泡
class TextBubble : public BubbleFrame
{
Q_OBJECT
public:
    TextBubble(ChatRole role, const QString &text, QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *o, QEvent *e);
private:
    void adjustTextHeight();
    void setPlainText(const QString &text);
    void initStyleSheet();
private:
    QTextEdit *m_pTextEdit;
};

#endif //CLIENT_TEXTBUBBLE_H
