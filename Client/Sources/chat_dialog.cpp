//
// Created by 86157 on 2026/3/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_chat_dialog.h" resolved

#include "chat_dialog.h"
#include "ui_chat_dialog.h"


ChatDialog::ChatDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::ChatDialog) {
    ui->setupUi(this);
}

ChatDialog::~ChatDialog() {
    delete ui;
}
