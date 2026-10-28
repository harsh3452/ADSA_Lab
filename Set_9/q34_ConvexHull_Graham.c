#include <stdio.h>
#include <stdlib.h>

struct Point
{
    int x;
    int y;
};

struct Point p0;

int orientation(struct Point a, struct Point b, struct Point c)
{
    int value = (b.y - a.y) * (c.x - b.x)
              - (b.x - a.x) * (c.y - b.y);

    if(value == 0)
        return 0;

    if(value > 0)
        return 1;

    return 2;
}

int distance(struct Point a, struct Point b)
{
    return (a.x - b.x) * (a.x - b.x)
         + (a.y - b.y) * (a.y - b.y);
}

void sortPoints(struct Point points[], int n)
{
    int i, j;
    struct Point temp;

    for(i = 1; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            int o = orientation(p0, points[i], points[j]);

            if(o == 1 ||
               (o == 0 &&
                distance(p0, points[i]) >
                distance(p0, points[j])))
            {
                temp = points[i];
                points[i] = points[j];
                points[j] = temp;
            }
        }
    }
}

void convexHull(struct Point points[], int n)
{
    int i, top;
    struct Point stack[100];

    if(n < 3)
    {
        printf("Convex hull requires at least 3 points\n");
        return;
    }

    int lowest = 0;

    for(i = 1; i < n; i++)
    {
        if(points[i].y < points[lowest].y ||
          (points[i].y == points[lowest].y &&
           points[i].x < points[lowest].x))
            lowest = i;
    }

    struct Point temp = points[0];
    points[0] = points[lowest];
    points[lowest] = temp;

    p0 = points[0];

    sortPoints(points, n);

    stack[0] = points[0];
    stack[1] = points[1];
    stack[2] = points[2];
    top = 2;

    for(i = 3; i < n; i++)
    {
        while(top >= 1 &&
              orientation(stack[top - 1],
                           stack[top],
                           points[i]) != 2)
        {
            top--;
        }

        stack[++top] = points[i];
    }

    printf("\nPoints on the Convex Hull:\n");

    for(i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main()
{
    struct Point points[100];
    int n, i;

    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter coordinates:\n");

    for(i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    convexHull(points, n);

    return 0;
}