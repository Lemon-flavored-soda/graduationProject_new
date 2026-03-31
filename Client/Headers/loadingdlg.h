//
// Created by 86157 on 2026/3/30.
//

#ifndef CLIENT_LOADINGDLG_H
#define CLIENT_LOADINGDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LoadingDlg; }
QT_END_NAMESPACE

class LoadingDlg : public QDialog {
Q_OBJECT

public:
    explicit LoadingDlg(QWidget *parent = nullptr);

    ~LoadingDlg() override;

private:
    Ui::LoadingDlg *ui;
};


#endif //CLIENT_LOADINGDLG_H
