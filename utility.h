#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdlib.h>
#include <stdio.h>

double** createSqrArray(int X , int Y);
double*** createCubeArray(int X , int Y , int Z);
void destroySqrArray(double** sqrArray , int X , int Y);
void destroyCubeArray(double*** cubeArray , int X , int Y , int Z);
void printSqrArray(double** sqrArray , int X , int Y);
void printCubeArray(double*** cubeArray , int X , int Y , int Z);
void writeToFile(char* name , double*** cubeArray , int X , int Y , int Z , double dx , double dy);



#endif