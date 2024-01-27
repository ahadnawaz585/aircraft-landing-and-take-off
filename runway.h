#pragma once

#include "IdCodeGenerator.h"
#include <string>

enum class RunwayStatus
{
	OCCUPIED,
	FREE
};

class Runway : public IdCodeGenerator
{
private:
	int id;
	std::string code;
	RunwayStatus status;
	bool hasPriority;
	int planesLanded;
	int planesTakeOff;

public:
	Runway(RunwayStatus status, bool priority);

	RunwayStatus getStatus() const;
	bool hasLandingPriority() const;
	int getPlanesLanded() const;
	int getPlanesTakeOff() const;
	const std::string &getCode() const;

	void setStatus(RunwayStatus status);
	void setPriority(bool priority);
	void incrementPlanesLanded();
	void incrementPlanesTakeOff();
};


