//
// Created by 86157 on 2026/3/30.
//

#include "ChatView.h"
#include <QScrollBar>
#include <QTimer>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

ChatView::ChatView(QWidget *parent): QWidget(parent),isAppended(false) {
    //设置垂直布局
    QVBoxLayout* pMainLayout = new QVBoxLayout(this);
    pMainLayout->setContentsMargins(0,0,0,0);
    //设置滚动区域
    m_pScrollArea = new QScrollArea();
    //用于写QSS
    m_pScrollArea->setObjectName("chat_area");
    //将滚动区域加入垂直布局中
    pMainLayout->addWidget(m_pScrollArea);

    QWidget* w = new QWidget(this);
    w->setObjectName("chat_bg");
    //启用“自动填充背景”属性
    w->setAutoFillBackground(true);


    QVBoxLayout *pHLayout_1 = new QVBoxLayout();
    pHLayout_1->addWidget(new QWidget(),100000);
    w->setLayout(pHLayout_1);
    m_pScrollArea->setWidget(w);

    //关闭垂直滚动条
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //获取滚动条
    QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
    //当滚动的时候加载（区域变化）
    connect(pVScrollBar,&QScrollBar::rangeChanged,this,&ChatView::onVScrollBarMoved);

    //把垂直ScrollBar放到上边 而不是原来的并排
    QHBoxLayout *pHLayout_2 = new QHBoxLayout();
    pHLayout_2->addWidget(pVScrollBar, 0, Qt::AlignRight);
    pHLayout_2->setContentsMargins(0,0,0,0);
    m_pScrollArea->setLayout(pHLayout_2);
    pVScrollBar->setHidden(true);
    //让滚动区域的内容控件自动适应滚动区域的大小
    m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->installEventFilter(this);
    initStyleSheet();
}

void ChatView::onVScrollBarMoved(int min, int max) {
    if(isAppended){ //添加item可能调用多次
        QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
        //强制视图滚动到最底部。
        pVScrollBar->setSliderPosition(pVScrollBar->maximum());
        //500ms内可能调用多次
        QTimer::singleShot(500,[this](){
           isAppended = false;
        });
    }
}

void ChatView::initStyleSheet() {

}

//添加聊天元素
void ChatView::appendChatItem(QWidget *item) {
    QVBoxLayout *vl = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());
    //上方插入item，如果直接用 addWidget(item) 或插入到 count()，新消息会被放在占位符下面，导致新消息被挤到最底部看不见的地方，或者破坏占位符的“顶底”效果。
    vl->insertWidget(vl->count()-1, item);
    isAppended = true;
}

void ChatView::prependChatItem(QWidget *item) {

}

void ChatView::insertChatItem(QWidget *before, QWidget *item) {

}

bool ChatView::eventFilter(QObject *o, QEvent *e) {
    if(e->type() == QEvent::Enter && o == m_pScrollArea)
    {
        //设置滚动条何时隐藏
        m_pScrollArea->verticalScrollBar()->setHidden(m_pScrollArea->verticalScrollBar()->maximum() == 0);
    }
    else if(e->type() == QEvent::Leave && o == m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(true);
    }
    return QWidget::eventFilter(o, e);
}

void ChatView::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

ChatView::~ChatView() {

}

void ChatView::removeAllItem() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());
    int count = layout->count();
    for (int i = 0; i < count - 1; ++i) {
        QLayoutItem *item = layout->takeAt(0); // 始终从第一个控件开始删除
        if (item) {
            if (QWidget *widget = item->widget()) {
                delete widget;
            }
            delete item;
        }
    }
}

