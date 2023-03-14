#pragma once
#include <vector>
#include <algorithm>
#include "../../Entities/TrenchCoat.h"
#include "DatabaseRepo.h"

class DatabaseMemoryRepo: public DatabaseRepo
{
private:
    std::vector<TrenchCoat> trenchCoats;

    void testAddToEnd();
    void testRemoveFromPos();
    void testUpdateOnPos();

public:

    DatabaseMemoryRepo() { this->generateEntities(); };

    /**
     * Generates 10 entities by adding them to the repository.
     */
    void generateEntities();

    /**
     * Adds a new entity to the end of the repository.
     * @param tc the TrenchCoat entity to add
     */
    void addToEnd(const TrenchCoat& tc) override;

    /**
     * Removes a new entity from a given position in the repo.
     * @param pos the position from which to remove the element
     *              0 <= pos < nr of elements in repo
     */
    void removeFromPos(int pos) override;

    /**
     * Implements the update of a repo element on a given position.
     * @param pos the position on which to update the element
     *              0 <= pos < nr of elements in repo
     * @param newDetails the TrenchCoat entity that contains the
 *                      updated version of the entity on position pos
     */
    void updateOnPos(int pos, const TrenchCoat& newDetails) override;

    /**
     * Returns the number of elements in the repository.
     */
    int getSize() override {return (int)trenchCoats.size();}

    /**
     * Returns the entity on position pos in the repository.
     */
    TrenchCoat& operator[](int pos) override {return this->trenchCoats[pos];}

    /**
     * Decreases the quantity of the trench coat located
     * on the given position.
     * @param pos valid position in the cart repo vector
     */
    void decreaseQuantity(int pos) override {this->trenchCoats[pos].decreaseQuantity();}

    /**
     * Returns the position at which the given trench coat
     * is found in the cart repository vector.
     * @param tc trench coat
     * @return valid position in the cart repo vector
     */
    int getPos(TrenchCoat& tc) override;

    /**
     * Returns the vector containing the elements of the repository.
     */
    std::vector<TrenchCoat> getRepo() override { return this->trenchCoats; }

    static void testDatabaseMemoryRepo();
};
