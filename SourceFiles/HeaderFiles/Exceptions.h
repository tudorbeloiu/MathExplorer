#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class PrimaryExceptions : public std::exception
{
protected:
    std::string errMsg;

public:
    PrimaryExceptions(const std::string &msg) : errMsg(msg) {}

    virtual const char *what() const noexcept override
    {
        return this->errMsg.c_str(); // what function returns a const char*
    }
};

// Class for loading texture errors
class LoadTextureException : public PrimaryExceptions
{
public:
    LoadTextureException(const std::string &msg) : PrimaryExceptions("Load texture exception: " + msg) {}
};

// Class for loading font erros

class LoadFontException : public PrimaryExceptions
{
public:
    LoadFontException(const std::string &msg) : PrimaryExceptions("Load font exception: " + msg) {}
};

class GenerateQuestionException : public PrimaryExceptions
{
public:
    GenerateQuestionException(const std::string &msg) : PrimaryExceptions("Question generation exception: " + msg) {}
};

#endif