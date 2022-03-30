#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

#include <chrono>

using namespace std;

namespace plt = matplotlibcpp;

//Number of cities
#define N 10000
//Point area
#define XY 1000
//K==2 - 50:50 (%)
//K>2  - 1/k:(k-1)/k
#define THRESHOLD 3
//int THRESHOLD = 2;

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N , vector<int> (2, -1));

// Cities adjacency matrix
std::vector<std::vector<double>> dists( N , vector<double> (N, -1));

//Computes only the adjacency matrice
void compute_distances()
{
	//cout << "1" << endl;
	//#pragma omp parallel for schedule(static)
	for (int i = 0; i < N; i++)
	{
		//cout << "2" << endl;
		for (int j = 0; j < N; j++)
		{
			//cout << "3" << endl;
			//cout << i << "," << j << ' ';
			//#pragma omp critical
			dists[i][j] = sqrt( (cities[i][0] - cities[j][0]) * (cities[i][0] - cities[j][0]) + 
					    (cities[i][1] - cities[j][1]) * (cities[i][1] - cities[j][1])  );
			//cout << dists[i][j] << endl;
		}
		//cout << endl;
	}
	//cout << "4" << endl;
};

bool is_in_explored(int j, int explored_ind, int explored[])
{
	bool flag = false;
	//#pragma omp parallel for private(explored_ind) reduction(and:flag) schedule(static)
	for(int k = 0; k < explored_ind; k++)
	{
		if(explored[k] == j)
		{
			flag = true;
		}
	}
	return flag;
};

int find_min_of_row(int row, int explored_ind, int explored[])
{
	double min_d = 100000.0;
	int ind = -1;
	//#pragma omp parallel for reduction(min:min_d) shared(ind) schedule(dynamic)
	for(int j = 0; j < N; j++)
	{
		
		if (row != j)
		{
			if (is_in_explored(j, explored_ind, explored) == false)
			{
				if (min_d > dists[row][j])
				{
					//#pragma omp critical
					//{
						min_d = dists[row][j];
						ind = j;
					//}
				}
			}
		}
	}
	return ind;
};

int find_second_min_of_row(int row, int explored_ind, int explored[], int j1)
{
	double min_d = 100000.0;
	int ind = -1;
	//#pragma omp parallel for reduction(min:min_d) shared(ind) schedule(dynamic)
	for(int j2 = 0; j2 < N; j2++)
	{
		if (j1 != j2)
		{
			if (row != j2)
			{
				if (is_in_explored(j2, explored_ind, explored) == false)
				{
					if (min_d > dists[row][j2])
					{
						//#pragma omp critical
						//{
							min_d = dists[row][j2];
							ind = j2;
						//}
					}
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
			cities[i][j] = rand() % XY;
		}
		//cout << cities[i][0] << "," << cities[i][1] << endl;
	}
	//cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
/*
	cout << "1" << endl;
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < N; i++)
	{
		cout << "2" << endl;
		for (int j = 0; j < N; j++)
		{
			cout << "3" << endl;
			//#pragma omp critical
			//cout << i << "," << j << ' ';
			//#pragma omp critical
			dists[i][j] = sqrt( (cities[i][0] - cities[j][0]) * (cities[i][0] - cities[j][0]) + 
					    (cities[i][1] - cities[j][1]) * (cities[i][1] - cities[j][1])  );
			//cout << dists[i][j] << endl;
		}
		//cout << endl;
	}
	cout << "4" << endl;
	*/
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
	int j2;
	int explored[N+1] = {-1};
	int explored_ind = 0;
	int xs[N];
	int ys[N];
	double route_dist = 0.0;

	explored[explored_ind] = 0;
	xs[explored_ind] = cities[explored[0]][0];
	ys[explored_ind] = cities[explored[0]][1];
	explored_ind++;
	//#pragma omp parallel for reduction(+:route_dist) shared(explored,j,i) schedule(static)
	for( int it = 0; it < N; it++)
	{


		//cout << "1" << endl;
		//do{
//auto started = std::chrono::high_resolution_clock::now();
			//find the minimum, != 0 value of the row
			//and return its' index
			j = find_min_of_row(i, explored_ind, explored);
//auto done = std::chrono::high_resolution_clock::now();

//std::cout << "mor: " << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << " " << j << endl;
			//flag = is_in_explored(j, explored_ind, explored);
		//}while(flag == true);
		//cout << "2" << endl;


//started = std::chrono::high_resolution_clock::now();
		//do{
			//find the second minimum, != 0 value of the row
			//and return its' index
			j2 = find_second_min_of_row(i, explored_ind, explored, j);
			//flag = is_in_explored(j2, explored_ind, explored);
			/*
			cout << j2 << "," << j << endl;
			for(int t = 0; t < explored_ind; t++)
			{
				cout << explored[t] << ' ';
			}
			cout << endl;
			*/
		//}while(flag == true);
/*
done = std::chrono::high_resolution_clock::now();

std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << endl;

started = std::chrono::high_resolution_clock::now();
//*/
		int final_j;	
		if ((j > -1) or (j2 > -1))
		{		
			if ((j > -1) and (j2 > -1))
			{	
				int ch = rand() % THRESHOLD;
				if (ch == 0)
				{
					final_j = j;
				}else{
					final_j = j2;
				}	
			}else if (j > -1)
			{
				final_j = j;
			}else if (j2 > -1)
			{
				final_j = j2;
			}
			//cout << "i " << i << ", j " << j << endl;
			//for ploting purposes
			xs[explored_ind] = cities[final_j][0];
			ys[explored_ind] = cities[final_j][1];	
			//a column is found!
			//add it to explored
			explored[explored_ind] = final_j;
			explored_ind++;

			route_dist += dists[i][final_j];
			//cout << route_dist << endl;

			//go to the explored city
			i = final_j;


		}
//done = std::chrono::high_resolution_clock::now();

//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << endl;
		
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

	//plt::plot(xs, ys, "b-");
	//plt::show();
	return 0;
}
