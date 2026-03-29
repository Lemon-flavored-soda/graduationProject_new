//
// Created by 86157 on 2026/3/29.
//

#ifndef CLIENT_CUSTOMIZEEDIT_H
#define CLIENT_CUSTOMIZEEDIT_H

#include <QLineEdit>

class CustomizeEdit : public QLineEdit{
    Q_OBJECT
public:
    CustomizeEdit(QWidget* parent = nullptr);
    void SetMaxLength(int maxLen);
protected:
    void focusOutEvent(QFocusEvent *) override;
public slots:
    void limitTextLength(QString text);
private:
    int _max_len;
signals:
    void sig_focus_out();
};


#endif //CLIENT_CUSTOMIZEEDIT_H
