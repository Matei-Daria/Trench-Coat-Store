#include <qlistwidget.h>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QDebug>
#include <windows.h>
#include <algorithm>
#include <QDesktopServices>
#include <QMessageBox>
#include <fstream>
#include <QShortcut>
#include <QTableView>
#include "GUI.h"
#include "CartModel.h"

GUI::GUI(DatabaseService& databaseServ, CartService &cartServ) :
databaseService(databaseServ), cartService(cartServ)
{
    this->setWindowTitle("Proper Trench Coats Store");

    this->modeTabs = new QTabWidget;
    this->mainLayout = new QVBoxLayout{this};
    this->mainLayout->addWidget(this->modeTabs);

    this->createAdmin();
    this->createUser();
    this->connectSignalsAndSlots();
    this->populateAdminList();

}

void GUI::createAdmin()
{
    this->adminWidget = new QWidget;
    this->adminLayout = new QVBoxLayout(this->adminWidget);
    this->modeTabs->addTab(adminWidget, "Admin");

    this->createAdminList();
    this->createAdminForm();
    this->createAdminActions();
    this->createUndoRedo();
}

void GUI::createAdminList()
{
    auto *tcListLabel = new QLabel{"Trench coats database"};
    QFont f;
    f.setPointSize(12);
    tcListLabel->setFont(f);
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::darkGreen);
    tcListLabel->setPalette(p);
    this->adminLayout->addWidget(tcListLabel);

    this->adminList = new QListWidget();

    this->adminLayout->addWidget(this->adminList);
}

void GUI::createAdminForm()
{
    auto *formWidget = new QWidget;
    auto *formLayout = new QFormLayout{};

    this->sizeTextBox = new QLineEdit{};
    auto *sizeLabel = new QLabel{"&Size:"};
    sizeLabel->setBuddy(this->sizeTextBox);

    this->colorTextBox = new QLineEdit{};
    auto *colorLabel = new QLabel{"&Color:"};
    colorLabel->setBuddy(this->colorTextBox);

    this->photoTextBox = new QLineEdit{};
    auto *photoLabel = new QLabel{"&Photo:"};
    photoLabel->setBuddy(this->photoTextBox);

    this->priceTextBox = new QLineEdit{};
    auto *priceLabel = new QLabel{"&Price:"};
    priceLabel->setBuddy(this->priceTextBox);

    this->quantityTextBox = new QLineEdit{};
    auto *quantityLabel = new QLabel{"&Quantity:"};
    quantityLabel->setBuddy(this->quantityTextBox);

    formLayout->addRow(sizeLabel, this->sizeTextBox);
    formLayout->addRow(colorLabel, this->colorTextBox);
    formLayout->addRow(photoLabel, this->photoTextBox);
    formLayout->addRow(priceLabel, this->priceTextBox);
    formLayout->addRow(quantityLabel, this->quantityTextBox);

    formWidget->setLayout(formLayout);

    this->adminLayout->addWidget(formWidget);
}

void GUI::createAdminActions()
{
    auto *actionsWidget = new QWidget;
    auto *actionsLayout = new QHBoxLayout{};

    this->addButton = new QPushButton("Add");
    this->addButton->setToolTip("Add a trench coat. All fields must be filled.");
    actionsLayout->addWidget(this->addButton);

    this->deleteButton = new QPushButton("Delete");
    this->deleteButton->setToolTip("Delete the selected trench coat.");
    actionsLayout->addWidget(this->deleteButton);

    this->updateButton = new QPushButton("Update");
    this->updateButton->setToolTip(
            "Update a trench coat. Leave field empty if\nthat information is to remain unchanged.");
    actionsLayout->addWidget(this->updateButton);

    actionsWidget->setLayout(actionsLayout);
    this->adminLayout->addWidget(actionsWidget);
}

void GUI::createUser()
{
    this->userWidget = new QWidget;
    this->userLayout = new QVBoxLayout{this->userWidget};
    this->modeTabs->addTab(this->userWidget, "User");
    this->cartModel = new CartModel(this->cartService);

    this->createUserForm();
    this->createUser1by1List();
    this->createUserActions();
    this->createUserCartList();
}

void GUI::createUserForm()
{
    auto *buyLabel = new QLabel("Buy Trench Coats");
    QFont f;
    f.setPointSize(12);
    buyLabel->setFont(f);
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::darkGreen);
    buyLabel->setPalette(p);
    this->userLayout->addWidget(buyLabel);

    auto *formAndButtonWidget = new QWidget;
    auto *formWidget = new QWidget;
    auto *formAndButtonLayout = new QHBoxLayout{};
    auto *formLayout = new QFormLayout{};

    this->filterSizeTextBox = new QLineEdit{};
    auto *filterSizeLabel = new QLabel{"&Enter a clothing size:"};
    filterSizeLabel->setBuddy(this->filterSizeTextBox);

    formLayout->addRow(filterSizeLabel, this->filterSizeTextBox);
    formWidget->setLayout(formLayout);
    formAndButtonLayout->addWidget(formWidget);
    this->searchButton = new QPushButton("Search");
    formAndButtonLayout->addWidget(this->searchButton);
    formAndButtonWidget->setLayout(formAndButtonLayout);
    this->userLayout->addWidget(formAndButtonWidget);
}

void GUI::createUser1by1List()
{
    this->currentTCInfo = new QListWidget;
    this->currentTCInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->currentTCInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    this->userLayout->addWidget(this->currentTCInfo);
}

void GUI::createUserActions()
{
    auto *actionsWidget = new QWidget;
    auto *actionsLayout = new QHBoxLayout{};

    this->buyButton = new QPushButton("Buy");
    actionsLayout->addWidget(this->buyButton);
    this->viewPhotoButton = new QPushButton("View photo");
    actionsLayout->addWidget(this->viewPhotoButton);
    this->nextButton = new QPushButton("Next");
    actionsLayout->addWidget(this->nextButton);
    actionsWidget->setLayout(actionsLayout);
    this->userLayout->addWidget(actionsWidget);
}

void GUI::createUserCartList()
{
    auto *cartListLabel = new QLabel("Shopping cart");
    QFont f;
    f.setPointSize(12);
    cartListLabel->setFont(f);
    QPalette p;
    p.setColor(QPalette::WindowText, Qt::darkGreen);
    cartListLabel->setPalette(p);
    this->userLayout->addWidget(cartListLabel);
    this->cartList = new QListWidget;
    this->userLayout->addWidget(this->cartList);

    auto *cartOptionsWidget = new QWidget;
    auto *cartOptionsLayout = new QHBoxLayout(cartOptionsWidget);
    auto *cartTotalLabel = new QLabel("Total amount:");
    this->totalAmountWidget = new QLineEdit;
    this->totalAmountWidget->setText(QString(QString::fromStdString(std::to_string(this->cartService.getTotalAmount()))));
    cartOptionsLayout->addWidget(cartTotalLabel);
    cartOptionsLayout->addWidget(this->totalAmountWidget);

    this->viewCartButton = new QPushButton("View cart in the\nchosen format");
    cartOptionsLayout->addWidget(this->viewCartButton);
    this->cartTableViewButton = new QPushButton("View cart in\ntable form");
    cartOptionsLayout->addWidget(this->cartTableViewButton);
    this->userLayout->addWidget(cartOptionsWidget);
}

void GUI::populateAdminList()
{
    if (this->adminList->count() > 0)
        this->adminList->clear();
    std::vector<TrenchCoat> temp = this->databaseService.getRepoVector();
    for (TrenchCoat &tc: temp)
    {
        QString tcStr = QString::fromStdString(tc.to_string());
        auto *item = new QListWidgetItem(tcStr, this->adminList);
        this->adminList->addItem(item);
    }
    if (this->adminList->count() > 0)
        this->adminList->setCurrentRow(0);
}

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this, &GUI::databaseUpdatedSignal, this, &GUI::populateAdminList);
    QObject::connect(this->adminList, &QListWidget::itemSelectionChanged, this, [this]()
    { this->listItemChanged(); });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addTCButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteTCButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateTCButtonHandler);

    QObject::connect(this, &GUI::addTCSignal, this, &GUI::addTC);
    QObject::connect(this, &GUI::deleteTCSignal, this, &GUI::deleteTC);
    QObject::connect(this, &GUI::updateTCSignal, this, &GUI::updateTC);

    QObject::connect(this->searchButton, &QPushButton::clicked, this, &GUI::searchButtonHandler);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextButtonHandler);
    QObject::connect(this->viewPhotoButton, &QPushButton::clicked, this, &GUI::viewPhotoButtonHandler);
    QObject::connect(this->buyButton, &QPushButton::clicked, this, &GUI::buyButtonHandler);
    QObject::connect(this->viewCartButton, &QPushButton::clicked, this, &GUI::viewCartButtonHandler);
    QObject::connect(this->cartTableViewButton, &QPushButton::clicked, this, &GUI::cartTableViewButtonHandler);

    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoHandler);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoHandler);
    QObject::connect(this->ctrlZ, &QShortcut::activated, this, &GUI::undoHandler);
    QObject::connect(this->ctrlY, &QShortcut::activated, this, &GUI::redoHandler);
}

void GUI::addTCButtonHandler()
{
    QString size = this->sizeTextBox->text();
    QString color = this->colorTextBox->text();
    QString photo = this->photoTextBox->text();
    QString price = this->priceTextBox->text();
    QString quantity = this->quantityTextBox->text();

    try
    {
        Validator::validateNewTrenchCoat(price.toStdString(), quantity.toStdString());
        TrenchCoat tc(size.toStdString(), color.toStdString(),
                      photo.toStdString(), price.toFloat(), quantity.toInt());
        Validator::validateAddIdenticalTC(this->databaseService.getRepoVector(), tc);
        emit addTCSignal(size.toStdString(), color.toStdString(),
                         photo.toStdString(), price.toFloat(), quantity.toInt());
    }
    catch( TrenchCoatError &tce)
    {
        QMessageBox::critical(this, "Error", tce.what());
    }
    catch( DatabaseRepoError &dre)
    {
        QMessageBox::critical(this, "Error", dre.what());
    }
}

void GUI::deleteTCButtonHandler()
{
    int index = getSelectedIndex();

    if (index < 0 || index >= this->databaseService.getSize())
        return;

    try
    {
        Validator::validateDeleteTC(this->databaseService.getOnPos(index));
        emit deleteTCSignal(index);
    }
    catch (TrenchCoatError &tce)
    {
        QMessageBox::critical(this, "Error", tce.what());
    }
}

void GUI::updateTCButtonHandler()
{
    int index = getSelectedIndex();

    if (index < 0 || index >= this->databaseService.getSize())
        return;

    QString size = this->sizeTextBox->text();
    QString color = this->colorTextBox->text();
    QString photo = this->photoTextBox->text();
    QString price = this->priceTextBox->text();
    QString quantity = this->quantityTextBox->text();

    try
    {
        Validator::validateNewTrenchCoat(price.toStdString(), quantity.toStdString());

        emit updateTCSignal(index, size.toStdString(), color.toStdString(),
                            photo.toStdString(), price.toStdString(), quantity.toStdString());
    }
    catch( DatabaseRepoError &dre)
    {
        QMessageBox::critical(this, "Error", dre.what());
    }
}

void GUI::addTC(const std::string &size, const std::string &color, const std::string &photo, float price, int quantity)
{
    this->databaseService.addTC(size, color, photo, price, quantity);

    emit databaseUpdatedSignal();
}

void GUI::deleteTC(int pos)
{
    this->databaseService.removeTC(pos);

    emit databaseUpdatedSignal();
}

void GUI::updateTC(int pos, const std::string &size, const std::string &color,
                   const std::string &photo, std::string price, std::string quantity)
{
    this->databaseService.updateTC(pos, size, color, photo, price, quantity);

    emit databaseUpdatedSignal();
}

int GUI::getSelectedIndex()
{
    if (this->adminList->count() == 0)
        return -1;

    QModelIndexList index = this->adminList->selectionModel()->selectedIndexes();
    if (index.size() == 0)
    {
        this->sizeTextBox->clear();
        this->colorTextBox->clear();
        this->photoTextBox->clear();
        this->priceTextBox->clear();
        this->quantityTextBox->clear();
        return -1;
    }

    int i = index.at(0).row();
    return i;
}

void GUI::listItemChanged()
{
    int index = getSelectedIndex();
    if (index == -1)
        return;

    if (index > this->databaseService.getSize())
        return;

    TrenchCoat tc = this->databaseService.getOnPos(index);

    this->sizeTextBox->setText(QString::fromStdString(tc.getSize()));
    this->colorTextBox->setText(QString::fromStdString(tc.getColor()));
    this->photoTextBox->setText(QString::fromStdString(tc.getPhoto()));
    this->priceTextBox->setText(QString::fromStdString(std::to_string(tc.getPrice())));
    this->quantityTextBox->setText(QString::fromStdString(std::to_string(tc.getQuantity())));
}

void GUI::populateUserList(std::string size)
{
    if (this->currentTCInfo->count() > 0)
        this->currentTCInfo->clear();
    this->filtered = this->databaseService.getAllWithSize(size);
    for (TrenchCoat &tc: this->filtered)
    {
        std::string info = "Size: " + tc.getSize() + "\nColor: " + tc.getColor() + "\nPhoto: "
                           + tc.getPhoto() + "\nPrice: " + std::to_string(tc.getPrice()) + "\n\n";
        QString qStringInfo = QString::fromStdString(info);
        auto *item = new QListWidgetItem(qStringInfo);
        this->currentTCInfo->addItem(item);
    }
    if (this->currentTCInfo->count() > 0)
        this->currentTCInfo->setCurrentRow(0);
}

void GUI::searchButtonHandler()
{
    QString size = this->filterSizeTextBox->text();
    this->populateUserList(size.toStdString());
}

void GUI::nextButtonHandler()
{
    if (this->currentTCInfo->currentRow() == this->filtered.size() - 1)
        this->currentTCInfo->setCurrentRow(0);
    else
        this->currentTCInfo->setCurrentRow(this->currentTCInfo->currentRow() + 1);
}

void GUI::viewPhotoButtonHandler()
{
    if (this->currentTCInfo->count() == 0)
        return;

    int i = this->currentTCInfo->currentRow();
    std::string link = this->filtered[i].getPhoto();
    QDesktopServices::openUrl(QUrl(link.c_str(), QUrl::TolerantMode));
}

void GUI::buyButtonHandler()
{
    if (this->currentTCInfo->count() == 0)
        return;
    try
    {
        int i = this->currentTCInfo->currentRow();
        TrenchCoat tc = this->filtered[i];
        Validator::validateBuyTC(tc);
        this->cartService.addToEnd(tc);
        this->cartModel->addTC(tc);
        this->databaseService.decreaseQuantity(this->databaseService.getPos(tc));
        QString tcStr = QString::fromStdString(tc.to_string());
        auto *item = new QListWidgetItem(tcStr, this->cartList);
        this->cartList->addItem(item);
        this->totalAmountWidget->setText(QString::fromStdString(std::to_string(this->cartService.getTotalAmount())));
    }
    catch( CartRepoError &cre)
    {
        QMessageBox::critical(this, "Error", cre.what());
    }
}

void GUI::viewCartButtonHandler()
{
    std::string file = this->cartService.getRepoFilename();
    file.erase(0, 2);
    std::string filePath = "file:///C:/Users/Daria/Documents/GitHub/a14-914-Matei-Daria-Maria/" + file;
    QDesktopServices::openUrl(QUrl(filePath.c_str(), QUrl::TolerantMode));
}

void GUI::createUndoRedo()
{
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");

    auto* undoRedoLayout = new QHBoxLayout();
    auto* undoRedoWidget = new QWidget();
    undoRedoLayout->addWidget(this->undoButton);
    undoRedoLayout->addWidget(this->redoButton);
    undoRedoWidget->setLayout(undoRedoLayout);
    this->adminLayout->addWidget(undoRedoWidget);

    this->ctrlZ = new QShortcut(this);
    this->ctrlZ->setKey(QKeySequence(tr("Ctrl+Z")));
    this->ctrlY = new QShortcut(this);
    this->ctrlY->setKey(QKeySequence(tr("Ctrl+Y")));
}

void GUI::undoHandler()
{
    try
    {
        this->databaseService.undo();
    }
    catch (DatabaseRepoError& dre)
    {
        QMessageBox::critical(this, "Error", dre.what());
    }

    emit databaseUpdatedSignal();
}

void GUI::redoHandler()
{
    try
    {
        this->databaseService.redo();
    }
    catch (DatabaseRepoError& dre)
    {
        QMessageBox::critical(this, "Error", dre.what());
    }

    emit databaseUpdatedSignal();
}

void GUI::cartTableViewButtonHandler()
{
    auto* tableViewWindow = new QWidget;
    auto* tableView = new QTableView;
    tableView->setModel(this->cartModel);
    auto* tableViewLayout = new QVBoxLayout(tableViewWindow);
    tableViewLayout->addWidget(tableView);
    tableViewWindow->setLayout(tableViewLayout);
    tableViewWindow->setMinimumWidth(tableView->width());
    tableViewWindow->setMinimumHeight(tableView->height() / 2);
    tableViewWindow->show();
}
