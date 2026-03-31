//
// Created by 86157 on 2026/3/31.
//

#ifndef CLIENT_PICTUREBUBBLE_H
#define CLIENT_PICTUREBUBBLE_H


#include "BubbleFrame.h"
#include <QHBoxLayout>
#include <QPixmap>
class PictureBubble : public BubbleFrame
{
Q_OBJECT
public:
    PictureBubble(const QPixmap &picture, ChatRole role, QWidget *parent = nullptr);
};


#endif //CLIENT_PICTUREBUBBLE_H
