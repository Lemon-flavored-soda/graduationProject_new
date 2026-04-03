//
// Created by 86157 on 2026/4/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FriendLabel.h" resolved

#include "friendlabel.h"
#include "ui_FriendLabel.h"
#include <QFontMetrics>


FriendLabel::FriendLabel(QWidget *parent) :
        QFrame(parent), ui(new Ui::FriendLabel) {
    ui->setupUi(this);
    ui->close_lb->SetState("normal","hover","pressed",
                           "selected_normal","selected_hover","selected_pressed");
    connect(ui->close_lb, &ClickedLabel2::clicked, this, &FriendLabel::slot_close);
}

void FriendLabel::SetText(QString text) {
    _text = text;
    ui->tip_lb->setText(_text);
    ui->tip_lb->adjustSize();

    QFontMetrics fontMetrics(ui->tip_lb->font()); // 获取QLabel控件的字体信息
    auto textWidth = fontMetrics.horizontalAdvance(ui->tip_lb->text()); // 获取文本的宽度
    auto textHeight = fontMetrics.height(); // 获取文本的高度

    qDebug()<< " ui->tip_lb.width() is " << ui->tip_lb->width();
    qDebug()<< " ui->close_lb->width() is " << ui->close_lb->width();
    qDebug()<< " textWidth is " << textWidth;
    this->setFixedWidth(ui->tip_lb->width()+ui->close_lb->width()+5);
    this->setFixedHeight(textHeight+4);
    qDebug()<< "  this->setFixedHeight " << this->height();
    _width = this->width();
    _height = this->height();
}

FriendLabel::~FriendLabel() {
    delete ui;
}

int FriendLabel::Width()
{
    return _width;
}

int FriendLabel::Height()
{
    return _height;
}

QString FriendLabel::Text()
{
    return _text;
}

void FriendLabel::slot_close()
{
    emit sig_close(_text);
}