#include<stdio.h>
#include<stdio.h>
int main(){
    int c;
    printf("Enter the no. of choice\n");
    scanf("%d",&c);

     for(int i=0;i<c;i++){
        for(int j=c;j>i;j--){
            printf("  ");
        }
         for(int j=0;j<(2*i-1);j++){
            printf("* ");
            }
            printf("\n");
     }
     return 0;

}