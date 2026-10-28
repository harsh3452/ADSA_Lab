#include <stdio.h>

int graph[20][20];
int path[20];
int visited[20];
int n, e;

int isSafe(int vertex, int pos)
{
    if(!graph[path[pos - 1]][vertex])
        return 0;

    if(visited[vertex])
        return 0;

    return 1;
}

int hamiltonian(int pos)
{
    int v;

    if(pos == n)
    {
        if(graph[path[pos - 1]][path[0]])
            return 1;

        return 0;
    }

    for(v = 1; v < n; v++)
    {
        if(isSafe(v, pos))
        {
            path[pos] = v;
            visited[v] = 1;

            if(hamiltonian(pos + 1))
                return 1;

            visited[v] = 0;
        }
    }

    return 0;
}

void findHamiltonianCycle()
{
    int i;

    path[0] = 0;
    visited[0] = 1;

    if(hamiltonian(1))
    {
        printf("Hamiltonian Cycle exists:\n");

        for(i = 0; i < n; i++)
            printf("%d -> ", path[i]);

        printf("%d\n", path[0]);
    }
    else
    {
        printf("Hamiltonian Cycle does not exist\n");
    }
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter adjacency matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }

    findHamiltonianCycle();

    return 0;
}