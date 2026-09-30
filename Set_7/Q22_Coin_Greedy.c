#include <stdio.h>

void coinChange(int coins[], int n, int amount)
{
    int i, count;

    printf("Coins used:\n");

    for(i = n - 1; i >= 0; i--)
    {
        count = amount / coins[i];

        while(count > 0)
        {
            printf("%d ", coins[i]);
            amount -= coins[i];
            count--;
        }
    }

    printf("\n");
}

int main()
{
    int coins[20];
    int n, amount, i;

    printf("Enter number of denominations: ");
    scanf("%d", &n);

    printf("Enter denominations in increasing order:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter amount: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}