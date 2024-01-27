#ifndef IdCodeGenerator_h
#define IdCodeGenerator_h
#include <string>

class IdCodeGenerator
{
private:
    static int lastAssignedID;
    virtual int generateID() = 0;

protected:
    std::string generateCode(const std::string &prefix);

public:
    virtual ~IdCodeGenerator() = default;
    int getNextID();
};

#endif