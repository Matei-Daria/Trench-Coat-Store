#pragma once
#include <string>
#include <utility>
#include <iostream>

class TrenchCoat
{
private:

    std::string size, color, photo;
    float price;
    int quantity;

public:
    /**
     * constructor
     */
    TrenchCoat(std::string size, std::string color, std::string photo, float price,
               int quantity);

    /**
     * default constructor
     */
    TrenchCoat();

    /**
     * copy constructor
     */
    TrenchCoat(const TrenchCoat& trenchCoat);

    /**
     * Operator "==" overloading.
     * Decides what makes two TrenchCoat entities identical
     * (they have the same size, color and photo link).
     * @param tc1 lhs operand
     * @param tc2 rhs operand
     * @return true - if they are identical, false - otherwise
     */
    friend bool operator==(const TrenchCoat& tc1, const TrenchCoat& tc2);

    /**
     * destructor
     */
    ~TrenchCoat();

    std::string getSize() {return this->size;}
    std::string getColor() {return this->color;}
    std::string getPhoto() {return this->photo;}
    float getPrice() const {return this->price;}
    int getQuantity() const {return this->quantity;}

    void setSize(std::string value) {this->size = std::move(value);}
    void setColor(std::string value) {this->color = std::move(value);}
    void setPhoto(std::string value) {this->photo = std::move(value);}
    void setPrice(float value) { this->price = value;}
    void setQuantity(int value) {this->quantity = value;}

    /**
     * Decreases by 1 the quantity of the trench coat.
     */
    void decreaseQuantity() {this->quantity--;}

    static void testTrenchCoat();

    friend std::istream& operator>>(std::istream& is, TrenchCoat& tc);
    friend std::ostream& operator<<(std::ostream& os, TrenchCoat& tc);

    [[nodiscard]] std::string to_string() const;
};