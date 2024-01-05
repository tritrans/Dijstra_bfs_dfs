#include "baitaprr.h"

void showmenu()
{
    printf("\n*********************************************************************\n");
    printf("\n*                      MENU                                         *");
    printf("\n*1. Them canh                                                       *");
    printf("\n*2. Duyet do thi theo DFS                                           *");
    printf("\n*3. Duyet do thi theo BFS                                           *");
    printf("\n*4. Tim duong di ngan nhat su dung Dijkstra                         *");
    printf("\n*5. Tim chu trinh ngan nhat (BFS)                                   *");
    printf("\n*6. Tong do dai duong di ngan nhat tu dinh dau den tat ca cac dinh  *");
    printf("\n*7. Kiem tra tinh lien thong cua do thi (DFS)                       *");
    printf("\n*********************************************************************\n");
}
int main()
{
    Graph graph;
    int distance[100];
    int numVertices, source, destination, startVertex, TS;
    initGraph(&graph, MAX_VERTICES);
    File(&graph);
    printf("Ma tran ke cua do thi:\n");
    printGraph(&graph);
    int choice;
    do {
        showmenu();
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: 
        {
            printf("Nhap dinh nguon: ");
            scanf("%d", &source);
            printf("Nhap dinh dich: ");
            scanf("%d", &destination);
            if (!addEdge(&graph, source, destination))
                printf("Canh (%d, %d) da ton tai", source, destination);
            else
            {
                printf("Ma tran ke cua do thi sau khi them canh (%d, %d):\n", source, destination);
                printGraph(&graph);
            }
            break;
        }
        case 2: 
        {
            bool visited[MAX_VERTICES] = { false };

            printf("Nhap dinh bat dau: ");
            scanf("%d", &startVertex);
            printf("DFS: ");
            dfs(&graph, startVertex, visited);
            printf("\n");
            break;
        }
        case 3: 
        {
            bool visited[MAX_VERTICES] = { false };
            printf("Nhap dinh bat dau: ");
            scanf("%d", &startVertex);
            printf("BFS: ");
            bfs(&graph, startVertex, visited);
            printf("\n");
            break;
        }
        case 4: 
        {
            printf("Nhap dinh nguon: ");
            scanf("%d", &source);
            printf("Nhap dinh dich: ");
            scanf("%d", &destination);
            DijkstraResult result = dijkstra(&graph, source);
            printf("Duong di ngan nhat tu %d den %d: ", source, destination);
            printShortestPath(result, destination);
            printf(" voi khoang cach la %d", result.distance[destination]);
            printf("\n");
            break;
        }
        case 5:
        {
            printf("Nhap dinh bat dau cho BFS: ");
            scanf("%d", &startVertex);
            if (!hasCycle(&graph, startVertex)) {
                printf("Khong tim thay chu trinh.\n");
            }
            break;
        }
        case 6:
        {
            DijkstraResult result;
            printf("Nhap dinh nguon: ");
            scanf("%d", &source);
            totalDistance(&graph, source, result);
            printf("Tong do dai duong di tu dinh %d den cac dinh khac:\n", source);
            for (int i = 0; i < graph.numVertices; i++)
            {
                printf("Dinh %d: %d, Duong di: ", i, result.distance[i]);
                printShortestPath(result,i);// In duong di ngan nhat tu nguon den mot dinh cu the
                printf("\n");
            }

            break;
        }
        case 7:
        {
            int connected = isConnected(&graph);

            if (connected)
            {
                printf("Do thi lien thong.\n");
            }
            else
            {
                printf("Do thi khong lien thong.\n");
            }
            break;
        }

        }

    } while (!0);

    return 0;
}