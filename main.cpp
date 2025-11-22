#include "MainWindow.h"  // Исправлено: правильный регистр
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Parking Management System");
    QApplication::setApplicationVersion("2.0");
    QApplication::setOrganizationName("YourCompany");
    QApplication::setStyle("Fusion");
    MainWindow window;
    window.show();
    return QApplication::exec();
}
