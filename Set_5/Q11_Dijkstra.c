#include <stdio.h>

#define INF 9999

int n;
int graph[20][20];

void dijkstra(int src)
{
    int dist[20], visited[20];
    int i, j, u, min;

    for (i = 0; i < n; i++)
    {
        dist[i] = INF; // assign all distance as infinity at start as we don't know the distances
        visited[i] = 0; // assign 0 means none of the vertexes are visited/finalized. 
    }

    dist[src] = 0;

    for (i = 0; i < n - 1; i++)
    {
        min = INF;
        u = -1;
        //get the vertex with smallest distance which is not finalized
        for (j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }
        //no more reachable vertex to process so get out.
        if (u == -1)
            break;
        //finalize the vertex we selected
        visited[u] = 1; // greedy approach were we finalize the vertex when we visit it for the first time itself.

        
        for (j = 0; j < n; j++)
        {
            if (graph[u][j] != 0 && //check if edge exists and also check we have not finalize j.
                !visited[j] &&
                dist[u] + graph[u][j] < dist[j]) // check if we have a smaller distance from u to j 
            {
                dist[j] = dist[u] + graph[u][j]; //if we find smaller distance assign it
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", src);
    //print all the distances from source vertex
    for (i = 0; i < n; i++)
        printf("%d -> %d = %d\n",
               src, i, dist[i]);
}


int main()
{
    int i, j, src;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(src);

    return 0;
}
