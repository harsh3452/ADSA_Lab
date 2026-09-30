#include <stdio.h>

#define INF 9999

struct Edge
{
    int u, v, weight;
};

void bellmanFord(struct Edge edges[], int n, int e, int src)
{
    int dist[20];
    int i, j;

    for(i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    /* Relax all edges V-1 times */
    for(i = 1; i <= n - 1; i++) 
    {
        for(j = 0; j < e; j++) // pick all edges and iterate and find if new minimum is
        {
            if(dist[edges[j].u] != INF &&
               dist[edges[j].u] + edges[j].weight < dist[edges[j].v])
            {
                dist[edges[j].v] =
                    dist[edges[j].u] + edges[j].weight;
            }
        }
    }

    /* Check for negative weight cycle */
    for(j = 0; j < e; j++)
    {
        if(dist[edges[j].u] != INF &&
           dist[edges[j].u] + edges[j].weight < dist[edges[j].v])
        {
            printf("Negative weight cycle exists\n");
            return;
        }
    }

    printf("\nShortest distances from vertex %d:\n", src);

    for(i = 0; i < n; i++)
        printf("%d -> %d = %d\n", src, i, dist[i]);
}

int main()
{
    int n, e, src, i;
    struct Edge edges[50];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight):\n");

    for(i = 0; i < e; i++)
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].weight);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    bellmanFord(edges, n, e, src);

    return 0;
}