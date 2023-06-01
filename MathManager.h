#pragma once

#include <algorithm>  // Include the algorithm library for mathematical functions
#include <cmath>  // Include the cmath library for mathematical functions
#include "SDL.h"  // Include the SDL library for SDL-related functionality

class MathManager
{
public: // Public methods.

    // Calculate the Euclidean distance between two points given their coordinates
    static double Distance(const double&, const double&, const double&, const double&);

    // Calculate the Euclidean distance between two SDL_FRect rectangles
    static double Distance(const SDL_FRect*, const SDL_FRect*);

    // Calculate the Euclidean distance between two SDL_FPoint points
    static double Distance(const SDL_FPoint*, const SDL_FPoint*);

    // Normalize a 2D vector represented by an SDL_FPoint
    static SDL_FPoint Normalize(SDL_FPoint);

    // Calculate the angle between two points given their coordinates
    static double AngleBetweenPoints(const double, const double);

    // Set the deltas (change in x and y) based on a given angle and speed
    static void SetDeltas(const double, double&, double&, double = 1.0, double = 1.0);

    // Calculate the change in x (delta x) based on a given angle and speed
    static double SetDeltaX(const double, double = 1.0);

    // Calculate the change in y (delta y) based on a given angle and speed
    static double SetDeltaY(const double, double = 1.0);

    // Convert an SDL_FRect to an SDL_Rect
    static SDL_Rect ConvertFRect2Rect(const SDL_FRect&);

    // Convert an SDL_FPoint to an SDL_Point
    static SDL_Point ConvertFPoint2Point(const SDL_FPoint&);

    // Convert an angle in degrees to radians
    static double Deg2Rad(const double);

    // Convert an angle in radians to degrees
    static double Rad2Deg(const double);

    // Convert an angle to the range of [-180, 180] degrees
    static double Angle180(double);

    // Convert an angle to the range of [0, 360] degrees
    static double Angle360(double);

    // Perform linear interpolation between two values (double)
    static double LerpD(double, double, double);

    // Perform linear interpolation between two angles (radians)
    static double LerpRad(double, double, double);

    // Calculate the halfway point between two SDL_Point points
    static SDL_Point HalfwayPoint(const SDL_Point&, const SDL_Point&);

    // Clamp an integer value between a minimum and maximum value
    static int ClampI(const int, const int, const int);

private: // Private properties.

    // Private constructor to prevent instances of MathManager from being created
    MathManager() = default;
};
