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
//Point area
#define XY 1000

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N , vector<int> (2, -1));

// Cities adjacency matrix
std::vector<std::vector<double>> dists( N+1 , vector<double> (N+1, -1));

int route[N];
int route_ind;

//Computes only the lower triagonal part of the cities' adjacency matrix
//  |- - - - -|
//  |x - - - -|
//  |x x - - -|
//  |x x x - -|
//  |x x x x -|
//because the adjacency matrix is (assumed) symmetric and the distance of 
//a city to itself is zero (elements of the main diagonal)
void compute_distances()
{
	for (int i = 0; i < N+1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			//cout << i << "," << j << ' ';
			dists[i][j] = sqrt( (cities[i%N][0] - cities[j][0]) * (cities[i%N][0] - cities[j][0]) + 
					    (cities[i%N][1] - cities[j][1]) * (cities[i%N][1] - cities[j][1])  );
			//cout << dists[i][j] << endl;
		}
		//cout << endl;
	}
};



int main(void)
{

	cout << "Initializing cities..." << endl;


	//Seed rand()
	srand (time(NULL));
	//srand(1645283643);
	//cout << time(NULL) << endl;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cities[i][j] = rand() % XY;
		}
		//cout << cities[i][0] << "," << cities[i][1] << endl;
	}
	//cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
	
	//starting and ending city
	std::vector<int> point_zero_city = {cities[0][0], cities[0][1]};
	cout << "Point zero city: (" << point_zero_city[0] << "," << point_zero_city[1] << ")" << endl;

	cout << "Begin TSP..." << endl;
/*
	for(int i = 0; i < N+1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << dists[i%N][j];
		}
		cout << endl;
	}
*/
	route_ind = 0;
	double route_dist = 0.0;
	int xs[N+1] = {-1};
	int ys[N+1] = {-1};
	for (int j = 0; j < N+1; j++)
	{
		double min_dist = 10000.0;
		int temp_x = -1;
		int temp_y = -1;
		for (int i = 1; i < N+1; i++)
		{
			if ( i > j )
			{
				if (min_dist > dists[i][j])
				{
					min_dist = dists[i][j];
					temp_x = i;
					temp_y = j;
				}
			}
		}
		//route[route_ind] = temp_ind;
		route_dist += min_dist;
		//cout << route_dist << endl;
		xs[route_ind] = temp_x;
		ys[route_ind] = temp_y;

		route_ind++;
	}

	//add the looping path to point zero city
	xs[N] = xs[0];
	ys[N] = ys[0];
	route_dist += dists[N][0];
/*
	for (int i = 0; i < N; i++)
	{
		cout << xs[i] << "," << ys[i] << endl;
	}
//*/


	plt::plot(xs, ys, "b-");
	plt::show();
	return 0;
}
