#pragma once
#include "CartRepo.h"

class CartCSVRepo: public CartRepo
{
private:
    std::vector<TrenchCoat> cartItems;
    float totalAmount;
    std::string filename;

    void writeToCSV();

public:
    explicit CartCSVRepo(const std::string& file);

    /**
     * Adds a new entity to the end of the repository.
     * @param tc the TrenchCoat entity to add
     */
    void addToEnd(const TrenchCoat &tc) override;

    /**
     * Returns the total amount of the products in the cart.
     */
    float getTotalAmount() override { return this->totalAmount; }

    /**
     * Returns the number of elements in the repository.
     */
    int getSize() override {return (int)this->cartItems.size();}

    /**
     * Returns the entity on position pos in the repository.
     */
    TrenchCoat& operator[](int pos) override {return this->cartItems[pos];}

    /**
     * Modifies the total amount in the cart by adding the value
     * of the parameter.
     * @param amount float value, >=0
     */
    void increaseTotalAmount(float amount) override { this->totalAmount += amount; }

    /**
     * Returns the vector containing the elements of the repository.
     */
    std::vector<TrenchCoat> getRepo() override { return this->cartItems; }

    std::string getFilename() override { return this->filename; }
};