#include <QApplication>
#include "mainwindow.h"
#include "styling.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Styling::apply(app);

    MainWindow window;
    window.show();

    return app.exec();
}