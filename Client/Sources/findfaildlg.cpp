//
// Created by 86157 on 2026/4/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FindFailDlg.h" resolved

#include "findfaildlg.h"
#include "ui_FindFailDlg.h"


FindFailDlg::FindFailDlg(QWidget *parent) :
        QDialog(parent), ui(new Ui::FindFailDlg) {
    ui->setupUi(this);
    setWindowTitle("添加");
    //隐藏边框
//    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("FindFailDlg");
    ui->fail_sure_btn->SetState("normal", "hover", "press");
    this->setModal(true);
}

FindFailDlg::~FindFailDlg() {
    qDebug() << "Find FailDlg destruct";
    delete ui;
}

void FindFailDlg::on_fail_sure_btn_clicked() {
    this->hide();
}
