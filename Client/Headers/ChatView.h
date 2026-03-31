//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_CHATVIEW_H
#define CLIENT_CHATVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

class ChatView:public QWidget{
    Q_OBJECT
public:
    explicit ChatView(QWidget* parent = Q_NULLPTR);
    ~ChatView();
    void appendChatItem(QWidget* item);     //尾插
    void prependChatItem(QWidget* item);    //头插
    void insertChatItem(QWidget* before, QWidget* item);    //中间插
    void removeAllItem();
protected:
    bool eventFilter(QObject *o, QEvent *e) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onVScrollBarMoved(int min, int max);
private:
    QVBoxLayout *m_pVl;
    //滚动区域
    QScrollArea *m_pScrollArea;
    bool isAppended;
    void initStyleSheet();
};


#endif //CLIENT_CHATVIEW_H
