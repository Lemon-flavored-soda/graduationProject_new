//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_CLICKEDLABEL2_H
#define CLIENT_CLICKEDLABEL2_H

#include <QLabel>
#include "global.h"

class ClickedLabel2:public QLabel
{
Q_OBJECT
public:
    ClickedLabel2(QWidget* parent);
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void SetState(QString normal="", QString hover="", QString press="",
                  QString select="", QString select_hover="", QString select_press="");

    ClickLbState GetCurState();
    bool SetCurState(ClickLbState state);
    void ResetNormalState();
protected:

private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;

    QString _selected;
    QString _selected_hover;
    QString _selected_press;

    ClickLbState _curstate;
signals:
    void clicked(QString, ClickLbState);

};


#endif //CLIENT_CLICKEDLABEL2_H
