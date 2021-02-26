#ifndef RANDMST
#define RANDMST

#include <vector>
#include <math.h>

using namespace std;

class Randmst {
public:
    Randmst(int numPoints, int flag, int numDimensions);
    ~Randmst();
    struct node;
    float prim(node* source_node, int dimensions, int flag, int n);
    float get_distance(node* node1, node* node2, bool use_sqrt);
    void generate_edges(vector<node*> nodes, int flag, int dim, float max_length);
    vector<node*> generate_nodes(int dimensions, int points, unsigned int seed);
    float get_run();

    struct coordinate {
        vector<float> coordinates;
    };

    struct closest_connected {
        vector<node*> connected;
    };

    struct close_nodes {
        vector<node*> connected;
    };

    struct node {
        close_nodes* neighbor_nodes = nullptr;
        coordinate* coordinates = nullptr;
        node* closest_connected = nullptr;
        float closest_distance = INFINITY;

        node() {
            close_nodes* new_neighbor = new close_nodes();
            neighbor_nodes = new_neighbor;
        }
    };

private:
    float run;
};
#endif
