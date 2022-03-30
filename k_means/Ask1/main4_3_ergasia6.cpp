#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <vector>

// *******************************************************************
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
//************************************************************

using namespace std;


//Number of point vectors
#define N 100000
//Number of point dimensions
#define Nv 2
//Number of clusters
#define Nc 100
//Tolerance
#define THR_KMEANS 0.0001
//Point area
#define XY 1000

//Point Vectors
std::vector<std::vector<double>> V( N , vector<double> (Nv, -1));

//Cluster Centers
std::vector<std::vector<double>> centroids( Nc , vector<double> (Nv, 0));

//Classes
std::vector<int> classes(N, -1);

//Find Euclidian Distance between two vectors 
//(regardless of vector dimensions)
double	vectors_distance(std::vector<double> a, std::vector<double> b)
{
	double temp = 0;
	for (int i = 0; i < Nv; i++)
	{
		temp += (a[i] - b[i]) * (a[i] - b[i]);
	}
	return  sqrt(temp);
};

void find_indexes(std::vector<int> vec)
{
	//store cluster indexes for the points in vec2
	static int vec2[N];
	register int ind;
	for (int j = 0; j < Nc; j++)
	{
		ind = 0;
		for (int i = 0; i < N; i++)
		{
			vec2[i] = -1;
			if (vec[i] == j)
			{
				vec2[ind] = i;
				ind++;
			}
		}	

		//Compute new cluster centroid
		register int k;
		double temp [Nv] = {0.0};
		for (k = 0; k < N; k++)
		{
			if (vec2[k] == -1)
			{
				break;
			}
			else
			{
				for(int o = 0; o < Nv; o++)
				{
					temp[o] += V[vec2[k]][o];
					
				}
			}	
		}
		for (int o = 0; o < Nv; o++)
		{
			centroids[j][o] = temp[o] / k;
		}
	}
}

int main(void)
{
	//Seed rand()
	//srand (time(NULL));
	srand(24);
	//cout << time(NULL) << endl;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Nv; j++)
		{
			V[i][j] = rand() % XY;
		}
	}
	
	//Pick Nc random centers-----------------------------------------
	std::vector<int> xs(Nc, -1);
	int ind = 0;

	int x;

	for (int i = 0; i < Nc; i++)
	{
		do{
			x = rand() % N;
			auto res = std::find(begin(xs), end(xs), x);
			if (res != std::end(xs)) 
			{
				continue;	
			}else
			{
				break;
			}
		}while(true);
		xs.at(ind) = x;
		ind++;
	
		//Pick new centroid
		for (int j = 0; j < Nv; j++)
		{
			centroids[i][j] = V[x][j];
		}
	}
	//---------------------------Pick Nc random centers-------------------------

	cout << "Begin Clustering..." << endl;
	double cumulative_dist;
	double last_c_dist = 0.0;
	register double tol;
	do
	{
		cumulative_dist = 0.0;
		//---------------------------Cluster Points---------------------------------
		//Calculate Euclidian distances of each point to every cluster centroid
		//add the minimum ED to a local sum for tol computation
		for (int i = 0; i < N; i++)
		{
			float min_dist = 1000.0;
			register float temp;
			for (int j = 0; j < Nc; j++)
			{
				temp = vectors_distance(V[i], centroids[j]);
				
				if (temp < min_dist)
				{
					min_dist = temp;
					classes[i] = j;
				}
			}
			cumulative_dist += min_dist;
		}
		
		//find points assigned to this cluster
		find_indexes(classes);

		//compute new tolerance (normalized)
		tol = fabs(cumulative_dist - last_c_dist)/(cumulative_dist + last_c_dist);
		
		cout << "tol: " << tol << endl;
		last_c_dist = cumulative_dist;
	}while( tol > THR_KMEANS);

    return 0;
};
