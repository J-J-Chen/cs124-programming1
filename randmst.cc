#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include "priorityQueue.h"

using namespace std;

vector<vector<float>> generate_nodes(int dimensions, int points);
float prim(vector<vector<float>> nodes, int dimensions, int n);
float get_distance(vector<float> point1, vector<float> point2, bool use_sqrt);

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

float prim(vector<vector<float>> nodes, int dimensions, int n) {
  return 0.0;
}

/**
 * Generates a vector of random nodes
 * @param dimensions Number of dimensions the points are in
 * @param points The number of points to be generated
 * @param seed Optional seed for testing. Default random
 * @return Returns a vector of points containing a vector of coordinates
 */
vector<vector<float>> generate_nodes(int dimensions, int points, unsigned int seed = time(NULL)) {
  srand(seed);
  vector<vector<float>> nodes;
  for(int i = 0; i < points; ++i) {
    vector<float> new_point;
    nodes.push_back(new_point);
    for(int j = 0; j < dimensions; ++j) {
      nodes.back().push_back(rand());
    }
  }
  return nodes;
}

/**
 * Gets the distance between two points
 * @param point1 The first point whose distance is to be calculated
 * @param point2 The second point whose distance is to be calculated
 * @param use_sqrt false will return the sum of coordinates while true returns Euclidian distance
 * between point1 and point2
 * @return Returns either the sum of coordinates or the Euclidian distance between the points
 */
float get_distance(vector<float> point1, vector<float> point2, bool use_sqrt = false) {
  float sum = 0;
  for(int i = 0; i < point1.size(); ++i)
    sum += point1[i] + point2[i];
  if(use_sqrt)
    return sqrt(sum);
  return sum;
}

