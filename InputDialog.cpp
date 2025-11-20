#include "InputDialog.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QKeyEvent>

InputDialog::InputDialog(const QString& title, const QString& label, InputType type, QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(true);

    setupUI(title, label, type);
}

void InputDialog::setupUI(const QString& title, const QString& label, InputType type)
{
    setFixedSize(500, 250); // Увеличиваем размер для лучшего отображения

    // Main frame with shadow
    auto mainFrame = new QFrame(this);
    mainFrame->setObjectName("mainFrame");
    mainFrame->setStyleSheet(
        "QFrame#mainFrame {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #34495e, stop:1 #2c3e50);"
        "  border-radius: 15px;"
        "  border: 2px solid #3498db;"
        "}"
        );

    // Add shadow effect
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(30);
    shadowEffect->setColor(QColor(0, 0, 0, 120));
    shadowEffect->setOffset(0, 10);
    mainFrame->setGraphicsEffect(shadowEffect);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->addWidget(mainFrame);

    auto frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setContentsMargins(35, 30, 35, 25);
    frameLayout->setSpacing(25);

    // Title
    auto titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  color: #ecf0f1;"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "  background: transparent;"
        "  padding: 5px;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(titleLabel);

    // Label
    auto descLabel = new QLabel(label);
    descLabel->setStyleSheet(
        "QLabel {"
        "  color: #bdc3c7;"
        "  font-size: 14px;"
        "  background: transparent;"
        "  padding: 5px;"
        "}"
        );
    descLabel->setWordWrap(true);
    frameLayout->addWidget(descLabel);

    // Input field based on type
    QString inputStyle =
        "QLineEdit, QSpinBox, QComboBox {"
        "  background: #1f2530;"
        "  color: #ecf0f1;"
        "  border: 2px solid #3498db;"
        "  border-radius: 10px;"
        "  padding: 12px 18px;"
        "  font-size: 14px;"
        "  selection-background-color: #3498db;"
        "  min-height: 25px;"
        "}"
        "QLineEdit:focus, QSpinBox:focus, QComboBox:focus {"
        "  border-color: #1abc9c;"
        "  background: #1a1f29;"
        "}"
        "QLineEdit::placeholder {"
        "  color: #7f8c8d;"
        "}"
        "QComboBox {"
        "  padding-right: 40px;"
        "}"
        "QComboBox::drop-down {"
        "  border: none;"
        "  width: 35px;"
        "  background: #3498db;"
        "  border-radius: 0 8px 8px 0;"
        "}"
        "QComboBox::down-arrow {"
        "  image: none;"
        "  border-left: 6px solid transparent;"
        "  border-right: 6px solid transparent;"
        "  border-top: 6px solid #ecf0f1;"
        "  width: 12px;"
        "  height: 8px;"
        "}"
        "QComboBox QAbstractItemView {"
        "  background: #2c3e50;"
        "  color: #ecf0f1;"
        "  border: 2px solid #3498db;"
        "  border-radius: 8px;"
        "  selection-background-color: #3498db;"
        "  outline: none;"
        "  padding: 5px;"
        "}"
        "QSpinBox::up-button, QSpinBox::down-button {"
        "  background: #3498db;"
        "  border: none;"
        "  border-radius: 4px;"
        "  width: 25px;"
        "  margin: 1px;"
        "}"
        "QSpinBox::up-button:hover, QSpinBox::down-button:hover {"
        "  background: #1abc9c;"
        "}"
        "QSpinBox::up-arrow, QSpinBox::down-arrow {"
        "  width: 8px;"
        "  height: 8px;"
        "}";

    switch (type) {
    case InputType::Text:
        textEdit = new QLineEdit();
        textEdit->setStyleSheet(inputStyle);
        textEdit->setPlaceholderText("Введите значение...");
        textEdit->setMinimumHeight(40);
        frameLayout->addWidget(textEdit);
        break;

    case InputType::Integer:
        spinBox = new QSpinBox();
        spinBox->setStyleSheet(inputStyle);
        spinBox->setRange(0, 1000);
        spinBox->setValue(25);
        spinBox->setSuffix(" мест");
        spinBox->setMinimumHeight(40);
        frameLayout->addWidget(spinBox);
        break;

    case InputType::ComboBox:
        comboBox = new QComboBox();
        comboBox->setStyleSheet(inputStyle);
        comboBox->setMinimumHeight(40);
        frameLayout->addWidget(comboBox);
        break;
    }

    frameLayout->addSpacing(10);

    // Buttons
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    btnOk = new QPushButton("✓ Подтвердить");
    btnCancel = new QPushButton("✗ Отмена");

    // Улучшенные стили кнопок
    btnOk->setStyleSheet(
        "QPushButton {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #27ae60, stop:1 #219a52);"
        "  color: white; font-weight: bold; border-radius: 10px; padding: 12px 25px;"
        "  font-size: 14px; border: 2px solid #27ae60; min-width: 130px;"
        "  min-height: 40px;"
        "}"
        "QPushButton:hover {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2ecc71, stop:1 #27ae60);"
        "  border: 2px solid #2ecc71;"
        "}"
        "QPushButton:pressed {"
        "  background: #219a52;"
        "  border: 2px solid #219a52;"
        "}"
        "QPushButton:focus {"
        "  outline: none;"
        "}"
        );

    btnCancel->setStyleSheet(
        "QPushButton {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e74c3c, stop:1 #c0392b);"
        "  color: white; font-weight: bold; border-radius: 10px; padding: 12px 25px;"
        "  font-size: 14px; border: 2px solid #e74c3c; min-width: 130px;"
        "  min-height: 40px;"
        "}"
        "QPushButton:hover {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ff6b6b, stop:1 #e74c3c);"
        "  border: 2px solid #ff6b6b;"
        "}"
        "QPushButton:pressed {"
        "  background: #c0392b;"
        "  border: 2px solid #c0392b;"
        "}"
        "QPushButton:focus {"
        "  outline: none;"
        "}"
        );

    connect(btnOk, &QPushButton::clicked, this, &InputDialog::onOkClicked);
    connect(btnCancel, &QPushButton::clicked, this, &InputDialog::onCancelClicked);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnCancel);
    buttonLayout->addWidget(btnOk);

    frameLayout->addLayout(buttonLayout);

    // Enter key support
    if (textEdit) {
        connect(textEdit, &QLineEdit::returnPressed, this, &InputDialog::onOkClicked);
        textEdit->setFocus();
    } else if (spinBox) {
        connect(spinBox, &QSpinBox::editingFinished, this, &InputDialog::onOkClicked);
        spinBox->setFocus();
    } else if (comboBox) {
        comboBox->setFocus();
    }
}

void InputDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);

    if (parentWidget()) {
        move(parentWidget()->mapToGlobal(parentWidget()->rect().center()) - rect().center());
    } else {
        const QScreen* screen = QApplication::primaryScreen();
        if (screen) {
            move(screen->geometry().center() - rect().center());
        }
    }

    // Fade in animation
    auto animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void InputDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(0, 0, 0, 150));
    QDialog::paintEvent(event);
}

void InputDialog::onOkClicked()
{
    accept();
}

void InputDialog::onCancelClicked()
{
    reject();
}

// Static convenience methods
QString InputDialog::getText(const QString& title, const QString& label, const QString& defaultValue, QWidget* parent)
{
    InputDialog dialog(title, label, InputType::Text, parent);
    if (dialog.textEdit) {
        dialog.textEdit->setText(defaultValue);
        dialog.textEdit->selectAll();
    }
    return dialog.exec() == QDialog::Accepted ? dialog.textValue() : QString();
}

int InputDialog::getInteger(const QString& title, const QString& label, int defaultValue, int min, int max, QWidget* parent)
{
    InputDialog dialog(title, label, InputType::Integer, parent);
    if (dialog.spinBox) {
        dialog.spinBox->setRange(min, max);
        dialog.spinBox->setValue(defaultValue);
    }
    return dialog.exec() == QDialog::Accepted ? dialog.intValue() : defaultValue;
}

QString InputDialog::getItem(const QString& title, const QString& label, const QStringList& items, int currentIndex, QWidget* parent)
{
    InputDialog dialog(title, label, InputType::ComboBox, parent);
    if (dialog.comboBox) {
        dialog.comboBox->addItems(items);
        dialog.comboBox->setCurrentIndex(currentIndex);
    }
    return dialog.exec() == QDialog::Accepted ? dialog.itemValue() : QString();
}
