//
// Created by 86157 on 2026/4/1.
//

#ifndef CLIENT_FINDSUCCESSDLG_H
#define CLIENT_FINDSUCCESSDLG_H

#include <QDialog>
#include <memory>
#include "userdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class FindSuccessDlg; }
QT_END_NAMESPACE

class FindSuccessDlg : public QDialog {
Q_OBJECT

public:
    explicit FindSuccessDlg(QWidget *parent = nullptr);
    ~FindSuccessDlg() override;
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);

private:
    Ui::FindSuccessDlg *ui;
    std::shared_ptr<SearchInfo>_si;
    QWidget* _parent;

private slots:
    void on_add_friend_btn_clicked();
};


#endif //CLIENT_FINDSUCCESSDLG_H
