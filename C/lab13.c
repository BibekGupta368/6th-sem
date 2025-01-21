#include <stdio.h>
int main()
{
    int n,pr;
    int arr[100], so = 0, se = 0;
    printf("Enter the number of Elements\n");
    scanf("%d", &n);
    printf("Enter the elements\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            so = so + arr[i];
        }
        else
        {
            se = se + arr[i];
        }
    }
    printf("The sum of odd elements is %d\n", so);
    printf("The sum of odd elements is %d\n", se);

    for (int i = 0; i < n; i++)
    {
        int j = i, flag = 0;
        while (j>0)
        {
            if(arr[i] % j == 0)
            {
              flag = 1;
            }
            j=j-1;
        }
        if(flag==2){
             pr=pr+arr[i];
        }

    }
    printf("The sum of prime no. is %d\n",pr);

    return 0;
}