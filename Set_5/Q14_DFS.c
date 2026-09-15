#include <stdio.h>

int graph[20][20];
int n;
int visited[20];
int start[20], finish[20];
int time = 0;

void DFS(int u)
{
    int v;

    visited[u] = 1;
    start[u] = ++time;

    for (v = 0; v < n; v++)
    {
        if (graph[u][v] == 0)
            continue;

        if (!visited[v])
        {
            printf("%d -> %d : Tree Edge\n", u, v);
            DFS(v);
        }
        else if (finish[v] == 0)
        {
            printf("%d -> %d : Back Edge\n", u, v);
        }
        else if (start[u] < start[v])
        {
            printf("%d -> %d : Forward Edge\n", u, v);
        }
        else
        {
            printf("%d -> %d : Cross Edge\n", u, v);
        }
    }

    finish[u] = ++time;
}

void startDFS()
{
    int i;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        start[i] = 0;
        finish[i] = 0;
    }

    time = 0;

    for (i = 0; i < n; i++)
    {
        if (!visited[i])
            DFS(i);
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

    printf("\nDFS Edge Classification:\n");

    startDFS();

    return 0;
}