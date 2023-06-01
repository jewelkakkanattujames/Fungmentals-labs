#include "MathManager.h"

// Calculate the Euclidean distance between two points
double MathManager::Distance(const double& x1, const double& x2, const double& y1, const double& y2)
{
	// Calculate the square of the differences in x and y coordinates
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Calculate the Euclidean distance between two SDL_FRect rectangles
double MathManager::Distance(const SDL_FRect* r1, const SDL_FRect* r2)
{
	// Calculate the square of the differences in x and y coordinates
	return sqrt((r2->x - r1->x) * (r2->x - r1->x) + (r2->y - r1->y) * (r2->y - r1->y));
}

// Calculate the Euclidean distance between two SDL_FPoint points
double MathManager::Distance(const SDL_FPoint* p1, const SDL_FPoint* p2)
{
	// Calculate the square of the differences in x and y coordinates
	return sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y));
}

// Normalize a 2D vector represented by SDL_FPoint
SDL_FPoint MathManager::Normalize(SDL_FPoint v)
{
	// Initialize a normalized vector
	SDL_FPoint norm = { 0.0f, 0.0f };

	// Calculate the length of the vector
	float x = v.x;
	float y = v.y;
	float length = (x * x) + (y * y);

	// Check if the length is greater than 0 to avoid division by zero
	if (length > 0)
	{
		// Calculate the reciprocal of the length
		length = 1.0f / sqrt(length);

		// Normalize the vector by multiplying each component with the reciprocal length
		norm.x = x * length;
		norm.y = y * length;
	}

	// Return the normalized vector
	return norm;
}

// Calculate the angle between two points
double MathManager::AngleBetweenPoints(const double dy, const double dx)
{
	return atan2(dy, dx); // In radians.
}

// Set the deltas (changes in x and y) based on an angle and scaling factors
void MathManager::SetDeltas(const double angle, double& dx, double& dy, double fx, double fy)
{
	dx = SetDeltaX(angle, fx);
	dy = SetDeltaY(angle, fy);
}

// Calculate the delta x based on an angle and a scaling factor
double MathManager::SetDeltaX(const double angle, double fx)
{
	return cos(angle) * fx;
}

// Calculate the delta y based on an angle and a scaling factor
double MathManager::SetDeltaY(const double angle, double fy)
{
	return sin(angle) * fy;
}

// Convert degrees to radians
double MathManager::Deg2Rad(const double angle)
{
	return angle * (M_PI / 180.0);
}

// Convert radians to degrees
double MathManager::Rad2Deg(const double angle)
{
	return angle * (180.0 / M_PI);
}

// Convert an SDL_FRect to an SDL_Rect
SDL_Rect MathManager::ConvertFRect2Rect(const SDL_FRect& r)
{
	return { (int)r.x, (int)r.y, (int)r.w, (int)r.h };
}

// Convert an SDL_FPoint to an SDL_Point
SDL_Point MathManager::ConvertFPoint2Point(const SDL_FPoint& p)
{
	return { (int)p.x, (int)p.y };
}

// Constrain an angle between -180 and 180 degrees
double MathManager::Angle180(double a)
{
	// Normalize the angle to a range between 0 and 360 degrees
	a = fmod(a + 180.0, 360.0);

	// If the angle is negative, add 360 degrees to bring it back to the range of 0 to 360 degrees
	if (a < 0)
		a += 360.0;

	// Subtract 180 degrees to bring the angle back to the range of -180 to 180 degrees
	return a - 180.0;
}

// Constrain an angle between 0 and 360 degrees
double MathManager::Angle360(double a)
{
	// Normalize the angle to a range between 0 and 360 degrees
	a = fmod(a, 360.0);

	// If the angle is negative, add 360 degrees to bring it back to the range of 0 to 360 degrees
	if (a < 0)
		a += 360.0;

	return a;
}

// Linear interpolation between two values (double)
double MathManager::LerpD(double a, double b, double factor)
{
	return ((1.0 - factor) * a) + (factor * b);
}

// Linear interpolation between two angles (in radians)
double MathManager::LerpRad(double a, double b, double factor)
{
	double result;
	double diff = b - a;

	// Adjust the angles if the difference is larger than pi radians
	if (diff < -M_PI)
	{
		b += M_PI * 2;
		result = LerpD(a, b, factor);
		if (result >= M_PI * 2)
			result -= M_PI * 2;
	}
	else if (diff > M_PI)
	{
		b -= M_PI * 2;
		result = LerpD(a, b, factor);
		if (result < 0.0)
			result += M_PI * 2;
	}
	else
		result = LerpD(a, b, factor);

	return result;
}

// Calculate the halfway point between two SDL_Point points
SDL_Point MathManager::HalfwayPoint(const SDL_Point& from, const SDL_Point& to)
{
	return { (int)(((double)from.x + (double)to.x) / 2.0), (int)(((double)from.y + (double)to.y) / 2.0) };
}

// Clamp an integer value between a minimum and maximum value
int MathManager::ClampI(const int a, const int min, const int max)
{
	return std::min(std::max(a, min), max);
}
