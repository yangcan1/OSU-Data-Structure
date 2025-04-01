/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name:Can Yang
 * Email:yangca@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"
#include <math.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0


struct pq_entry {
    int node;
    int prev;
};
int n_nodes, n_edges;


void dijkstra(int Graph[n_nodes][n_nodes], int start_node) {
    float cost[n_nodes], prev[n_nodes];
    for (int i = 0; i < n_nodes; i ++) {
        cost[i] = INFINITY;
        prev[i] = -1;
    }
    struct pq *PQ = pq_create();
    struct pq_entry *first = malloc(sizeof(pq_entry));
    first
    pq_insert(PQ, first, 0);

}

int main(int argc, char const *argv[]) {
  /*
   * Write your code here to read the file `airports.dat` and to find the
   * least-cost paths from node 0 to all other nodes in the graph.  Make sure
   * to print out the least-cost paths you find at the end.
   */
    FILE *file = fopen(DATA_FILE, "r");
    fscanf(file, "%d %d", &n_nodes, &n_edges);
    int Graph[n_nodes][n_nodes];
    for (int i = 0; i < n_nodes; i++) {
        for (int j = 0; j < n_nodes; j++) {
            Graph[i][j] = 0;
        }
    }
        int from, to, cost;

    for (int i = 0; i < n_edges; i++) {
        fscanf(file, "%d %d %d", &from, &to, &cost);
        Graph[from][to] = cost;
    }
    fclose(file);
    dijkstra(Graph, START_NODE);

  return 0;
}
