#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

namespace plt = matplotlibcpp;

//Number of point vectors
#define N 1000//00
//Number of point dimensions
#define Nv 2//1000
//Number of clusters
#define Nc 50//100
//Tolerance
#define THR_KMEANS 0.000001

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
	std::vector<double>	auxiliary;

	std::transform (a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),
	[](double element1, double element2) {return (element1-element2)*(element1-element2);});//pow((element1-element2),2);});

	return  sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
};

int* find_indexes(std::vector<int> vec, int j)
{

	static int vec2[N];
	int ind = 0;
	for (int i = 0; i < N; i++)
	{
		vec2[i] = -1;
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
void compute_new_center(void)
{
	for (int j = 0; j < Nc; j++)
	{
		int * vec = find_indexes(classes, j);
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
}
//*/
// main function that doesn't receive any parameter and
// returns integer.
int main(void)
{




	//Seed rand()
	//srand (time(NULL));
	srand(1645283643);
	//cout << time(NULL) << endl;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Nv; j++)
		{
			V[i][j] = rand() % 30;
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
			//cout << x << endl;
			auto res = std::find(begin(xs), end(xs), x);
			/*
			for (std::vector<int>::const_iterator i = xs.begin(); i != xs.end(); i++)
				std::cout << *i << ' ';
			*/
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

//	double last_dist = 1000;
	int it_cnt = 0;
	float cumulative_dist;
	float last_c_dist = 0;
	double tol;
	do
	{
		cumulative_dist = 0;
		//---------------------------Cluster Points---------------------------------
		//Calculate Euclidian distances of each point to every cluster centroid
		for (int i = 0; i < N; i++)
		{
			double min_dist = 1000;
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
		//handle overflow
		if (cumulative_dist != cumulative_dist)
		{
			cumulative_dist = 1000000;
		}
		*/
		/*
		for (std::vector<int>::const_iterator i = classes.begin(); i != classes.end(); i++)
			std::cout << *i << ' ';
		cout << endl;
		*/
		/*
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

		//plt::scatter(xss, yss, "b+");//plt::plot(xss);//, yss, "r--");
		plt::plot(pxs, pys, "bo", xss, yss, "r*");
		plt::show();
		//*/

		//find points assigned to this cluster
		//int * vec = find_indexes(classes, j);
		//Compute new cluster centroid
		compute_new_center();
		/*
		//Compute new cluster centroid
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
		//*/


		it_cnt++;
		tol = fabs(cumulative_dist - last_c_dist);
		
		cout << "c_dist: " << cumulative_dist << endl;
		cout << "last_c_dist: " << last_c_dist << endl;
		cout << "tol: " << tol << endl;
		last_c_dist = cumulative_dist;
	}while( tol > THR_KMEANS);//while((it_cnt < maxit)&&( tol > 0.01));
    return 0;
};
