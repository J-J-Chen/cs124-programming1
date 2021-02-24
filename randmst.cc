#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <random>
#include "priorityQueue.h"
#include "randmst.h"

using namespace std;

Randmst::~Randmst() {}

Randmst::Randmst(int numPoints, int numDimensions) {
  printf("Bout to make nodes\n");
  printf("numDim: %d\n",numDimensions);
  vector<node*> nodes = generate_nodes(numDimensions, numPoints, time(NULL));
  printf("Bout to make edges\n");
  generate_edges(nodes, 10);
  printf("Made edges\n");
  average = prim(nodes[0], numDimensions, numPoints);
}

int main(int argc, char *argv[]) {
  if(argc < 5) {
    printf("ERROR: Too few arguments. Please use the form: \n");
    printf("./randmst flag numPoints numTrials numDimensions \n");
    return 1;
  }
  int flag = atoi(argv[1]);
  int numPoints = atoi(argv[2]);
  int numTrails = atoi(argv[3]);
  int numDimensions = atoi(argv[4]);

  printf("numDim)))): %s\n", argv[4]);

  Randmst randmst(numPoints, numDimensions);
  randmst.print_average();
}

float Randmst::prim(node *root_node, int dimensions, int n) {
  float total_dist = 0;
  PriorityQueue queue(n);// = new PriorityQueue(n);
  node *to_add = root_node;
  printf("SDFSD\n");
  printf("%d\n", root_node->neighbor_nodes == nullptr);
  printf("SDFSD\n");
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < to_add->neighbor_nodes->connected.size(); ++j) {
      printf("YAY\n");
      float dist = get_distance(to_add, to_add->neighbor_nodes->connected[j], false);
      if(dist < to_add->neighbor_nodes->connected.at(j)->closest_distance) {
        to_add->neighbor_nodes->connected[j]->closest_distance = dist;
        queue.add(to_add->neighbor_nodes->connected[j]); //The new point is closer. May have to delete old
      }
    }
    total_dist += sqrt(to_add->closest_distance); //Add the total dist
    to_add->closest_distance = -1; //Shows that it has been added to the mst
    to_add = queue.pop();
    while(to_add->closest_distance < 0) {
      to_add = queue.pop();
    }
  }
  return total_dist/n;
}

/**
 * Generates a vector of nodes randomly
 * @param dimensions Number of dimensions the points are in
 * @param points The number of points to be generated
 * @param seed Optional seed for testing. Default random
 * @return Returns a vector of nodes
 */
vector<Randmst::node*> Randmst::generate_nodes(int dimensions, int points, unsigned int seed = time(NULL)) {
  printf("Hello: %d, %d\n", dimensions, points);
  srand(seed);
  vector<node*> nodes;
  printf("made nodes\n");
  for(int i = 0; i < points; ++i) {
    printf("Number: %d\n", i);
    node *new_node = new node();
    coordinate *new_coordinate = new coordinate();
    vector<float> coordinates;
    nodes.push_back(new_node);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    for(int j = 0; j < dimensions; ++j) {
      coordinates.push_back(dis(gen));
    }
    new_coordinate->coordinates = coordinates;
    new_node->coordinates = new_coordinate;
  }
  return nodes;
}

void Randmst::generate_edges(vector<node*> nodes, float max_length = 1) {
  for(int i = 0; i < nodes.size(); ++i) {
    for(int j = i + 1; j < nodes.size(); ++j) {
      float dist = get_distance(nodes[i], nodes[j], false);
      printf("Dist: %f\n", dist);
      if(dist < max_length * max_length) {
        if(nodes[i]->neighbor_nodes == nullptr) {
          close_nodes *new_neighbors = new close_nodes();
          nodes[i]->neighbor_nodes = new_neighbors;
        }
        if(nodes[j]->neighbor_nodes == nullptr) {
          close_nodes *new_neighbors = new close_nodes();
          nodes[j]->neighbor_nodes = new_neighbors;
        }
        printf("PUSHED BACK\n");
        nodes[i]->neighbor_nodes->connected.push_back(nodes[j]);
        printf("FIRST\n");
        nodes[j]->neighbor_nodes->connected.push_back(nodes[i]);
        printf("SECOND\n");
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
float Randmst::get_distance(node *node1, node *node2, bool use_sqrt = false) {
  float sum = 0;
  printf("SDFDSF %f\n", node1->coordinates->coordinates[0]);
  if(node1->coordinates->coordinates.size() == 1)
    return abs(node1->coordinates->coordinates[0] - node2->coordinates->coordinates[0]);
  for(int i = 0; i < node1->coordinates->coordinates.size(); ++i)
    sum += node1->coordinates->coordinates[i] + node2->coordinates->coordinates[i];
  if(use_sqrt)
    return sqrt(sum);
  return sum;
}

void Randmst::print_average() {
  printf("Average: %f", average);
}

