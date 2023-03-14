#pragma once

#include "../Entities/TrenchCoat.h"
#include "../Repo/DatabaseRepo/DatabaseRepo.h"

class UndoAction
{
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoAction() = default;
};

class UndoAdd: public UndoAction
{
private:
    DatabaseRepo& repo;
    TrenchCoat trenchCoat;

public:
    UndoAdd(DatabaseRepo& r, TrenchCoat& tc): repo(r), trenchCoat(tc) {}

    void undo() override { repo.removeFromPos(repo.getPos(trenchCoat)); }

    void redo() override { repo.addToEnd(trenchCoat); }
};

class UndoRemove: public UndoAction
{
private:
    DatabaseRepo& repo;
    TrenchCoat trenchCoat;

public:
    UndoRemove(DatabaseRepo& r, TrenchCoat& tc): repo(r), trenchCoat(tc) {}

    void undo() override { repo.addToEnd(trenchCoat); }

    void redo() override { repo.removeFromPos(repo.getPos(trenchCoat)); }
};

class UndoUpdate: public UndoAction
{
private:
    DatabaseRepo& repo;
    TrenchCoat oldTC, newTC;

public:
    UndoUpdate(DatabaseRepo& r, TrenchCoat& oldTC, TrenchCoat& newTC): repo(r), oldTC(oldTC), newTC(newTC) {}

    void undo() override { repo.updateOnPos(repo.getPos(newTC), oldTC); }

    void redo() override { repo.updateOnPos(repo.getPos(oldTC), newTC); }
};