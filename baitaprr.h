#ifndef baitaprr_h
#define baitaprr_h
#define MAX_VERTICES 100

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


struct Queue {
    int data[MAX_VERTICES];
    int front, rear;
};

struct  DijkstraResult {
    int distance[MAX_VERTICES];
    int parent[MAX_VERTICES];
    bool visited[MAX_VERTICES];
};

struct  Graph {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

void File(Graph* graph);
void printGraph(Graph* graph);
void initQueue(Queue* queue);
bool isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void initGraph(Graph* graph, int numVertices);
int addEdge(Graph* graph, int source, int destination);
void dfs(Graph* graph, int startVertex, bool visited[]);
void bfs(Graph* graph, int startVertex, bool visited[]);
DijkstraResult dijkstra(Graph* graph, int source);
void printShortestPath(DijkstraResult result, int destination);
int hasCycle(Graph* graph, int startVertex);
int findMinDistance(int distance[], bool visited[], int numVertices);
void totalDistance(Graph* graph, int source, DijkstraResult& result);
int isConnected(Graph* graph);

#endif