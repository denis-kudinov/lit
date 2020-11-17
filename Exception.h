#include <iostream>
#include <exception>

class Exception : public std::exception
{
    std::string message;
public:
    Exception(const std::string& msg) : message(msg){}

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }
}; 