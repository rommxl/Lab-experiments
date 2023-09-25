#include <stdio.h>
#include <stdlib.h>

int Min(int arr[],int n)
{

    int min=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]<arr[min])
        {
            min=i;
        }
    }
    return min;
}
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int arr[], int n)
{
    int i, j, min;
    for (i = 0; i < n - 1; i++) 
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        swap(&arr[min], &arr[i]);
    }
}

void main()
{
    int arrival[5];
    //int req[5];
    int sum=0;
    int brSc[5];
    int brArr[5];
    int comp[5];
    int start[5];
    printf("Enter number of patients: 5\n");
    for(int i=0;i<5;i++)
    {
        printf("Enter arrival time for patient %d: ",i+1);
        scanf("%d",&arrival[i]);
    }
    for(int i=0;i<5;i++)
    {
        printf("Enter required time for patient %d: ",i+1);
        scanf("%d",&brSc[i]);
        sum+=brSc[i];
        brArr[i]=10000;
    }
    printf("\n");
    int rn=arrival[0];
    int rnj=0;
    sort(arrival,5);
    for(int i=0;i<sum;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(i==arrival[j])
            {
                brArr[j]=brSc[j];
            }
        }
        if(rn==0)
        {
            comp[rnj]=i;
            rnj=Min(brArr,5);
            printf("%d-P%d-",i,rnj+1);
            rn=brArr[rnj];
            start[rnj]=i;
            brArr[rnj]=1000;
        }
        rn--;
    }
    comp[rnj]=sum+arrival[0];
    float avgWait=0;
    float avgTat=0;
    float avgct=0;
    for(int a=0;a<5;a++)
    {
        avgWait=avgWait+(start[a]-arrival[a]);
    }
    for(int a=0;a<5;a++)
    {
        avgTat=avgTat+(comp[a]-arrival[a]);
    }
    for(int a=0;a<5;a++)
    {
        avgct=avgct+comp[a];
    }
    avgWait=avgWait/5;
    avgTat=avgTat/5;
    avgct=avgct/5;
    printf("%d\n\n",sum+arrival[0]);
    printf("Process\tWT\tTAT\tCT\n");
    for(int i=0;i<5;i++)
    {
        printf("%d\t%d\t%d\t%d\n",i+1,start[i]-arrival[i],comp[i]-arrival[i],comp[i]);
    }
    printf("Average Completion time: %f\n",avgct);
    printf("Average TAT: %f\n",avgTat);
    printf("Average wait time: %f\n",avgWait);
}