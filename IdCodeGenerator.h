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
    ~IdCodeGenerator();

    int getId() const;
    const std::string& getCode() const;
};
