#include "Acceleration.h"

void Acceleration::HandleKeydown(unsigned char key, int x, int y)
{
	if (!keydown)
	{
		keydown = true;
		switch (key)
		{
			case 'w':
				acceleration = 0;
				decelTimer.stop();
				accelTimer.setInterval([&]()
						{
						if (currentVelocity > -143)
						{
						currentVelocity -= acceleration;
						acceleration += 0.2;
						}
						else
						{
							accelTimer.stop();
						}
						}, 30);
		}
	}
}

void Acceleration::HandleKeyup(unsigned char key, int x, int y)
{
	if (keydown)
	{
		keydown = false;
		switch (key)
		{
			case 'w':
				acceleration = 0;
				accelTimer.stop();
				decelTimer.setInterval([&]()
						{
							if (currentVelocity < 137)
							{
							currentVelocity	+= acceleration;
							acceleration += 0.1;
							}
							else
							{
								decelTimer.stop();
							}
						}, 30);;
		}
	}
}

int Acceleration::GetVelocity()
{
	return currentVelocity;
}
