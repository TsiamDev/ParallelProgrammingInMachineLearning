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
#define N 5//0//00
//Point area
#define XY 1000

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N+1 , vector<int> (2, -1));

// Cities adjacency matrix
std::vector<std::vector<double>> dists( N , vector<double> (N, -1));

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
	for (int i = 0; i < N; i++)
	{
		cout << "A" << endl;
		for (int j = 0; j < N; j++)
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
	//srand (time(NULL));
	srand(24);
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
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
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
	int explored_ind = 0;
	int explored[N] = {1};

	int j = 0;
	int it = 0;

	double min_dist;
	int temp_min_x;
	int temp_min_y;
	//second minimum value
	double min_dist2;
	int temp_x;
	int temp_y;
	bool found;
	while(it < N)
	//for (int j = 0; j < N-1; j++)
	{

		for(int k = 0; k < N; k++)
		{
			for (int l = 0; l < N; l++)
			{
				cout << dists[k][l] << ' ';
			}
			cout << endl;
		}
		cout << "it " << it << endl;
		
		//find the three leftmost columns that have not been explored
		int indices[3] = {-1};
		int o = 0;
		for (int k = 0; k < N; k++)
		{
			bool foundk = false;
			for (int t = 0; t < explored_ind; t++)
			{
				if(explored[t] == k)
				{
					foundk = true;
					break;
				}	
			}
			if (foundk == false)
			{
				indices[o] = k;	
				o++;
			}
			if (o == 3)
			{
				break;
			}
		}

		
		if (indices[0] != j)
		{
			min_dist = dists[j][indices[0]];
			temp_min_x = j;
			temp_min_y = 1;

			//second minimum value
			min_dist2 = dists[j][indices[1]];
			temp_x = j;
			temp_y = 1;
		}else if (indices[1] != j)
		{
			min_dist = dists[j][0];
			temp_min_x = j;
			temp_min_y = 0;

			//second minimum value
			min_dist2 = dists[j][2];
			temp_x = j;
			temp_y = 2;
		}else if (indices[2] != j)
		{
			min_dist = dists[j][0];
			temp_min_x = j;
			temp_min_y = 0;

			//second minimum value
			min_dist2 = dists[j][1];
			temp_x = j;
			temp_y = 1;
		}
		
	
		//compare the two first values and swap them accordingly
		if (min_dist < min_dist2)
		{
			double temp = min_dist;
			min_dist = min_dist2;
			min_dist2 = temp;
			
			int t = temp_x;
			temp_x = temp_min_x;
			temp_min_x = t;
		}		
	
		cout << min_dist << "---" <<  min_dist2 << endl;
		for (int i = temp_y+1; i < N; i++)
		{
			found = false;
			for (int t = 0; t < explored_ind; t++)
			{
				if (i == explored[t])
				{	
					cout << "found " << i << endl;
					found = true;
					break;
				}
			}
			/*
			if (found == false)
			{
				explored[explored_ind] = i;
				cout << "expored " << i << endl;
				explored_ind++;
			}
			*/
			//*
			cout << "explored: " ;
			for (int t = 0; t < explored_ind; t++)
			{
				cout << explored[t] << ' ';
			}
			cout << endl;
			//*/
			if ( i != j )
			{
				if ( found == false )
				{
					cout << "j " << j << endl;
					cout << "i " << i << endl;
					//cout << "found is " << found << endl;
					if (min_dist > dists[j][i])
					{
						cout << min_dist2 << ", min_dist2" << endl;
						min_dist2 = min_dist;
						cout << ", min_dist2" << min_dist2 << endl;
						min_dist = dists[j][i];
						temp_x = temp_min_x;
						temp_y = temp_min_y;
						temp_min_x = j;
						temp_min_y = i;
						//j = temp_y;
						cout << "min2 is at j " << temp_y << endl;
					}else if( min_dist2 > dists[j][i])
					{
						cout << min_dist2 << "mm min_dist2" << endl;
						min_dist2 = dists[j][i];
						cout << "mm min_dist2" << min_dist2 << endl;				
						temp_x = j;
						temp_y = i;
						//j = temp_y;
						cout << "min2 is at j " << temp_y << endl;
					}
				}
			}
			cout << "----inner for  ------" << endl;
		}
		if (found == false)
		{
			//cout << "bef route_dist " << route_dist << endl; 
			//cout << "bef min_dist2 " << min_dist2 << endl; 
			//route[route_ind] = temp_ind;
			route_dist += min_dist2;
			cout << "route_dist " << route_dist << endl;
			//cout << "temp_x " << temp_x << endl;
			xs[route_ind] = cities[temp_y][0];
			ys[route_ind] = cities[temp_y][1];
			cout << "Go To " << xs[route_ind] << "," << ys[route_ind] << endl;

			explored[explored_ind] = temp_y;
			cout << "explored " << temp_y << endl;
			explored_ind++;

			route_ind++;
			

			j = temp_y;
			cout << "go to j " << j << endl;
		}
		it++;
		cout << "**********************" << endl;
	}
	/*
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
*/
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
