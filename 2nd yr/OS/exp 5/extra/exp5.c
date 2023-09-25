#include <stdio.h>

void SJF(int pat[],int at[], int cpy[],int bt[],int btcpy[])
{
    int min=0;
    for(int i=0;i<5;i++)
    {
        int j;
        for(j=0;j<5;j++)
        {
            if(bt[j]<bt[min])
            {
                min=j;  
            }
        }
    }
}

void main()
{
    int pat[5],at[5],bt[5];
    int patcpy[5],atcpy[5],btcpy[5];
    printf("Number of patients: 5");
    for(int i=0;i<5;i++)
    {
        printf("Enter arrival time of P%d: ",i+1);
        scanf("%d",&at[i]);
        printf("Enter burst time of P%d: ",i+1);
        scanf("%d",&bt[i]);
    }
}