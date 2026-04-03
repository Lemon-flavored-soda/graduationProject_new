//
// Created by 86157 on 2026/4/1.
//

#ifndef CLIENT_CLICKEDONCELABEL_H
#define CLIENT_CLICKEDONCELABEL_H
#include <QLabel>
#include <QMouseEvent>

class ClickedOnceLabel : public QLabel{
    Q_OBJECT
public:
    explicit ClickedOnceLabel(QWidget* parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *ev) override;
signals:
    void clicked(QString);
};


#endif //CLIENT_CLICKEDONCELABEL_H
