//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_CLICKEDBTN2_H
#define CLIENT_CLICKEDBTN2_H

#include <QPushButton>

class ClickedBtn2:public QPushButton{
        Q_OBJECT
        public:
    ClickedBtn2(QWidget *parent = nullptr);
        ~ClickedBtn2();
        void SetState(QString nomal, QString hover, QString press);
        protected:
    void enterEvent(QEnterEvent *event) override;// 鼠标进入
        virtual void leaveEvent(QEvent *event) override; // 鼠标离开
        virtual void mousePressEvent(QMouseEvent *event) override; // 鼠标按下
        virtual void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放
        private:
        QString _normal;
        QString _hover;
        QString _press;
    };


#endif //CLIENT_CLICKEDBTN2_H
