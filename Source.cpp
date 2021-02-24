#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <random>
//#include "priorityQueue.h"
#include <typeinfo>

using namespace std;

int bincoeff(int N, int R)
{
	// Calc N/1*(N-1)/2*(N-2)/3*... for quicker computation
	// rather than using factorials
	if (R == 0)
	{
		return 1;
	}

	int out = 1;
	for (int i = 1; i <= R; i++)
	{
		out *= N - i + 1;
		out /= i;
	}

	return out;

}

struct edge {
	int index;
	float dist = 10000000;
	struct edge *next;
};


float get_distance(vector<float> point1, vector<float> point2, int dimension, int v, int to, vector<vector<float>> node, bool use_sqrt = false) {
	float sum = 0;
	if (dimension == 0) {
		return node[v][to];
	}
	else {
		for (int i = 0; i < point1.size(); ++i)
			sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
	}
	if (use_sqrt)
		return sqrt(sum);
	return sum;
}

//int prims(vector<vector<float>> nodes, int points) {
//	vector<int> dist(points, 10000000);
//	vector<bool> visited(points, false);
//	PriorityQueue H(points);
//	edge s;
//	int tot_edge = 0;
//	s.dist = 0;
//	s.index = 0;
//	visited[s.index] = true;
//	dist[s.index] = 0;
//	//H.add(s);
//	vector<int> path(points);
//
//	// NOT WORKING - NEED TO CHANGE PRIORITY QUEUE
//	// TO TAKE STRUCT 'EDGE'
//	for (int i = 0; i < points || H.empty(); ++i) {
//		edge v;
//		//v = H.deletemin();
//
//		for (int k = 0; k < points; ++k) {
//			if (visited[k] != true) {
//				edge w;
//				w.index = k;
//
//				int vw = get_distance(nodes[v.index], nodes[k]);
//				if (w.dist > vw) {
//					w.dist = vw;
//					dist[k] = vw;
//					//H.add(w);
//				}
//			}
//		}
//
//		visited[v.index] = true;
//		tot_edge += v.dist;
//	
//	}
//
//	return tot_edge;
//}

// TEMPORARY
const int INF = 100000; // weight INF means there is no edge

struct Edge {
	float w = INF;
	int to = -1;
};
// TEMPORARY
void temp_mst(vector<vector<float>> node, int numpoints, bool dodist, int dimension) {
	float total_weight = 0;
	vector<bool> selected(numpoints, false);
	vector<Edge> min_e(numpoints);
	min_e[0].w = 0;
	float max_edge = 0;

	for (int i = 0; i < numpoints; ++i) {
		int v = -1;
		for (int j = 0; j < numpoints; ++j) {
			if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
				v = j;
		}

		if (min_e[v].w == INF) {
			cout << "No MST!" << endl;
			exit(0);
		}

		selected[v] = true;
		total_weight += min_e[v].w;
		if (min_e[v].to != -1) {
			//	cout << v << " " << min_e[v].to << endl;
			if (min_e[v].w > max_edge) {
				max_edge = min_e[v].w;
			}
		}

		if (dodist) {
			for (int to = 0; to < numpoints; ++to) {
				float dnt = get_distance(node[v], node[to], dimension, v, to, node, true);
				if (dnt < min_e[to].w) {//adj[v][to] < min_e[to].w) 
					min_e[to] = { dnt, v };
					
				}
			}
		}
		else {
			for (int to = 0; to < numpoints; ++to) {
				if (node[v][to] < min_e[to].w) {
					min_e[to] = { node[v][to], v };
				}
			}
		}
	}

	//cout << total_weight << endl;

	//cout << "Points & Max edge: " << endl;
	//cout << numpoints << endl;
	cout << max_edge << endl;
}

int main() // int& test, int& numpoints, int& numtrials, int& dimension)
{
	// Init variables
	int points;
	int numtrials;
	int dimensions;

	// Init random device and seed
	random_device rd;
	mt19937 gen(rd());
	// Gen uniform dist between 0, 1
	uniform_real_distribution<> dis(0, 1);


	// For quick testing
	cout << "Enter number of points:";
	cin >> points;

	cout << "Enter number of trials:";
	cin >> numtrials;

	cout << "Enter dimension:";
	cin >> dimensions;


	std::vector<int> graph(bincoeff(points, 2));
	std::vector<int> coords(dimensions);

	for (int k = 10; k < points; k += 50) {
		// Iterate and generate coordinates
		vector<vector<float>> nodes(k);
		int dim = 0;
		if (dimensions == 0) {
			for (int i = 0; i < k; i++) {
				vector<float> new_point(k);
				for (int j = 0; j < k; j++) {
					new_point.push_back(0);
				}
				nodes.push_back(new_point);
			}

			for (int i = 0; i < k; i++) {
				for (int j = 0; j < k; j++) {
					float val = dis(gen);
					nodes[i][j]; //.back().push_back(dis(gen));//dis(gen));
					nodes[j][i];
				}
			}
		}
		else {
			for (int i = 0; i < k; i++) {
				vector<float> new_point(dimensions);
				nodes.push_back(new_point);
				for (int j = 0; j < dimensions; j++) {
					nodes[i].push_back(dis(gen)); //.back().push_back(dis(gen));//dis(gen));
				}

			}
		}

		// For testing - print out nodes to make sure distance is correct
		/*for (int i = 0; i < points; i++) {
			for (auto it = nodes[i].begin(); it != nodes[i].end(); it++) {
				cout << *it << " ";
			}
			cout << endl;
		}*/

		//cout << "Begin MST:" << endl;
		// Just an example to make sure dist is correct
		//cout << "Dist:" << endl;
		//cout << get_distance(nodes[0], nodes[1], true);

		vector<vector<float>> tmp_nodes = { {10000, 1, 10000, 3, 10000, 10000, 10000, 10000, 10000, 10000},
											{1, 10000, 5, 10000, 5, 10000, 10000, 10000, 10000},
											{10000, 5, 10000, 10000, 10000, 2, 10000, 10000, 10000},
											{3, 10000, 10000, 10000, 4, 10000, 2, 10000, 10000},
											{10000, 5, 10000, 4, 10000, 1, 10000, 5, 10000},
											{10000, 10000, 2, 10000, 1, 10000, 10000, 10000, 7},
											{10000, 10000, 10000, 2, 10000, 10000, 10000, 3, 10000},
											{10000, 10000, 10000, 10000, 5, 10000, 3, 10000, 6},
											{10000, 10000, 10000, 10000, 10000, 7, 10000, 6, 10000} };

		//temp_mst(tmp_nodes, 9, false);
		temp_mst(nodes, k, true, dimensions);
	}

	return 0;
}
