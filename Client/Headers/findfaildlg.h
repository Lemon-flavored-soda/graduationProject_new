//
// Created by 86157 on 2026/4/3.
//

#ifndef CLIENT_FINDFAILDLG_H
#define CLIENT_FINDFAILDLG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class FindFailDlg; }
QT_END_NAMESPACE

class FindFailDlg : public QDialog {
Q_OBJECT

public:
    explicit FindFailDlg(QWidget *parent = nullptr);

    ~FindFailDlg() override;

private slots:
    void on_fail_sure_btn_clicked();

private:
    Ui::FindFailDlg *ui;
};


#endif //CLIENT_FINDFAILDLG_H
