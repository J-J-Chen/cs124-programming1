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
  //printf("Bout to make nodes\n");
  //printf("numDim: %d\n",numDimensions);
  vector<node*> nodes = generate_nodes(numDimensions, numPoints, time(NULL));
  //printf("Bout to make edges\n");
  generate_edges(nodes, 1);
  //printf("Made edges\n");
  run = prim(nodes[0], numDimensions, numPoints);
}

int main(int argc, char *argv[]) {
  if(argc < 5) {
    printf("ERROR: Too few arguments. Please use the form: \n");
    printf("./randmst flag numPoints numTrials numDimensions \n");
    return 1;
  }
  int flag = atoi(argv[1]);
  int numPoints = atoi(argv[2]);
  int numTrials = atoi(argv[3]);
  int numDimensions = atoi(argv[4]);

  float total = 0;
  for(int i = 0; i< numTrials; ++i) {
    Randmst randmst(numPoints, numDimensions);
    float sing_run = randmst.get_run();
    total += sing_run;
    printf("Run #%d got: %f\n", i+1, sing_run);
  }
  printf("Average: %f\n", total/numTrials);
}

float Randmst::prim(node *root_node, int dimensions, int n) {
  float total_dist = 0;
  PriorityQueue queue(100*n);
  root_node->closest_distance = 0;
  node *to_add = root_node;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < to_add->neighbor_nodes->connected.size(); ++j) {
      float dist = get_distance(to_add, to_add->neighbor_nodes->connected[j], true);
      if(dist < to_add->neighbor_nodes->connected.at(j)->closest_distance) {
        to_add->neighbor_nodes->connected[j]->closest_distance = dist;
        queue.add(to_add->neighbor_nodes->connected[j]); //The new point is closer. May have to delete old
        //printf("ADDED TO QUEUE: %f\n", to_add->neighbor_nodes->connected[j]->closest_distance);
      }
    }
    //total_dist += sqrt(to_add->closest_distance); //Add the total dist
    //printf("MADE IT HERE\n");
    total_dist += to_add->closest_distance;
    //printf("TOTAL DIST: %f\n", total_dist);
    //printf("TO ADD BEFORE: %f\n", to_add->closest_distance);
    to_add->closest_distance = -1; //Shows that it has been added to the mst
    //printf("TO ADD Later: %f\n", to_add->closest_distance);
    to_add = queue.pop();
    //printf("TO ADD after pop: %f\n", to_add->closest_distance);
    while(to_add->closest_distance < 0) {
      if(to_add == nullptr) break;
      //printf("Bleep: %f\n",to_add->closest_distance);
      to_add = queue.pop();
      if(to_add == nullptr) break;
    }
    //printf("FINSIH A POINT SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSss\n");
    //if(to_add == nullptr) printf("STOOOOOOOOOOOOOOOOOOOOOOP\n");
  }
  //printf("FINISH\n");
  //printf("COUNT: %f\n", total_dist/count);
  return total_dist;
}

/**
 * Generates a vector of nodes randomly
 * @param dimensions Number of dimensions the points are in
 * @param points The number of points to be generated
 * @param seed Optional seed for testing. Default random
 * @return Returns a vector of nodes
 */
vector<Randmst::node*> Randmst::generate_nodes(int dimensions, int points, unsigned int seed = time(NULL)) {
  srand(seed);
  vector<node*> nodes;
  for(int i = 0; i < points; ++i) {
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
      float dist = get_distance(nodes[i], nodes[j], true);
      //printf("Dist: %f\n", dist);
      if(dist < max_length * max_length) {
        if(nodes[i]->neighbor_nodes == nullptr) {
          close_nodes *new_neighbors = new close_nodes();
          vector<node*> new_node_lst;
          new_neighbors->connected = new_node_lst;
          nodes[i]->neighbor_nodes = new_neighbors;
        }
        if(nodes[j]->neighbor_nodes == nullptr) {
          close_nodes *new_neighbors = new close_nodes();
          vector<node*> new_node_lst;
          new_neighbors->connected = new_node_lst;
          nodes[j]->neighbor_nodes = new_neighbors;
        }
        nodes[i]->neighbor_nodes->connected.push_back(nodes[j]);
        nodes[j]->neighbor_nodes->connected.push_back(nodes[i]);
      }
    }
    //printf("GOT NEIGHBORS: %d\n", nodes[i]->neighbor_nodes->connected.size());
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
  if(node1->coordinates->coordinates.size() == 0) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    return dis(gen);
  }
  for(int i = 0; i < node1->coordinates->coordinates.size(); ++i) {
    float val = (node1->coordinates->coordinates[i] - node2->coordinates->coordinates[i]);
    sum += val * val;
  }
  if(use_sqrt)
    return sqrt(sum);
  return sum;
}

float Randmst::get_run() {
  return run;
}

