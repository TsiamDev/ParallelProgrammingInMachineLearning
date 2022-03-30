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
#define N 50//0//00
//Point area
#define XY 1000

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N+1 , vector<int> (2, -1));

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
	cout << "1" << endl;
	for (int i = 1; i < N+1; i++)
	{
		cout << "A" << endl;
		for (int j = 0; j < i; j++)
		{
			cout << i << "," << j << ' ';
			dists[i][j] = sqrt( (cities[i][0] - cities[j][0]) * (cities[i][0] - cities[j][0]) + 
					    (cities[i][1] - cities[j][1]) * (cities[i][1] - cities[j][1])  );
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
		cout << cities[i][0] << "," << cities[i][1] << endl;
	}
	cities[N] = cities[0];
	cout << cities[N][0] << "," << cities[N][1] << endl;
	//cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
	
	//starting and ending city
	std::vector<int> point_zero_city = {cities[0][0], cities[0][1]};
	cout << "Point zero city: (" << point_zero_city[0] << "," << point_zero_city[1] << ")" << endl;

	cout << "Begin TSP..." << endl;
//*
	for(int i = 0; i < N+1; i++)
	{
		for (int j = 0; j < N+1; j++)
		{
			cout << dists[i][j] << ' ';
		}
		cout << endl;
	}
//*/
	cout << "---------------------------------" << endl;
	route_ind = 0;
	double route_dist = 0.0;
	int xs[N+1] = {-1};
	int ys[N+1] = {-1};
	//int j = 0;
	for (int j = 0; j < N-1; j++)
	{
	/*
		if( j == N )
		{
			min_dist2 = 
		}*/
		//j = 0;
		//minimum value
		double min_dist = dists[j+1][j];
		int temp_min_x = j+1;
		int temp_min_y = j;
		//double min_dist = dists[i][0];
		//int temp_min_x = ;
		//int temp_min_y = j;

		//second minimum value
		double min_dist2 = dists[j+2][j];
		int temp_x = j+2;
		int temp_y = j;
	
		//compare the two first values and swap them accordingly
		if (min_dist < min_dist2)
		{
			double temp = min_dist;
			min_dist = min_dist2;
			min_dist2 = temp;

			temp_x = j+1;
			temp_min_x = j+2;
		}		
	
		cout << min_dist << "---" <<  min_dist2 << endl;
		for (int i = 3; i < N+1; i++)
		{

			if ( i > j )
			{
				if (min_dist > dists[i][j])
				{
					min_dist2 = min_dist;
					min_dist = dists[i][j];
					temp_x = temp_min_x;
					temp_y = temp_min_y;
					temp_min_x = i;
					temp_min_y = j;
				}else if( min_dist2 > dists[i][j])
				{
					min_dist2 = dists[i][j];
					temp_x = i;
					temp_y = j;
				}
			}
		}
		//route[route_ind] = temp_ind;
		route_dist += min_dist2;
		cout << route_dist << endl;
		xs[route_ind] = cities[temp_y][0];
		ys[route_ind] = cities[temp_y][1];
		cout << xs[route_ind] << "," << ys[route_ind] << endl;

		route_ind++;
	}
	
	//the two last steps are unrolled
	//Second to last step
	if ( dists[N-1][N-2] > dists[N][N-2] )
	{
		route_dist += dists[N-1][N-2];
		xs[route_ind] = cities[N-1][0];
		ys[route_ind] = cities[N-1][1];
	}else{
		route_dist += dists[N][N-2];
		xs[route_ind] = cities[N][0];
		ys[route_ind] = cities[N][1];
	}
	cout << route_dist << endl;
	cout << xs[route_ind] << "," << ys[route_ind] << endl;
	route_ind++;

	//Last step
	route_dist += dists[N][N-1];
	xs[route_ind] = cities[N][0];
	ys[route_ind] = cities[N][1];
	cout << xs[route_ind] << "," << ys[route_ind] << endl;
	route_ind++;
	cout << "-------------------------------" << endl;
	//add the looping path to point zero city
	//xs[route_ind] = xs[0];
	//ys[route_ind] = ys[0];
	//route_dist += dists[N][0];
//*
	for (int i = 0; i < N+1; i++)
	{
		cout << xs[i] << "..." << ys[i] << endl;
	}
//*/


	plt::plot(xs, ys, "b-");
	plt::show();
	return 0;
}
