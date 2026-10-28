#include <stdio.h>

int graph[20][20];
int selected[20];
int n, e, m;

int isClique(int count)
{
    int i, j;

    for(i = 0; i < count; i++)
    {
        for(j = i + 1; j < count; j++)
        {
            if(!graph[selected[i]][selected[j]])
                return 0;
        }
    }

    return 1;
}

int findClique(int vertex, int count)
{
    if(count == m)
        return 1;

    if(vertex == n)
        return 0;

    selected[count] = vertex;

    if(findClique(vertex + 1, count + 1))
        return 1;

    if(findClique(vertex + 1, count))
        return 1;

    return 0;
}

void clique()
{
    if(findClique(0, 0))
    {
        int i;

        printf("Clique of size %d exists:\n", m);

        for(i = 0; i < m; i++)
            printf("%d ", selected[i]);

        printf("\n");
    }
    else
    {
        printf("Clique of size %d does not exist\n", m);
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

    printf("Enter clique size: ");
    scanf("%d", &m);

    clique();

    return 0;
}