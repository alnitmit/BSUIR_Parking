#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Parking Management System");
    app.setApplicationVersion("2.0");
    app.setOrganizationName("YourCompany");

    app.setStyle("Fusion");

    MainWindow window;
    window.show();

    return app.exec();
}
