#ifndef MODERNDIALOG_H
#define MODERNDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

class ModernDialog : public QDialog
{
    Q_OBJECT

public:
    enum class DialogType {
        Info,
        Success,
        Warning,
        Error,
        Question
    };

    explicit ModernDialog(DialogType type, const QString& title, const QString& message,
                          QWidget* parent = nullptr);

    static void showInfo(const QString& title, const QString& message, QWidget* parent = nullptr);
    static void showSuccess(const QString& title, const QString& message, QWidget* parent = nullptr);
    static void showWarning(const QString& title, const QString& message, QWidget* parent = nullptr);
    static void showError(const QString& title, const QString& message, QWidget* parent = nullptr);
    static bool showQuestion(const QString& title, const QString& message, QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onYesClicked();
    void onNoClicked();

private:
    void setupUI(DialogType type, const QString& title, const QString& message);
    QString getIcon(DialogType type) const;
    QString getStyleSheet(DialogType type) const;

    QPushButton* btnYes = nullptr;
    QPushButton* btnNo = nullptr;
    QPushButton* btnOk = nullptr;
    bool result = false;
};

#endif
