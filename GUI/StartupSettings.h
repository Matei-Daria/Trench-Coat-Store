#pragma once

#include <QPushButton>

class StartupSettings: public QWidget
{
    Q_OBJECT
private:
    bool choice;
    QPushButton *csvButton;
    QPushButton *htmlButton;

public:
    StartupSettings();
    void csvButtonHandler();
    void htmlButtonHandler();
    void startMainApp();
};
