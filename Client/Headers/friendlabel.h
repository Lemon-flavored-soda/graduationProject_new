//
// Created by 86157 on 2026/4/1.
//

#ifndef CLIENT_FRIENDLABEL_H
#define CLIENT_FRIENDLABEL_H

#include <QWidget>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class FriendLabel; }
QT_END_NAMESPACE

class FriendLabel : public QFrame {
Q_OBJECT

public:
    explicit FriendLabel(QWidget *parent = nullptr);
    ~FriendLabel() override;
    void SetText(QString text);
    int Width();
    int Height();
    QString Text();
private:
    Ui::FriendLabel *ui;
    QString _text;
    int _width;
    int _height;
public slots:
    void slot_close();
signals:
    void sig_close(QString);
};


#endif //CLIENT_FRIENDLABEL_H
