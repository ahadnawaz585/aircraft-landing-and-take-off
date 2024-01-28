#include "IdCodeGenerator.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int IdCodeGenerator::lastAssignedID = 0;

IdCodeGenerator::IdCodeGenerator(){
}

std::string IdCodeGenerator::generateCode(const std::string &prefix)
{
    std::ostringstream oss;
    oss << prefix << std::setw(3) << std::setfill('0') << generateID();
    return oss.str();
}

int IdCodeGenerator::generateID()
{
    return ++lastAssignedID;
}

IdCodeGenerator::~IdCodeGenerator() {
}

