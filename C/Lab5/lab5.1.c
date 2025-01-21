#include <stdio.h>
#include <stdlib.h>
int sodd(int *arr, int n)
{
    int so = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            so = so + arr[i];
        }
    }
    return so;
}
int seven(int *arr, int n)
{
    int se = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            se = se + arr[i];
        }
    }
    return se;
}
int is_prime(int num) {
    if (num <= 1) return 0;  
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;  
}

int prime(int *arr, int n) {
    int pr = 0;  
    for (int i = 0; i < n; i++) {
        if (is_prime(arr[i])) {
            pr = pr + arr[i];  
        }
    }
    return pr;  
}


int main()
{
    int n, arr[100];
    printf("Enter the size of array\n");
    scanf("%d", &n);
    printf("Enter the elements\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int so = sodd(arr, n);
    printf("The sum of odd elements is %d\n", so);
    int se = seven(arr, n);
    printf("The sum of even elements is %d\n", se);
    int pr = prime(arr, n);
    printf("The sum of prime no. is %d\n", pr);

    return 0;
}