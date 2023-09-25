#include <stdio.h>
#include <stdlib.h>

int findSmallest(int arr[], int size)
{
	int smallest = 0; 
	for(int i=1;i<size;i++)
    {
		if(arr[smallest] > arr[i])
        {
			smallest = i;
		}
	}
	return smallest;
}

double findSum(int arr[], int size)
{
	int sum =0;
	for(int i=0;i<size;i++)
    {
		sum = sum + arr[i];
	}
	return sum;
}

int main()
{
    int n=5;
	printf("Enter number of patients: %d\n",n);
	//scanf("%d", &n);
	int sc[5];
	int sum=0;
	int brSc[5] ;
	int brArr[5] ;
	int comp[5];
	int start[5];
	for(int i=0;i<n;i++)
    {
		printf("Enter arrival time for patient %d: ", i+1);
		scanf("%d", &sc[i]);
		printf("Enter time taken for patient %d with oxygen: ", i+1);
		scanf("%d", &brSc[i]);
		sum = sum+brSc[i];
		brArr[i] = 1000;
	}
	int rn = sc[0];
	int rnj = 0;
	
	for(int i=0; i<sum ;i++)
    {
		for(int j=0 ; j<n; j++)
        {
			if (i==sc[j])
            {
				brArr[j] = brSc[j];
			}
		}
		if (rn==0)
        {
			comp[rnj] = i;
			rnj = findSmallest(brArr,n);
			printf("%d-P%d-",i,rnj+1);
			rn = brArr[rnj];
			start[rnj] =i;
			brArr[rnj] = 1000;
		}
		rn--;
	}
	comp[rnj] = sum+sc[0];
	printf("%d\n\n",sum+sc[0]);
	printf("Process\tWT\tTAT\tCT\n");
	for(int i=0;i<n;i++)
    {
		printf("%d\t%d\t%d\t%d\n",i+1,start[i]-sc[i],comp[i]-sc[i],comp[i]);
	}
    printf("The Average waiting time is %lf\n",(findSum(start,n)-findSum(sc,n))/n);
    printf("The Average Turn Around Time time is %lf\n",(findSum(comp,n)-findSum(sc,n))/n);
    printf("The Average completion time is %lf\n",findSum(comp,n)/n);
	return 0;
}
