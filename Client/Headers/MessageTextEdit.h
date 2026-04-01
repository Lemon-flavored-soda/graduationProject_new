//
// Created by 86157 on 2026/3/31.
//

#ifndef CLIENT_MESSAGETEXTEDIT_H
#define CLIENT_MESSAGETEXTEDIT_H
#include "global.h"
#include <QTextEdit>

class MessageTextEdit :public QTextEdit{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget* parent = nullptr);
    ~MessageTextEdit();
    QVector<MsgInfo> getMsgList();
    void insertFileFromUrl(const QStringList& urls);
signals:
    void send();
protected:
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
private:
    void insertImages(const QString &url);
    void insertTextFile(const QString &url);
    bool canInsertFromMimeData(const QMimeData *source)const;
    void insertFromMimeData(const QMimeData* source);

    bool isImage(QString url);//判断文件是否为图片
    void insertMsgList(QVector<MsgInfo> &list, QString flag, QString text, QPixmap pix);

    QStringList getUrl(QString text);
    QPixmap getFileIconPixmap(const QString& url);//获取文件图标及大小信息，并准化成图片
    QString getFileSize(qint64 size);//获取文件大小

    QVector<MsgInfo>mMsgList;
    QVector<MsgInfo>mGetMsgList;
private slots:
    void textEditChanged();

};


#endif //CLIENT_MESSAGETEXTEDIT_H
