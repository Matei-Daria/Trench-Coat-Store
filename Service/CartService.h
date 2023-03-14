#pragma once
#include "../Repo/CartRepo/CartMemoryRepo.h"

class CartService
{
private:
    CartRepo *repo;

    void testAddToEnd();
    void testGetOnPos();

public:
    explicit CartService(CartRepo *r);

    /**
     * Adds a trench coat to the cart repo by calling
     * the CartMemoryRepo method addToEnd. Increases the total
     * amount in the cart by the price of the newly
     * added trench coat.
     * @param tc trench coat
     * @return true if the trench coat has been successfully added
     * to the cart, false if the quantity of the given trench
     * is zero and it can't be bought
     */
    void addToEnd(const TrenchCoat &tc);

    /**
     * Returns the total amount of the products in the cart.
     */
    float getTotalAmount() { return this->repo->getTotalAmount(); }

    /**
     * Returns the number of elements in the repository.
     */
    auto getSize() const { return this->repo->getSize(); }

    /**
     * Returns the entity on position pos in the repository.
     */
    TrenchCoat& getOnPos(int pos) {return this->repo->operator[](pos);}

    /**
     * Modifies the total amount in the cart by adding the value
     * of the parameter.
     * @param amount float value, >=0
     */
    void increaseTotalAmount(float amount) { this->repo->increaseTotalAmount(amount); }

    /**
     * Returns the vector containing the elements of the repository.
     */
    std::vector<TrenchCoat> getRepoVector() { return this->repo->getRepo(); }

    CartRepo* getRepo() {return this->repo;}

    static void executeOpen(const std::string& exeString);

    void openFile();

    std::string getRepoFilename() { return this->repo->getFilename(); }

    static void testCartService();
};
