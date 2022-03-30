#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

namespace plt = matplotlibcpp;

//Number of point vectors
const int N = 100000;
//Number of point dimensions
const int Nv = 2;
//Number of clusters
const int Nc = 100;
//Point area
const int XY = 1000;


//Point Vectors
std::vector<std::vector<double>> V( N , vector<double> (Nv, -1));
//std::vector<int> V[N][Nv];

//Cluster Centers
std::vector<std::vector<double>> centroids( Nc , vector<double> (Nv, 0));
//std::vector<int> centroids[Nc][Nv];

//Classes
std::vector<int> classes(N, -1);

//http://www.cplusplus.com/forum/general/209784/
double	vectors_distance(std::vector<double> a, std::vector<double> b)
{
	double temp = 0;
	for (int i = 0; i < Nv; i++)
	{
		temp += (a[i] - b[i]) * (a[i] - b[i]);
	}
	return  sqrt(temp);
};

int* find_indexes(std::vector<int> vec, int j)
{

	static int vec2[N];
	for(int i = 0; i < N; i++)
		vec2[i] = -1;
	int ind = 0;
	for (int i = 0; i < N; i++)
	{
		//cout << vec[i] << "," << j << endl;
		if (vec[i] == j)
		{
			vec2[ind] = i;
			ind++;
		}
	}	

	/*
	for (int i = 0; i < N; i++)
		std::cout << vec2[i] << ' ';
	cout << endl;
	*/
	return vec2;
}
//*
void compute_new_center(int * vec, int j)
{
	int k;
	double tempx = 0.0;
	double tempy = 0.0;
	for (k = 0; k < N; k++)
	{
		//cout << vec[k] << endl;
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
	//cout << tempx << "," << tempy << endl;
	centroids[j][0] = tempx;
	centroids[j][1] = tempy;
}

void plot(void)
{
	//Plot centroids
	std::vector<double> xss(Nc), yss(Nc);
	for(int i = 0; i < Nc; i++)
	{
		xss.at(i) = centroids[i][0];
		yss.at(i) = centroids[i][1];
	}

	//Plot Points
	std::vector<double> pxs(N), pys(N);
	for(int i = 0; i < N; i++)
	{
		pxs[i] = V[i][0];
		pys[i] = V[i][1];
	}

	plt::plot(pxs, pys, "bo", xss, yss, "r*");
	plt::show();
}

int main(void)
{
	//Seed rand()
	//set this for random iteration
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
		//cout << V[i][0] << "," << V[i][1] << endl;
	}
	//cout << "---------------------------" << endl;
	
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
				//cout << "in xs" << endl;
				continue;	
			}else{
				//cout << "not in xs" << endl; 
				break;
			}
		}while(true);
		//cout << "-----------------------" << endl;
		xs.at(ind) = x;
		ind++;
	
		//Pick new centroid
		for (int j = 0; j < Nv; j++)
		{
			centroids[i][j] = V[x][j];
		}
		//cout << centroids[i][0] << "," << centroids[i][1] << endl;
		//*/
		


	}
	//---------------------------Pick Nc random centers-------------------------

	double cumulative_dist;
	double last_c_dist = 0.0;
	double tol;
	do
	{
		cumulative_dist = 0.0;
		//---------------------------Cluster Points---------------------------------
		//Calculate Euclidian distances of each point to every cluster centroid
		for (int i = 0; i < N; i++)
		{
			double min_dist = 1000.0;
			double temp;
			for (int j = 0; j < Nc; j++)
			{
				temp = vectors_distance(V[i], centroids[j]);
				
				//cout << cumulative_dist << endl;
				if (temp < min_dist)
				{
					//cout << temp << "--" << min_dist << "  ";
					min_dist = temp;
					classes[i] = j;
				}
			}
			cumulative_dist += min_dist;
			//cout << endl;
		}
		/*
		for (std::vector<int>::const_iterator i = classes.begin(); i != classes.end(); i++)
			std::cout << *i << ' ';
		cout << endl;
		*/
		
		for (int j = 0; j < Nc; j++)
		{
			//find points assigned to this cluster
			int * vec = find_indexes(classes, j);
			//Compute new cluster centroid
			compute_new_center(vec, j);
		}

		tol = fabs(cumulative_dist - last_c_dist)/(cumulative_dist + last_c_dist);
		
		//cout << "c_dist: " << cumulative_dist << endl;
		//cout << "last_c_dist: " << last_c_dist << endl;
		cout << "tol: " << tol << endl;
		last_c_dist = cumulative_dist;
	}while( tol > 0.0001);
	
	plot();
    return 0;
};
