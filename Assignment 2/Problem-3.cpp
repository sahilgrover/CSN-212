#include <bits/stdc++.h>
using namespace std;

#define UL 10000

int A[UL+5],B[2*UL+5],dp[UL+5];
int binary_search(int x[],int r,int num)
{
	int l=0;
	while(r-l>1)
	{
		int mid=(l+r)/2;
		if(x[mid]>num) r=mid;
		else l=mid;
	}
	return r;
}
 
int LIS(int arr[],int start,int n)
{
	for(int j=0;j<n;j++) dp[j]=0;
	dp[0]=arr[start];
	int len=1;
	for(int j=start+1;j<n+start;j++)
	{
		if(arr[j] < dp[0])  dp[0] = arr[j];
		
		else if (arr[j] > dp[len-1])  dp[len++]=arr[j];
		
		else dp[binary_search(dp,len-1,arr[j])]=arr[j];
	}
	return len;
}
 
 
int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
		int n; scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&A[i]);
			B[i]=A[i]; B[n+i]=A[i];
    	}
	    int ans=0,res;
		for(int i=0;i<n;i++)
		{	
	    	res = LIS (B,i,n);
		    ans = max(ans,res);
	   	}
		printf("%d\n",ans);
	}
	return 0;
}