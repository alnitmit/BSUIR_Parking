#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>  // Добавляем этот include

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    enum InputType {
        Text,
        Integer,
        ComboBox
    };

    explicit InputDialog(const QString& title, const QString& label, InputType type = Text,
                         QWidget* parent = nullptr);

    static QString getText(const QString& title, const QString& label, const QString& defaultValue = "",
                           QWidget* parent = nullptr);
    static int getInteger(const QString& title, const QString& label, int defaultValue = 0,
                          int min = 0, int max = 100, QWidget* parent = nullptr);
    static QString getItem(const QString& title, const QString& label, const QStringList& items,
                           int currentIndex = 0, QWidget* parent = nullptr);

    QString textValue() const { return textEdit ? textEdit->text() : QString(); }
    int intValue() const { return spinBox ? spinBox->value() : 0; }
    QString itemValue() const { return comboBox ? comboBox->currentText() : QString(); }

protected:
    void showEvent(QShowEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI(const QString& title, const QString& label, InputType type);

    QLineEdit* textEdit;
    QSpinBox* spinBox;
    QComboBox* comboBox;
    QPushButton* btnOk;
    QPushButton* btnCancel;
};

#endif // INPUTDIALOG_H
