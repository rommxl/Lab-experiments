#include <stdio.h>
#include <stdlib.h>

void sort(int at[], int bt[], int atcpy[], int btcpy[], int patient[])
{
    int min=0;
    int temp[5];
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(bt[j]<bt[min] && bt[j]!=-1)
            {
                min=j;
                btcpy[i]=bt[min];
                atcpy[i]=at[min];
                patient[i]=min+1;
            }
        }
        bt[min]=-1;
    }
}

void printArr(int arr[])
{
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }
}
void main()
{
    //int n=5;
    printf("Enter number of patients: 5\n");               //number of processes
    //scanf("%d",&n);
    int at[5];
    int atcpy[5];
    int bt[5];
    int btcpy[5];
    int patient[5];
    int curtime=0;
    int min=0;
    for(int i=0;i<5;i++)
    {
        printf("Enter at time of patient %d: ",i+1);
        scanf("%d",&at[i]);
    }
    for(int i=0;i<5;i++)
    {
        printf("Enter enter required time for patient %d: ",i+1);
        scanf("%d",&bt[i]);
    }
    //printf("Test");
    //sorting all according to AT
    //sort(at,bt,atcpy,btcpy,patient);
    printArr(bt);
}