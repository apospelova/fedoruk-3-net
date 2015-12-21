#include "utility.h"

double** createSqrArray(int X , int Y){
	int i , j;
	double** sqrArray = (double**)malloc(sizeof(double) * Y);
	for(i = 0 ; i < Y ; i++){
		sqrArray[i] = (double*)malloc(sizeof(double) * X);
		for(j = 0 ; j < X ; j++)
			sqrArray[i][j] = 0.;
	}
	return sqrArray;
}

double*** createCubeArray(int X , int Y , int Z){
	int i;
	double*** cubeArray = (double***)malloc(sizeof(double) * Z);
	for(i = 0 ; i < Z ; i++)
		cubeArray[i] = createSqrArray(X , Y);
	return cubeArray;
}

void destroySqrArray(double** sqrArray , int X , int Y){
	int i;
	for(i = 0 ; i < Y ; i++)
		free(sqrArray[i]);
	free(sqrArray);
}

void destroyCubeArray(double*** cubeArray , int X , int Y , int Z){
	int i;
	for(i = 0 ; i < Z ; i++)
		destroySqrArray(cubeArray[i] , X , Y);
	free(cubeArray);
}

void printSqrArray(double** sqrArray  , int X , int Y){
	int i, j;
	for(i = 0 ; i < Y ; i++){
		for(j = 0 ; j < X ; j++)
			printf("%.2f " , sqrArray[i][j]);
		printf("\n");
	}
}

void printCubeArray(double*** cubeArray , int X , int Y , int Z){
	int i;
	for(i = 0 ; i < Z ; i++){
		printSqrArray(cubeArray[i] , X , Y);
		printf("------------------------\n");
	}
}

void writeToFile(char* nameFile , double*** data , int X , int  Y ,int  T , double dx , double dy){
	int i , j , k;
	FILE *file;
	file = fopen(nameFile , "w");
	for(k = 0 ; k < T ; k++){
		for(j = 0 ; j < Y ; j++){
			for(i = 0 ; i < X ; i++)
				fprintf(file, "%f %f %f\n", i * dx , j * dy , data[k][j][i]);
		}
		fprintf(file, "\n\n");
	}
	fclose(file);
}
