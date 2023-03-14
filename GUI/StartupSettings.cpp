#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "StartupSettings.h"
#include "../Repo/DatabaseRepo/DatabaseFileRepo.h"
#include "../Repo/CartRepo/CartCSVRepo.h"
#include "../Service/DatabaseService.h"
#include "../Service/CartService.h"
#include "GUI.h"
#include "../Repo/CartRepo/CartHTMLRepo.h"

StartupSettings::StartupSettings()
{
    this->setWindowTitle("Proper Trench Coats Store");
    auto* mainLayout = new QVBoxLayout{this};
    auto* actionsWidget = new QWidget;
    auto* actionsLayout = new QHBoxLayout{actionsWidget};

    auto* welcome = new QLabel("Welcome to the Proper Trench Coats Store!");
    QFont f;
    f.setPointSize(12);
    welcome->setFont(f);
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::darkGreen);
    welcome->setPalette(p);

    mainLayout->addWidget(welcome);

    auto* message = new QLabel("Choose the format for the shopping cart: ");
    actionsLayout->addWidget(message);

    this->csvButton = new QPushButton("CSV");
    this->htmlButton = new QPushButton("HTML");
    actionsLayout->addWidget(this->csvButton);
    actionsLayout->addWidget(this->htmlButton);

    actionsWidget->setLayout(actionsLayout);
    mainLayout->addWidget(actionsWidget);

    QObject::connect(this->csvButton, &QPushButton::clicked, this, &StartupSettings::csvButtonHandler);
    QObject::connect(this->htmlButton, &QPushButton::clicked, this, &StartupSettings::htmlButtonHandler);
}

void StartupSettings::csvButtonHandler()
{
    this->choice = false;
    this->startMainApp();
}

void StartupSettings::htmlButtonHandler()
{
    this->choice = true;
    this->startMainApp();
}

void StartupSettings::startMainApp()
{
    DatabaseRepo* databaseRepo = new DatabaseFileRepo("../Files/database.txt");
    DatabaseService databaseService(databaseRepo);
    this->close();

    if (!this->choice)
    {
        CartRepo* cartRepo = new CartCSVRepo("../Files/cart.csv");
        CartService cartService(cartRepo);
        auto *gui = new GUI(databaseService, cartService);
        gui->show();
    }
    else
    {
        CartRepo* cartRepo = new CartHTMLRepo("../Files/cart.html");
        CartService cartService(cartRepo);
        auto *gui = new GUI(databaseService, cartService);
        gui->show();
    }
}
