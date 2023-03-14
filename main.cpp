#include <QApplication>
#include "GUI/GUI.h"
#include "GUI/StartupSettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto *startupSettings = new StartupSettings;
    startupSettings->show();

    return QApplication::exec();
}
