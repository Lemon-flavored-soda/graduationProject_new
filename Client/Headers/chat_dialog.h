//
// Created by 86157 on 2026/3/27.
//

#ifndef CLIENT_CHAT_DIALOG_H
#define CLIENT_CHAT_DIALOG_H

#include <QDialog>
#include "global.h"
#include "StateWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChatDialog; }
QT_END_NAMESPACE

class ChatDialog : public QDialog {
Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog() override;
    void addChatUserList();
    void ClearLabelState(StateWidget* lb);
protected:
    bool eventFilter(QObject *, QEvent *) override;
    void handleGlobalMousePress(QMouseEvent* event);
private:
    void ShowSearch(bool bsearch = false);
    void AddLBGroup(StateWidget* lb);
    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool b_loading;
    QList<StateWidget*> _lb_list;
public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString& str);
};


#endif //CLIENT_CHAT_DIALOG_H
