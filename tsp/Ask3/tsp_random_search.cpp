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
#define N 100//0//0

//cities cartesian coordinates
std::vector<std::vector<int>> cities( N , vector<int> (2, -1));

//Cities adjacency matrice
//std::vector<std::vector<double>> dists( N+1 , vector<double> (N+1, -1));
std::vector<std::vector<double>> dists( N , vector<double> (N, -1));

//Route matrice
std::vector<std::vector<int>> route( N , vector<int> (N, 0));

unsigned short int checked_ind = 0;
std::vector<std::vector<int>> checked( N , vector<int> (2, -1));

string c[2] = { "b", "r" };
int ii = 0;

int explored[2*N][2] = {-1};
int exp_ind = 0;

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
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ( j == (i-1) )
			{
				//cout << i << "," << j << ' ';
				dists[i][j] = sqrt( (cities[i%N][0] - cities[j][0]) * (cities[i%N][0] - cities[j][0]) + 
						    (cities[i%N][1] - cities[j][1]) * (cities[i%N][1] - cities[j][1])  );
				//cout << dists[i][j] << endl;
			}
		}
		//cout << endl;
	}
};

void print(std::vector<std::vector<int>> cities2, std::vector<std::vector<double>> dists2, std::vector<std::vector<int>> route2)
{	
	/*
	//print cities
	for (unsigned short int i = 0; i < N; i++)
	{
		cout << "(" << cities2[i][0] << "," << cities2[i][1] << ")" << " - ";
	}
	cout << "(" << cities2[0][0] << "," << cities2[0][1] << ")" << endl;
	*/
	//print distances
	for (unsigned short int i = 0; i <= N; i++)
	{
		for (unsigned short int j = 0; j <= N; j++)
		{
			//cout << dists2[i][j] << ' ';
		}
		//cout << endl;
	}
/*
	//print route
	for (unsigned short int i = 1; i < N; i++)
	{
		for (unsigned short int j = 0; j < N; j++)
		{
			if ( j == (i-1) )
			{
				cout << route[i][j] << ",";
			}
		}
	}
	cout << route[N-1][0] << endl;
*/
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
	/*
	for (unsigned short int i = 0; i < N+1; i++)
	{
		cout << xs[i] << ' ';
	}
	cout << endl;
	for (unsigned short int i = 0; i < N+1; i++)
	{
		cout << ys[i] << ' ';
	}
	cout << endl;
	*/
	//*
	//Plot cities
	plt::plot(xs, ys, c[ii] + "-");//, xss, yss, "r*");
	ii++;
	ii = ii % 2;
	//plt::show();
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

bool random_search3(void)
{
	bool hasReverted;
	double r_len = compute_route_len();
	bool newPair = true;
	int i;
	do{
		hasReverted = false;
		// Choose two cities
		int ind1;
		int ind2;
		do{
			i = 0;
			do{
				ind1 = 1 + (rand() % N);
				ind2 = rand() % N;
				if (abs(ind1 - ind2) != 1)
				{	
					continue;
				}
				if (ind1<ind2)
				{
					continue;
				}
				break;
			}while(true);
			//cout << "ind1: " << ind1 << endl;
			//cout << "ind2: " << ind2 << endl;

			newPair = true;
			for(i = 0; i < checked_ind; i++)
			{
				//cout << i << endl;
				if ((checked[i][0] == ind1) and (checked[i][1] == ind2))
				{
					newPair = false;
					break;
				}else{
					
				}
			}
			if (newPair)
			{
				//cout << "added " << ind1 << "," << ind2 << " to checked at pos " << checked_ind << endl;
				checked[checked_ind][0] = ind1;
				checked[checked_ind][1] = ind2;
				checked_ind++;
			}

			if( (i == N-1) and (not newPair) )
			{
				break;
			}

			//cout << "while: " << (not newPair) << endl;
		}while(not newPair);

		/*
		for (int i = 0; i != checked.size(); ++i)
		{  	
			cout << checked[i][0] << "," << checked[i][1] << endl;
		}
		*/

		int x_t = cities[ind1%N][0];
		int y_t = cities[ind1%N][1];
		cities[ind1%N][0] = cities[ind2][0];
		cities[ind1%N][1] = cities[ind2][1];
		cities[ind2][0] = x_t;
		cities[ind2][1] = y_t;

		//cout << "ind1: " << ind1 << ", ind2: " << ind2 << endl;
		//cout << cities[ind1%N][0] << "," << cities[ind1%N][1] << "---" << cities[ind2][0] << "," << cities[ind2][1] << endl;

		compute_distances();

		double r_len_new = compute_route_len();
		//cout << "rlen: " << r_len << ", new: " << r_len_new << endl;
		if (r_len_new >= r_len)
		{
			//Revert
			hasReverted = true;
			//cout << "Reverting" << endl;
			x_t = cities[ind1%N][0];
			y_t = cities[ind1%N][1];
			cities[ind1%N][0] = cities[ind2][0];
			cities[ind1%N][1] = cities[ind2][1];
			cities[ind2][0] = x_t;
			cities[ind2][1] = y_t;

			compute_distances();
		}

		if( i == (N-1) )
			break;
		//cout << "A" << endl;
	}while(hasReverted == true);
	
	if (i == (N-1) )
	{	
		return false;
	}else{
		return true;
	}
}

bool random_search4(void)
{
	bool flag = false;

	int d = compute_route_len();
	cout << "1" << endl;
	//pick two random cities
	int c1;
	int c2;
	do{
		cout << "4" << endl;
		c1 = rand() % N;
		c2 = rand() % N;
		bool flag = false;
		for(int i = 0; i < N*N; i++)
		{
			if( ((explored[i][0] == c1) and (explored[i][1] == c2)) or ((explored[i][0] == c2) and (explored[i][1] == c1)) )
			{
				flag = true;
				break;
			}

		}
		if ( flag == true )
		{
			continue;
		}
	}while( c1 == c2 );
	cout << "exp_ind: " << exp_ind << "," << sizeof(explored)/sizeof(explored[0]) << endl;
	explored[exp_ind][0] = c1;
	explored[exp_ind][1] = c2;
	exp_ind++;
	cout << "B" << endl;
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
		int temp_x = cities[c1%N][0];
		int temp_y = cities[c1%N][1];
		cities[c1%N][0] = cities[c2%N][0];
		cities[c1%N][1] = cities[c2][1];
		cities[c2%N][0] = temp_x;
		cities[c2%N][1] = temp_y;
		compute_distances();
		flag = true;
	}

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
	cout << "---------------------------" << endl;

	cout << "Computing distances between cities..." << endl;

	compute_distances();
	
	//starting and ending city
	std::vector<int> point_zero_city = {cities[0][0], cities[0][1]};
	cout << "Point zero city: (" << point_zero_city[0] << "," << point_zero_city[1] << ")" << endl;

	cout << "Begin TSP (Random Search)..." << endl;

	//cout << "Compute Random initial route" << endl;
	/*
	double route_len = 0.0;
	for (unsigned short int i = 1; i < N; i++)
	{
		for (unsigned short int j = 0; j < N; j++)
		{
			if ( j == (i-1) )
			{
				cout << "(" << i << "," << j << ")" << endl;
				route[i][j] = rand() % 100 + 1;
				cout << route[i][j] << endl;

				//account for the new distance
				route_len += route[i][j];
			}
		}
	}
	route[N-1][0] = rand() % 100 + 1;
	cout << "(" << N-1 << "," << 0 << ")" << endl;
	cout << route[N-1][0] << endl;

	cout << "Route length: " << route_len << endl;
	
	*/
	//------------------------------for plotting-------------------------------
	//unsigned short int xs [N+1];
	//unsigned short int ys [N+1];
	/*
	unsigned short int index = 0;
	for (unsigned short int i = 0; i < N; i++)
	{
		for (unsigned short int j = 0; j < i; j++)
		{
			cout << route[i][j] << ' ';
			if (route[i][j] != 0)
			{
				xs[index] = cities[index][0];
				ys[index] = cities[index][1];
				//cout << index << endl;
				index++;
				//cout << index << endl;
			}
		}
		cout << endl;
	}
	cout << index << endl;
	xs[index] = cities[0][0];
	ys[index] = cities[0][1];


	//print();
	//*/
	
	//print(cities, dists, route);

	double route_len;
	double last_route_len = std::numeric_limits<double>::max();
	double tol;
	int max_it = 0;
	bool newPair;
	do{

		//newPair = random_search3();
		do{
			//cout << "1" << endl;
			newPair = random_search4();
			//cout << newPair << endl;
			//cout << "3" << endl;
		}while(newPair == true);
	cout << "A" << endl;
		route_len = compute_route_len();
		tol = fabs(route_len - last_route_len)/(route_len + last_route_len);
		last_route_len = route_len;
		cout << tol << "," << route_len << endl;
		max_it++;
		//if (max_it > 3000)
		//if ((tol < 0.000000001) or (route_len < 40000))
		if ((tol < 0.00000001))// or (route_len < 40000))
			break;
		//if (newPair == false)
		//	break;
		//if (tol < 0.000001)
		//	break;
	}while( true );//(max_it < 3) and (newPair) and (tol > 0.001) );

	//random_search(cities, dists);
	/*
	for (unsigned short int i = 0; i < N+1; i++)
	{
		cout << xs[i];
	}
	cout << endl;
	for (unsigned short int i = 0; i < N+1; i++)
	{
		cout << ys[i];
	}
	cout << endl;
	//Plot cities
	plt::plot(xs, ys, "b-");//, xss, yss, "r*");
	plt::show();
	//*/
	print(cities, dists, route);
	plt::show();


	return 0;
}

