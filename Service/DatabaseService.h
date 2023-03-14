#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include "../Repo/DatabaseRepo/DatabaseFileRepo.h"
#include "../Utilities/Validators.h"
#include "UndoRedo.h"

class DatabaseService
{
private:
    DatabaseRepo* repo;
    std::vector<std::shared_ptr<UndoAction>> undoActions;
    std::vector<std::shared_ptr<UndoAction>> redoActions;

    void testAddTC();
    void testRemoveTC();
    void testUpdateTC();
    void testValidFloat();
    void testValidInteger();

public:
    /**
     * constructor
     */
    explicit DatabaseService(DatabaseRepo* r);

    /**
     * Creates a new TrenchCoat entity.
     * Checks if the entity already exists in the repo and,
     * if it doesn't, adds it to the repo.
     * @param size string
     * @param color string
     * @param photo string
     * @param price float, >0
     * @param quantity integer, >=0
     * @return false - if an identical entity exists in the repo,
     *         true - otherwise, and the entity has been added to the repo
     */
    void addTC(const std::string &size, const std::string &color,
               const std::string &photo, float price, int quantity);

    /**
     * Removes an entity from the repository on a given position.
     * Checks if the position given as a parameter is a valid index
     * of the repository.
     * @param pos integer
     * @return false - if the position is not a valid index,
     *         true - otherwise and the trench coat has been removed
     */
    void removeTC(int pos);

    /**
     * Updates the trench coat at a given position in the repository
     * with the given new details.
     * Checks all new details against a predetermined value, as it indicates that
     * that detail is to remain unchanged in the update process.
     * So, if the value is 0, that particular detail is given the value of the
     * corresponding detail of the trench coat at the given position.
     * @param pos integer,  0 <= pos < nr of elements in repo
     * @param size string
     * @param color string
     * @param photo string
     * @param price string with valid float value, >0 or == "-"
     * @param quantity string with valid integer value, >=0 or == "-"
     */
    void updateTC(int pos, const std::string &size, const std::string &color,
                  const std::string &photo, std::string price, std::string quantity);

    /**
     * Returns the number of elements in the repository.
     */
    [[nodiscard]] auto getSize() const { return repo->getSize(); }

    /**
     * Returns the entity on position pos in the repository.
     */
    TrenchCoat getOnPos(int pos) {return this->repo->operator[](pos);}

    /***
     * Returns an entity of type DatabaseFileRepo containing all
     * trench coats in the current repo with a given size.
     * If the size is "-", the exact current repo is returned.
     * @param size string representing a size or "-"
     * @return an instance of DatabaseFileRepo (can be empty)
     */
    std::vector<TrenchCoat> getAllWithSize(const std::string& size);

    /**
     * Decreases the quantity of the trench coat located
     * on the given position.
     * @param pos valid position in the cart repo vector
     */
    void decreaseQuantity(int pos) {this->repo->decreaseQuantity(pos);}

    /**
     * Returns the position at which the given trench coat
     * is found in the cart repository vector.
     * @param tc trench coat
     * @return valid position in the cart repo vector
     */
    int getPos(TrenchCoat& tc) {return this->repo->getPos(tc);}

    /**
     * Returns the vector containing the elements of the repository.
     */
    std::vector<TrenchCoat> getRepoVector() { return this->repo->getRepo(); }

    DatabaseRepo* getRepo() { return this->repo; }

    void undo();

    void redo();

    static void testDatabaseService();
};