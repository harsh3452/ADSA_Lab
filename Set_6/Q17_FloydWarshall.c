#include <stdio.h>

#define INF 9999

void floydWarshall(int graph[20][20], int n)
{
    int dist[20][20];
    int i, j, k;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(dist[i][k] != INF &&
                   dist[k][j] != INF &&
                   dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("\nShortest distance matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int graph[20][20];
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    printf("(Use 9999 for no direct edge)\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    floydWarshall(graph, n);

    return 0;
}