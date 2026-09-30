#include <stdio.h>

int graph[20][20];
int color[20];
int n, m;

int isSafe(int vertex, int c)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(graph[vertex][i] && color[i] == c)
            return 0;
    }

    return 1;
}

int graphColoring(int vertex)
{
    int c;

    if(vertex == n)
        return 1;

    for(c = 1; c <= m; c++)
    {
        if(isSafe(vertex, c))
        {
            color[vertex] = c;

            if(graphColoring(vertex + 1))
                return 1;

            color[vertex] = 0;
        }
    }

    return 0;
}

void printColors()
{
    int i;

    for(i = 0; i < n; i++)
        printf("Vertex %d -> Color %d\n",
               i, color[i]);
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter number of colors: ");
    scanf("%d", &m);

    if(graphColoring(0))
    {
        printf("\nColoring:\n");
        printColors();
    }
    else
    {
        printf("Coloring not possible\n");
    }

    return 0;
}