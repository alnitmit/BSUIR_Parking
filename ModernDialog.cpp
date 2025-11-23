#include "ModernDialog.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QLinearGradient>

ModernDialog::ModernDialog(DialogType type, const QString& title, const QString& message, QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(true);
    setupUI(type, title, message);
}

void ModernDialog::setupUI(DialogType type, const QString& title, const QString& message)
{
    setFixedSize(400, 280);

    auto mainFrame = new QFrame(this);
    mainFrame->setObjectName("mainFrame");
    mainFrame->setStyleSheet(getStyleSheet(type));

    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(0, 5);
    mainFrame->setGraphicsEffect(shadowEffect);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(mainFrame);

    auto frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setContentsMargins(30, 30, 30, 25);
    frameLayout->setSpacing(20);

    auto headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(15);

    auto iconLabel = new QLabel();
    iconLabel->setText(getIcon(type));
    iconLabel->setStyleSheet("QLabel { font-size: 40px; background: transparent; }");
    iconLabel->setFixedSize(50, 50);

    auto titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("QLabel { color: white; font-size: 18px; font-weight: bold; background: transparent; }");
    titleLabel->setWordWrap(true);

    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(titleLabel);
    headerLayout->setStretchFactor(titleLabel, 1);
    frameLayout->addLayout(headerLayout);

    auto messageLabel = new QLabel(message);
    messageLabel->setStyleSheet("QLabel { color: rgba(255,255,255,0.9); font-size: 14px; line-height: 1.4; background: transparent; }");
    messageLabel->setWordWrap(true);
    messageLabel->setAlignment(Qt::AlignLeft);
    frameLayout->addWidget(messageLabel);

    frameLayout->addStretch();

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

    if (type == DialogType::Question) {
        btnYes = new QPushButton("✓ Да");
        btnNo = new QPushButton("✗ Нет");
        btnYes->setStyleSheet("QPushButton { background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #27ae60,stop:1 #219a52); color:white; font-weight:bold; border-radius:8px; padding:10px 20px; font-size:14px; border:none; min-width:80px; } QPushButton:hover{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2ecc71,stop:1 #27ae60);} QPushButton:pressed{background:#219a52;}");
        btnNo->setStyleSheet("QPushButton { background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #e74c3c,stop:1 #c0392b); color:white; font-weight:bold; border-radius:8px; padding:10px 20px; font-size:14px; border:none; min-width:80px; } QPushButton:hover{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #ff6b6b,stop:1 #e74c3c);} QPushButton:pressed{background:#c0392b;}");
        connect(btnYes, &QPushButton::clicked, this, &ModernDialog::onYesClicked);
        connect(btnNo, &QPushButton::clicked, this, &ModernDialog::onNoClicked);
        buttonLayout->addStretch();
        buttonLayout->addWidget(btnYes);
        buttonLayout->addWidget(btnNo);
    } else {
        btnOk = new QPushButton("OK");
        btnOk->setStyleSheet("QPushButton { background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #3498db,stop:1 #2980b9); color:white; font-weight:bold; border-radius:8px; padding:10px 30px; font-size:14px; border:none; min-width:100px; } QPushButton:hover{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #5dade2,stop:1 #3498db);} QPushButton:pressed{background:#2980b9;}");
        connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
        buttonLayout->addStretch();
        buttonLayout->addWidget(btnOk);
    }

    frameLayout->addLayout(buttonLayout);
}

QString ModernDialog::getIcon(DialogType type) const
{
    // Используем полные имена вместо using enum
    switch (type) {
    case DialogType::Info: return "💡";
    case DialogType::Success: return "✅";
    case DialogType::Warning: return "⚠️";
    case DialogType::Error: return "❌";
    case DialogType::Question: return "❓";
    default: return "💡";
    }
}

QString ModernDialog::getStyleSheet(DialogType type) const
{
    // Используем полные имена вместо using enum
    QString gradient;
    switch (type) {
    case DialogType::Info: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #3498db,stop:1 #2980b9)"; break;
    case DialogType::Success: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #27ae60,stop:1 #219a52)"; break;
    case DialogType::Warning: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #f39c12,stop:1 #e67e22)"; break;
    case DialogType::Error: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #e74c3c,stop:1 #c0392b)"; break;
    case DialogType::Question: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #9b59b6,stop:1 #8e44ad)"; break;
    default: gradient = "qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #3498db,stop:1 #2980b9)";
    }
    return QString("QFrame#mainFrame { background:%1; border-radius:15px; border:1px solid rgba(255,255,255,0.2);}").arg(gradient);
}

// Остальные методы без изменений...
void ModernDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    if (parentWidget()) {
        move(parentWidget()->mapToGlobal(parentWidget()->rect().center()) - rect().center());
    } else {
        const QScreen* screen = QApplication::primaryScreen();
        if (screen) move(screen->geometry().center() - rect().center());
    }

    auto animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void ModernDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(0,0,0,100));
    QDialog::paintEvent(event);
}

void ModernDialog::onYesClicked()
{
    result = true;
    accept();
}

void ModernDialog::onNoClicked()
{
    result = false;
    reject();
}

void ModernDialog::showInfo(const QString& title, const QString& message, QWidget* parent)
{
    ModernDialog dialog(DialogType::Info, title, message, parent);
    dialog.exec();
}

void ModernDialog::showSuccess(const QString& title, const QString& message, QWidget* parent)
{
    ModernDialog dialog(DialogType::Success, title, message, parent);
    dialog.exec();
}

void ModernDialog::showWarning(const QString& title, const QString& message, QWidget* parent)
{
    ModernDialog dialog(DialogType::Warning, title, message, parent);
    dialog.exec();
}

void ModernDialog::showError(const QString& title, const QString& message, QWidget* parent)
{
    ModernDialog dialog(DialogType::Error, title, message, parent);
    dialog.exec();
}

bool ModernDialog::showQuestion(const QString& title, const QString& message, QWidget* parent)
{
    ModernDialog dialog(DialogType::Question, title, message, parent);
    return dialog.exec() == QDialog::Accepted && dialog.result;
}
