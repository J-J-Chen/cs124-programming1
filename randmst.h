#ifndef RANDMST
#define RANDMST

#include <vector>
#include <math.h>

using namespace std;

class Randmst {
  public:
    ~Randmst();
  struct node;
  vector<node> generate_nodes(int dimensions, int points);
  float prim(node *source_node, int dimensions, int n);
  float get_distance(node node1, node node2, bool use_sqrt);
  void generate_edges(vector<node> nodes, float max_length);
  vector<node> generate_nodes(int dimensions, int points, unsigned int seed);
  
  struct coordinate {
    vector<float> coordinates;
  };
  
  struct closest_connected {
    vector<node> connected;
  };
  
  struct close_nodes {
    vector<node> connected;
  };
  
  struct node {
    close_nodes *neighbor_nodes = nullptr;
    coordinate *coordinates = nullptr;
    node *closest_connected = nullptr;
    float closest_distance = INFINITY;
  };
};
#endif

