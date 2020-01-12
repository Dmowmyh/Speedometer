#ifndef ACCELERATION_H
#define ACCELERATION_H
#include "timercpp/timercpp.h"

class Acceleration
{
public:
	Acceleration() = default;
	~Acceleration() = default;
	const int initialVelocity = 0;
	const int endVelocity = 290;
	const int initialAngle = 137;
	const int maximumAngle = -143;
	void HandleKeydown(unsigned char key, int x, int y);
	void HandleKeyup(unsigned char key, int x, int y);
	int GetVelocity();
private:
	bool keydown = false;
	int currentVelocity = 137;
	double acceleration = 0;
	Timer accelTimer;
	Timer decelTimer;
};

#endif /* end of include guard ACCELERATION_H */

