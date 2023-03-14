#include "qwidget.h"
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QShortcut>
#include "../Service/CartService.h"
#include "../Service/DatabaseService.h"
#include "CartModel.h"

class GUI : public QWidget
{
    Q_OBJECT
private:
    DatabaseService databaseService;
    CartService cartService;

    std::vector<TrenchCoat> filtered;
    QLayout *mainLayout;
    QTabWidget *modeTabs;
    QWidget *adminWidget;
    QLayout *adminLayout;
    QWidget *userWidget;
    QLayout *userLayout;
    QListWidget *adminList;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QLineEdit *sizeTextBox;
    QLineEdit *colorTextBox;
    QLineEdit *photoTextBox;
    QLineEdit *priceTextBox;
    QLineEdit *quantityTextBox;
    QLineEdit *filterSizeTextBox;
    QPushButton* searchButton;
    QListWidget* currentTCInfo;
    QPushButton* nextButton;
    QPushButton* viewPhotoButton;
    QPushButton* buyButton;
    QListWidget* cartList;
    QLineEdit* totalAmountWidget;
    QPushButton* viewCartButton;
    QPushButton* undoButton, *redoButton;
    QShortcut* ctrlZ, *ctrlY;
    QPushButton* cartTableViewButton;
    CartModel* cartModel;

    void createAdmin();
    void createAdminList();
    void createAdminForm();
    void createAdminActions();
    void createUser();
    void createUserForm();
    void createUser1by1List();
    void createUserActions();
    void createUserCartList();
    void populateAdminList();
    void connectSignalsAndSlots();
    int getSelectedIndex();
    void listItemChanged();
    void populateUserList(std::string size);
    void createUndoRedo();

public:
    GUI(DatabaseService& databaseService, CartService& cartService);

signals:
    void databaseUpdatedSignal();
    void addTCSignal(const std::string &size, const std::string &color,
                   const std::string &photo, float price, int quantity);
    void deleteTCSignal(int pos);
    void updateTCSignal(int pos, const std::string &size, const std::string &color,
                        const std::string &photo, std::string price, std::string quantity);

public slots:
    void addTCButtonHandler();
    void deleteTCButtonHandler();
    void updateTCButtonHandler();
    void addTC(const std::string &size, const std::string &color,
               const std::string &photo, float price, int quantity);
    void deleteTC(int pos);
    void updateTC(int pos, const std::string &size, const std::string &color,
                  const std::string &photo, std::string price, std::string quantity);
    void searchButtonHandler();
    void nextButtonHandler();
    void viewPhotoButtonHandler();
    void buyButtonHandler();
    void viewCartButtonHandler();
    void cartTableViewButtonHandler();
    void undoHandler();
    void redoHandler();
};