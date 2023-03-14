#pragma once
#include <exception>

class ValueError: public std::exception
{
private:
    const char* message;
public:
    explicit ValueError(const char* msg) : message(msg) {};
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};

class IndexError: public std::exception
{
private:
    const char* message;
public:
    explicit IndexError(const char* msg) : message(msg) {};;
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};

class TrenchCoatError: public std::exception
{
private:
    const char* message;
public:
    explicit TrenchCoatError(const char* msg) : message(msg) {};
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};

class DatabaseRepoError: public std::exception
{
private:
    const char* message;
public:
    explicit DatabaseRepoError(const char* msg): message(msg) {};
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};

class CartRepoError: public std::exception
{
private:
    const char* message;
public:
    explicit CartRepoError(const char* msg): message(msg) {};
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};

class FileError: public std::exception
{
private:
    const char* message;
public:
    explicit FileError(const char* msg): message(msg) {};
    [[nodiscard]] const char * what() const noexcept override { return this->message; };
};