#include "baitaprr.h"


// Khoi tao hang doi
void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}


// Kiem tra hang doi rong
bool isQueueEmpty(Queue* queue) {
    return queue->front == -1;
}


// Them phan tu vao hang doi
void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX_VERTICES - 1) {
        printf("Hang doi da day.\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;
    }

    queue->rear++;
    queue->data[queue->rear] = value;
}


// Xoa phan tu khoi hang doi
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Hang doi trong.\n");
        return -1;
    }

    int value = queue->data[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    else {
        queue->front++;
    }

    return value;
}

//Doc ma tran tu File
void File(Graph* graph)
{
    FILE* f = fopen("Text.txt", "r");
    if (f == NULL)
    {
        printf("Khong mo duoc file");
        return;
    }
    else
    {
        if (fscanf(f, "%d\n", &(graph->numVertices)) != 1)
        {
            printf("Loi khi doc so dinh\n");
            fclose(f);
            return;
        }

        for (int i = 0; i < graph->numVertices; i++)
        {
            for (int j = 0; j < graph->numVertices; j++)
            {
                if (fscanf(f, "%d", &graph->graph[i][j]) != 1)
                {
                    printf("Loi khi doc ma tran\n");
                    fclose(f);
                    return;
                }
            }
        }
    }
    fclose(f);
}


//In ma tran 
void printGraph(Graph* graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%-5d", graph->graph[i][j]);
        }
        printf("\n");
    }
}


// Khoi tao do thi
void initGraph(Graph* graph, int MAX)
{

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->graph[i][j] = 0;// all cac phan tu trong ma tran " graph" thanh 0
        }
    }
}


// Them canh vao do thi
int addEdge(Graph* graph, int source, int destination) {
    if (graph->graph[source][destination] == 0 && graph->graph[destination][source] == 0)
    {
        graph->graph[source][destination] = 1;
        // do thi vo huong
        graph->graph[destination][source] = 1;
        return 1;
    }
    else
        return 0;
}


// Duyet do thi theo DFS
void dfs(Graph* graph, int startVertex, bool visited[]) {
    visited[startVertex] = true;// Danh dau da tham
    printf("%d ", startVertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->graph[startVertex][i] && !visited[i]) {
            dfs(graph, i, visited);// Tỉep tuc duyet dinh ke chua tham
        }
    }
}


// Duyet do thi theo BFS
void bfs(Graph* graph, int startVertex, bool visited[]) {
    Queue queue;
    initQueue(&queue);

    visited[startVertex] = true;
    printf("%d ", startVertex);
    enqueue(&queue, startVertex);

    while (!isQueueEmpty(&queue)) {
        int currentVertex = dequeue(&queue);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->graph[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                printf("%d ", i);
                enqueue(&queue, i);
            }
        }
    }
}


// Kiem tra tinh lien thong cua do thi
int isConnected(Graph* graph) {
    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool)); // Mang danh dau all cac dinh da tham

    // Tim mot dinh bat ky va thuc hien duyet dfs tu dinh do
    int startVertex = 0;
    dfs(graph, startVertex, visited);

    //KIem tra xem all các dinh da tham hay chua
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            free(visited);
            return 0; // Do thi khong len thong 
        }
    }

    free(visited);
    return 1; // Do thi len thong 
}


// Tim duong di ngan nhat tu nguon den tat ca cac dinh su dung thuat toan Dijkstra
DijkstraResult dijkstra(Graph* graph, int source) {
    DijkstraResult result;
    //Khoi tao khoang cach cua all cac dinh tu nguon la vo cuc and khong co dinh nao duoc tham
    for (int i = 0; i < graph->numVertices; i++) {
        result.distance[i] = INT_MAX;
        result.visited[i] = false;
        result.parent[i] = -1;
    }
    // Khoang cach tu nguon den chinh no la 0
    result.distance[source] = 0;
    //Tim duong di ngan ngat cho all ca cac dinh 
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u;
        int minDistance = INT_MAX;

        for (int i = 0; i < graph->numVertices; i++) {
            if (!result.visited[i] && result.distance[i] < minDistance) {
                minDistance = result.distance[i];
                u = i;
            }
        }

        result.visited[u] = true;

        for (int v = 0; v < graph->numVertices; v++) {
            if (!result.visited[v] && graph->graph[u][v] && result.distance[u] != INT_MAX &&
                result.distance[u] + graph->graph[u][v] < result.distance[v])
            {
                result.distance[v] = result.distance[u] + graph->graph[u][v];
                result.parent[v] = u;
            }
        }
    }

    return result;
}


// In duong di ngan nhat tu nguon den mot dinh cu the
void printShortestPath(DijkstraResult result, int destination) {
    if (result.parent[destination] == -1) {
        printf("%d ", destination);
        return;
    }

    printShortestPath(result, result.parent[destination]);
    printf("-> %d ", destination);
}

//6
// tim chu trinh ngan nhat(BFS)
int hasCycle(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = { 0 };
    int parent[MAX_VERTICES] = { -1 };
    Queue queue;
    initQueue(&queue);

    visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    while (!isQueueEmpty(&queue)) {
        int currentVertex = dequeue(&queue);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->graph[currentVertex][i]) {
                if (!visited[i]) {
                    visited[i] = 1;
                    enqueue(&queue, i);
                    parent[i] = currentVertex;
                }
                else if (parent[currentVertex] != i) {
                    // Tim thay chu trinh
                    // In ra chu trinh ngan nhat
                    printf("Chu trinh ngan nhat: ");
                    int vertex = currentVertex;
                    while (vertex != startVertex) {
                        printf("%d ", vertex);
                        vertex = parent[vertex];
                    }
                    printf("%d\n", startVertex);

                    return 1;
                }
            }
        }
    }

    return 0;  // Khong tim thay chu trinh
}


// Tim dinh co khoang cach nho nhat chua duoc duyet
int findMinDistance(int distance[], bool visited[], int numVertices) {
    int min = INT_MAX, minIndex;
    int i;
    for (i = 0; i < numVertices; i++) {
        if (visited[i] == false && distance[i] < min) {
            min = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}


// Tinh tong do dai duong di ngan nhat tu dinh nguon den tat ca cac dinh
void totalDistance(Graph* graph, int source,DijkstraResult &result) {
    bool visited[MAX_VERTICES];
    int i, j;

    for (i = 0; i < graph->numVertices; i++) {
        result.distance[i] = INT_MAX;
        visited[i] = false;
        result.parent[i] = -1;
    }

    result.distance[source] = 0;

    for (i = 0; i < graph->numVertices - 1; i++) {
        int minIndex = findMinDistance(result.distance, visited, graph->numVertices);// Tim dinh co khoang cach nho nhat chua duoc duyet
        visited[minIndex] = true;

        for (j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && graph->graph[minIndex][j] != 0 &&
                result.distance[minIndex] != INT_MAX &&
                result.distance[minIndex] + graph->graph[minIndex][j] < result.distance[j])
            {
                result.distance[j] = result.distance[minIndex] + graph->graph[minIndex][j];
                result.parent[j] = minIndex;
            }
        }

    }
}