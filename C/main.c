#include<stdio.h>
#include<stdio.h>
int main(){
    int r,c;
    printf("Enter the no. of rows\n");
    scanf("%d",&r);
    printf("Enter the no. of column\n");
     scanf("%d",&c);
     for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("* ");
        }
         printf("\n");
     }
     return 0;

}