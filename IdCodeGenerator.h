#pragma once

#include <string>

class IdCodeGenerator {
private:
    static int lastAssignedID;

protected:
    static int generateID();
    static std::string generateCode(const std::string& prefix);

public:
    IdCodeGenerator();
    virtual ~IdCodeGenerator();

    virtual int getId() const = 0;  
    virtual const std::string& getCode() const = 0;  
};
