#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "priorityQueue.h"
#include "randmst.h"

using namespace std;

Randmst::~Randmst() {}

int main(int argc, char *argv[]) {
  if(argc < 5) {
    printf("ERROR: Too few arguments. Please use the form: \n");
    printf("./randmst flag numPoints numTrials numDimensions \n");
    return 1;
  }
  int flag = *argv[1];
  int numPoints = *argv[2];
  int numTrails = *argv[3];
  int numDimensions = *argv[4];

  //vector<vector<float>> nodes = generate_nodes(numDimensions, numPoints);
  //float mst = prim(nodes, numDimensions, numPoints);
  //printf("Average mst: %f", mst/(numPoints - 1));
}

float Randmst::prim(node *root_node, int dimensions, int n) {
  //PriorityQueue queue(n);
  return 0.0;
}

/**
 * Generates a vector of nodes randomly
 * @param dimensions Number of dimensions the points are in
 * @param points The number of points to be generated
 * @param seed Optional seed for testing. Default random
 * @return Returns a vector of nodes
 */
vector<Randmst::node> Randmst::generate_nodes(int dimensions, int points, unsigned int seed = time(NULL)) {
  srand(seed);
  vector<node> nodes;
  for(int i = 0; i < points; ++i) {
    node *new_node = new node();
    coordinate *new_coordinate = new coordinate();
    vector<float> coordinates;
    nodes.push_back(*new_node);
    for(int j = 0; j < dimensions; ++j) {
      coordinates.push_back(rand());
    }
    new_coordinate->coordinates = coordinates;
    *new_node->coordinates = *new_coordinate;
  }
  return nodes;
}

void Randmst::generate_edges(vector<node> nodes, float max_length = 1) {
  for(int i = 0; i < nodes.size(); ++i) {
    for(int j = i + 1; j < nodes.size(); ++j) {
      float dist = get_distance(nodes[i], nodes[j], false);
      if(dist < max_length * max_length) {
        nodes[i].neighbor_nodes->connected.push_back(nodes[j]);
        nodes[j].neighbor_nodes->connected.push_back(nodes[i]);
      }
    }
  }
}


/**
 * Gets the distance between two points
 * @param point1 The first point whose distance is to be calculated
 * @param point2 The second point whose distance is to be calculated
 * @param use_sqrt false will return the sum of coordinates while true returns Euclidian distance
 * between point1 and point2
 * @return Returns either the sum of coordinates or the Euclidian distance between the points
 */
float Randmst::get_distance(node node1, node node2, bool use_sqrt = false) {
  float sum = 0;
	float diff;
	for (int i = 0; i < node1.coordinates->coordinates.size(); ++i)
		diff = (node1.coordinates->coordinates[i] - node2.coordinates->coordinates[i]);
		sum += (diff*diff);
	if (use_sqrt)
		return sqrt(sum);
	return sum;
}

