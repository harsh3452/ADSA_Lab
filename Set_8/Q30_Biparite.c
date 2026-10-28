#include <stdio.h>

int graph[20][20];
int color[20];
int n, e;

int isBipartite()
{
    int queue[20];
    int front, rear;
    int i, v;

    for(i = 0; i < n; i++)
        color[i] = -1;

    for(i = 0; i < n; i++)
    {
        if(color[i] != -1)
            continue;

        front = 0;
        rear = 0;

        queue[rear++] = i;
        color[i] = 0;

        while(front < rear)
        {
            v = queue[front++];

            for(int j = 0; j < n; j++)
            {
                if(graph[v][j])
                {
                    if(color[j] == -1)
                    {
                        color[j] = 1 - color[v];
                        queue[rear++] = j;
                    }
                    else if(color[j] == color[v])
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

void printSets()
{
    int i;

    printf("Set 1: ");

    for(i = 0; i < n; i++)
        if(color[i] == 0)
            printf("%d ", i);

    printf("\nSet 2: ");

    for(i = 0; i < n; i++)
        if(color[i] == 1)
            printf("%d ", i);

    printf("\n");
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

    if(isBipartite())
    {
        printf("Graph is bipartite\n");
        printSets();
    }
    else
    {
        printf("Graph is not bipartite\n");
    }

    return 0;
}