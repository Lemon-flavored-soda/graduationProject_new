//
// Created by 86157 on 2026/3/20.
//

#include "../Headers/Toast.h"

#include <QPainter>
#include <QScreen>
#include <QGuiApplication>

Toast::Toast(QWidget *parent) : QWidget(parent) {
    // 1. 设置窗口属性：无边框、工具窗口（不在任务栏显示）、置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明
    setAttribute(Qt::WA_ShowWithoutActivating); // 显示时不激活窗口（不抢焦点）

    // 2. 布局和内容
    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setText("请求超时");
    m_label->setStyleSheet(
            "QLabel {"
            "   color: #6069F0;"          // 文字颜色
            "   font-size: 14px;"         // 字体大小
            "   font-weight: bold;"       // 加粗
            "   padding: 10px 20px;"      // 内边距
            "   background-color: rgba(255, 255, 255, 0.9);" // 白色背景
            "   border-radius: 8px;"      // 圆角
            "}"
    );

    // 3. 添加阴影效果 (让卡片浮起来)
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(15);
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(0, 2);
    m_label->setGraphicsEffect(shadow);

    // 4. 布局管理器
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->setContentsMargins(10, 10, 10, 10); // 留出阴影的空间

    // 5. 动画设置
    m_fadeIn = new QPropertyAnimation(this, "windowOpacity");
    m_fadeIn->setDuration(300);
    m_fadeIn->setStartValue(0.0);
    m_fadeIn->setEndValue(1.0);

    m_fadeOut = new QPropertyAnimation(this, "windowOpacity");
    m_fadeOut->setDuration(300);
    m_fadeOut->setStartValue(1.0);
    m_fadeOut->setEndValue(0.0);

    // 连接动画结束信号
    connect(m_fadeOut, &QPropertyAnimation::finished, this, &QWidget::close);
    connect(m_fadeOut, &QPropertyAnimation::finished, this, &QObject::deleteLater);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_fadeOut->start();
    });
}

void Toast::paintEvent(QPaintEvent *event) {
    // 如果需要更复杂的自定义绘制（比如画那个红色的感叹号图标），可以在这里写
    // 目前我们直接用 QLabel 显示文字，如果需要图标，可以在 QLabel 里 setPixmap
    QWidget::paintEvent(event);
}

void Toast::showMessage(QWidget *parent, const QString &message, int duration) {
    Toast *toast = new Toast(parent);
    toast->m_label->setText(message);

    // --- 关键：计算位置，使其居中于父窗口顶部 ---
    toast->adjustSize(); // 根据内容调整大小

    QPoint pos;
    if (parent) {
        // 相对于父窗口居中
        pos = parent->mapToGlobal(QPoint(
                (parent->width() - toast->width()) / 2,
                50 // 距离顶部 50 像素
        ));
    } else {
        // 如果没有父窗口，相对于屏幕居中
        QScreen *screen = QGuiApplication::primaryScreen();
        pos = QPoint(
                (screen->geometry().width() - toast->width()) / 2,
                100
        );
    }

    toast->move(pos);
    toast->show();

    // 启动动画和计时器
    toast->m_fadeIn->start();
    toast->m_timer->start(duration);
}