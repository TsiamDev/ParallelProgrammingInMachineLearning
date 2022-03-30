#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

namespace plt = matplotlibcpp;

//Number of cities
#define N 10000

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N , vector<int> (2, -1));

// Cities adjacency matrix
std::vector<std::vector<double>> dists( N , vector<double> (N, -1));

//Computes only the adjacency matrice
void compute_distances()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//cout << i << "," << j << ' ';
			dists[i][j] = sqrt( (cities[i][0] - cities[j][0]) * (cities[i][0] - cities[j][0]) + 
					    (cities[i][1] - cities[j][1]) * (cities[i][1] - cities[j][1])  );
			//cout << dists[i][j] << endl;
		}
		//cout << endl;
	}
};

bool is_in_explored(int j, int explored_ind, int explored[])
{
	for(int k = 0; k < explored_ind; k++)
	{
		if(explored[k] == j)
		{
			return true;
		}
	}
	return false;
};

int find_min_of_row(int row, int explored_ind, int explored[])
{
	double min = 100000.0;
	int ind = -1;
	for(int j = 0; j < N; j++)
	{
		
		if (row != j)
		{
			if (is_in_explored(j, explored_ind, explored) == false)
			{
				if (min > dists[row][j])
				{
					min = dists[row][j];
					ind = j;
				}
			}
		}
	}
	return ind;
};

int main(void)
{

	cout << "Initializing cities..." << endl;


	//Seed rand()
	//srand (time(NULL));
	srand(24);
	//cout << time(NULL) << endl;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cities[i][j] = rand() % 1000;
		}
		//cout << cities[i][0] << "," << cities[i][1] << endl;
	}
	//cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
	
	//starting and ending city
	std::vector<int> point_zero_city = {cities[0][0], cities[0][1]};
	cout << "Point zero city: (" << point_zero_city[0] << "," << point_zero_city[1] << ")" << endl;
	/*
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << dists[i][j] << ' ';
		}
		cout << endl;
	}
	//*/

	cout << "Begin TSP..." << endl;

	int i = 0;
	int j;
	int explored[N+1] = {-1};
	int explored_ind = 0;
	bool flag;
	int xs[N];
	int ys[N];
	double route_dist = 0.0;

	explored[explored_ind] = 0;
	xs[explored_ind] = cities[explored[0]][0];
	ys[explored_ind] = cities[explored[0]][1];
	explored_ind++;
	for( int it = 0; it < N; it++)
	{
		do{
			//find the minimum, != 0 value of the row
			//and return its' index
			j = find_min_of_row(i, explored_ind, explored);
			flag = is_in_explored(j, explored_ind, explored);
		}while(flag == true);
		if (j > -1)
		{
			//cout << "i " << i << ", j " << j << endl;
			//for ploting purposes
			xs[explored_ind] = cities[j][0];
			ys[explored_ind] = cities[j][1];	
			//a column is found!
			//add it to explored
			explored[explored_ind] = j;
			explored_ind++;

			route_dist += dists[i][j];
			//cout << route_dist << endl;

			//go to the explored city
			i = j;


		}
		
	}

	explored[explored_ind] = explored[0];
	xs[explored_ind] = cities[explored[0]][0];
	ys[explored_ind] = cities[explored[0]][1];
	explored_ind++;
	//cout << j << endl;
	//cout << it << endl;
	//cout << explored[explored_ind-1] << endl;
	//cout << dists[explored[explored_ind-2]][0] << endl;
	route_dist += dists[explored[explored_ind-2]][0];
	//cout << route_dist << endl;
	//xs[explored_ind] = cities[explored[0]][0];
	//ys[explored_ind] = cities[explored[0]][1];
	//explored_ind++;
	/*
	for(int l = 0; l < explored_ind; l++)
	{
		cout << explored[l] << ' ';
	}	
	cout << endl;

	for (int i = 0; i < N+1; i++)
	{
		cout << xs[i] << "..." << ys[i] << endl;
	}

	//*/

	cout << "route distance " << route_dist << " (km)" << endl;

	plt::plot(xs, ys, "b-");
	plt::show();
	return 0;
}
