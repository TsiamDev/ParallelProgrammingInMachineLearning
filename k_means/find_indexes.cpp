#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

const int N = 10;
const int Nc = 3;
const int Nv = 2;


	//Point Vectors
	std::vector<std::vector<double>> V( N , vector<double> (Nv, -1));
	//std::vector<int> V[N][Nv];

	//Cluster Centers
	std::vector<std::vector<double>> centroids( Nc , vector<double> (Nv, 0));
	//std::vector<int> centroids[Nc][Nv];

	//Classes
	std::vector<int> classes(N, -1);

int* find_indexes(std::vector<int> vec, int j)
{

	static int vec2[N];

	int ind = 0;
	for (int i = 0; i < N; i++)
	{	
		//initialize
		vec2[i] = -1;
		//cout << vec[i] << "," << j << endl;
		//update
		if (vec[i] == j)
		{
			vec2[ind] = i;
			ind++;
		}
	}	

	for (int i = 0; i < N; i++)
		std::cout << vec2[i] << ' ';
	
	cout << endl;
	return vec2;
}

int main(void)
{
	//srand(1645283643);
	srand(time(NULL));

	std::vector<std::vector<double>> V( N , vector<double> (Nv, -1));
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Nv; j++)
		{
			V[i][j] = rand() % 30;
		}
		cout << V[i][0] << "," << V[i][1] << endl;
	}
	cout << "---------------------------" << endl;

	//Generate clusters
	std::vector<int> classes(N, -1);

	for (int i = 0; i < N; i++)
	{
		classes[i] = rand() % 3;
	}

	for (std::vector<int>::const_iterator i = classes.begin(); i != classes.end(); i++)
		std::cout << *i << ' ';

	cout << endl;

	//find which vector is assigned to which cluster
	//and compute average
	for (int j = 0; j < Nc; j++)
	{
		int * vec = find_indexes(classes, j);
		int k;
		double tempx = 0.0;
		double tempy = 0.0;
		for (k = 0; k < N; k++)
		{
			cout << vec[k] << endl;
			if (vec[k] == -1)
			{
				break;
			}
			else
			{
				tempx = tempx + V[vec[k]][0];
				tempy = tempy + V[vec[k]][1];
			}
		}	
		tempx = tempx / k;
		tempy = tempy / k;
		cout << tempx << "," << tempy << endl;
		centroids[j][0] = tempx;
		centroids[j][1] = tempy;
	}
}
