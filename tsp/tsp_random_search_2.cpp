#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

namespace plt = matplotlibcpp;

//Number of cities
#define N 5000

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N+1 , vector<int> (2, -1));

//Cities adjacency matrice
std::vector<std::vector<double>> dists( N+1 , vector<double> (N+1, -1));

//Route matrice
std::vector<std::vector<int>> route( N , vector<int> (N, 0));

//Computes only the lower triagonal part of the cities' adjacency matrix
//  |- - - - -|
//  |x - - - -|
//  |x x - - -|
//  |x x x - -|
//  |x x x x -|
//because the adjacency matrice is (assumed) symmetric and the distance of 
//a city to itself is zero (elements of the main diagonal)
void compute_distances()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ( j == (i-1) )
			{
				//cout << i << "," << j << ' ';
				dists[i][j] = sqrt( (cities[i][0] - cities[j][0]) * (cities[i][0] - cities[j][0]) + 
						    (cities[i][1] - cities[j][1]) * (cities[i][1] - cities[j][1])  );
				//cout << dists[i][j] << endl;
			}
		}
		//cout << endl;
	}
};

void print(std::vector<std::vector<int>> cities2, std::vector<std::vector<long double>> dists2, std::vector<std::vector<int>> route2)
{	
	unsigned short int xs [N+1];
	unsigned short int ys [N+1];

	unsigned short int index = 0;
	for (unsigned short int i = 1; i <= N; i++)
	{
		for (unsigned short int j = 0; j < i; j++)
		{
			//cout << route2[i][j] << ' ';
			//if (route2[i][j] != 0)
			if (j == (i-1))
			{
				//cout << "(" << i << "," << j << ")" << endl;
				xs[index] = cities2[index][0];
				ys[index] = cities2[index][1];
				//cout << index << endl;
				index++;
				//cout << index << endl;
			}
		}
		//cout << endl;
	}
	//cout << index << endl;
	xs[index] = cities2[0][0];
	ys[index] = cities2[0][1];
	
	//Plot cities
	plt::plot(xs, ys, "b-");//, xss, yss, "r*");
	plt::show();
}



double compute_route_len(void)
{
	double r_len = 0.0;
	for(int i = 1; i < N; i++)
	{
		r_len += dists[i][i-1];
	}
	return r_len;
}

bool random_search()
{
	bool flag = true;
	
	int d = compute_route_len();

	//pick two random cities
	int c1 = rand() % N;
	int c2 = rand() % N;
	
	//switch cities
	int temp_x = cities[c1][0];
	int temp_y = cities[c1][1];
	cities[c1][0] = cities[c2][0];
	cities[c1][1] = cities[c2][1];
	cities[c2][0] = temp_x;
	cities[c2][1] = temp_y;
	//update the distances
	compute_distances();

	int d1 = compute_route_len();

	//cout << "d: " << d << ",d1: " << d1 << ",c1: " << c1 << ",c2: " << c2 << endl;

	if(d1 > d)
	{
		//revert 
		int temp_x = cities[c1][0];
		int temp_y = cities[c1][1];
		cities[c1][0] = cities[c2][0];
		cities[c1][1] = cities[c2][1];
		cities[c2][0] = temp_x;
		cities[c2][1] = temp_y;
		compute_distances();
		flag = false;
	}

	//cout << "B" << endl;

	return flag;
}

int main(void)
{

	cout << "Initializing cities..." << endl;


	//Seed rand()
	//srand (time(NULL));
	//cout << time(NULL) << endl;
	srand(24);

	int x = -1;
	int y = -1;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		bool flag;
		do{
			flag = false;
			x = rand() % 1000;
			y = rand() % 1000;
			for(int l1 = 0; l1 < N; l1++)
			{
				if( (x == cities[l1][0]) && (y == cities[l1][1]) ) 
				{
					flag = true;
					break;
				}
			}
		}while(flag == true);
		cities[i][0] = x;
		cities[i][1] = y;
		cout << cities[i][0] << "," << cities[i][1] << endl;
	}
	cities[N][0] = cities[0][0];
	cities[N][1] = cities[0][1];
	cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
	
	//starting and ending city
	cout << "Point zero city: (" << cities[0][0] << "," << cities[0][1] << ")" << endl;

	cout << "Begin TSP (Random Search)..." << endl;
	
	double route_len;
	double last_route_len = std::numeric_limits<double>::max();
	double tol = 1.0;
	int max_it = 0;
	do{
		bool flag = random_search();

		if (flag == true)
		{
			route_len = compute_route_len();
			tol = fabs(route_len - last_route_len)/(route_len + last_route_len);
			//cout << tol << "," << route_len << "," << last_route_len << endl;
			last_route_len = route_len;
			max_it++;
		}else
		{
			//cout << "Reverted" << endl;
		}
		//if ( route_len == last_route_len)
		if ((max_it > 150) or (tol < 0.0000001))
		//if ((tol < 0.000000001) or (route_len < 40000))
		//if ((tol < 0.00000001))// or (route_len < 40000))
		//if (newPair == false)
		//if ((tol < 0) and (max_it > 3000))
		//if(tol < 0.0000000000000001)
		{
			break;
		}
	}while( true );//(max_it < 3) and (newPair) and (tol > 0.001) );

	cout << "Took " << max_it << " iterations" << endl;

	print(cities, dists, route);

	return 0;
}

