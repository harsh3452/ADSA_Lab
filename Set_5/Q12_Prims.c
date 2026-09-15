#include <stdio.h>

#define INF 9999

int n;
int graph[20][20];

void prim()
{
    int key[20], parent[20], used[20];
    int i, j, u, min;

    for (i = 0; i < n; i++)
    {
        key[i] = INF;
        used[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (i = 0; i < n - 1; i++)
    {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++)
        {
            if (!used[j] && key[j] < min)
            {
                min = key[j];
                u = j;
            }
        }

        used[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (graph[u][j] != 0 &&
                !used[j] &&
                graph[u][j] < key[j])
            {
                key[j] = graph[u][j];
                parent[j] = u;
            }
        }
    }

    printf("Minimum Spanning Tree:\n");

    for (i = 1; i < n; i++)
    {
        printf("%d - %d : %d\n",
               parent[i], i, graph[i][parent[i]]);
    }
}


int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }

    prim();

    return 0;
}