#include <vector>
#include <random>
#include <math.h>
#include "priorityQueue.h"
#include <time.h>
#include "randmst.h"

using namespace std;

Randmst::~Randmst() {}

Randmst::Randmst(int numPoints, int flag, int numDimensions) {
    vector<node*> nodes = generate_nodes(numDimensions, numPoints, time(NULL));
    float cutoff = 0.45*exp(numPoints*-0.00002);
    generate_edges(nodes, flag, cutoff);
    run = prim(nodes[0], numDimensions, flag, numPoints);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("ERROR: Too few arguments. Please use the form: \n");
        printf("./randmst flag numPoints numTrials numDimensions \n");
        return 1;
    }
    int flag = atoi(argv[1]);
    int numPoints = atoi(argv[2]);
    int numTrials = atoi(argv[3]);
    int numDimensions = atoi(argv[4]);

    float total = 0;
    for (int i = 0; i < numTrials; ++i) {
        Randmst randmst(numPoints, flag, numDimensions);
        float sing_run = randmst.get_run();
        total += sing_run;
    }
    printf("%f %d %d %d\n", total / numTrials, numPoints, numTrials, numDimensions);
}

float Randmst::prim(node* root_node, int dimensions, int edge_max, int n) {
    float total_dist = 0;
    PriorityQueue queue(100 * n);
    root_node->closest_distance = 0;
    node* to_add = root_node;
    float max_edge = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < to_add->neighbor_nodes->connected.size(); ++j) {
            float dist = get_distance(to_add, to_add->neighbor_nodes->connected[j], true);
            if (dist < to_add->neighbor_nodes->connected.at(j)->closest_distance) {
                to_add->neighbor_nodes->connected[j]->closest_distance = dist;
                queue.add(to_add->neighbor_nodes->connected[j]); //The new point is closer. May have to delete old
            }
        }

        //Condition to keep track of longest edge for testing/optimization purposes
        if (to_add->closest_distance > max_edge) {
            max_edge = to_add->closest_distance;
        }

        total_dist += to_add->closest_distance;
        to_add->closest_distance = -1; //Shows that it has been added to the mst
        to_add = queue.pop();
        while (to_add->closest_distance < 0) {
            if (to_add == nullptr) break;
            to_add = queue.pop();
            if (to_add == nullptr) break;
        }
    }

    if (edge_max == 1) {
        return max_edge;
    }

    return total_dist;
}

/**
 * Generates a vector of nodes randomly
 * @param dimensions Number of dimensions the points are in
 * @param points The number of points to be generated
 * @param seed Optional seed for testing. Default random
 * @return Returns a vector of nodes
 */
vector<Randmst::node*> Randmst::generate_nodes(int dimensions, int points, unsigned int seed) {
    srand(seed);
    vector<node*> nodes;
    for (int i = 0; i < points; ++i) {
        node* new_node = new node();
        coordinate* new_coordinate = new coordinate();
        vector<float> coordinates;
        nodes.push_back(new_node);
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        for (int j = 0; j < dimensions; ++j) {
            coordinates.push_back(dis(gen));
        }
        new_coordinate->coordinates = coordinates;
        new_node->coordinates = new_coordinate;
    }
    return nodes;
}

void Randmst::generate_edges(vector<node*> nodes, int flag, float max_length = 1) {
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i + 1; j < nodes.size(); ++j) {
            float dist = get_distance(nodes[i], nodes[j], true);
            if (dist < max_length) {
                if (nodes[i]->neighbor_nodes == nullptr) {
                    close_nodes* new_neighbors = new close_nodes();
                    vector<node*> new_node_lst;
                    new_neighbors->connected = new_node_lst;
                    nodes[i]->neighbor_nodes = new_neighbors;
                }
                if (nodes[j]->neighbor_nodes == nullptr) {
                    close_nodes* new_neighbors = new close_nodes();
                    vector<node*> new_node_lst;
                    new_neighbors->connected = new_node_lst;
                    nodes[j]->neighbor_nodes = new_neighbors;
                }
                nodes[i]->neighbor_nodes->connected.push_back(nodes[j]);
                nodes[j]->neighbor_nodes->connected.push_back(nodes[i]);
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
float Randmst::get_distance(node* node1, node* node2, bool use_sqrt = true) {
    float sum = 0;
    if (node1->coordinates->coordinates.size() == 0) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        return dis(gen);
    }
    for (int i = 0; i < node1->coordinates->coordinates.size(); ++i) {
        float val = (node1->coordinates->coordinates[i] - node2->coordinates->coordinates[i]);
        sum += val * val;
    }
    if (use_sqrt)
        return sqrt(sum);
    return sum;
}

float Randmst::get_run() {
    return run;
}
