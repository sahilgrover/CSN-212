#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz 100000
#define ul 1000000
#define pr 1000000000000000
int main()
{
	srand(time(NULL));
	freopen("input.txt","w",stdout);
	int V[] = {5,10,20,50,100,200};
	int E[] = {11,23,37,89,173,403};
	cout<<6<<'\n';
	for (int i=0;i<6;i++)
	{
		cout<<V[i]<<" "<<E[i]<<'\n';
		cout<<0<<'\n'; //src = 0
		for(int j=0;j<E[i];j++)
		{
			int u = rand()%V[i];
			int v = ((u + rand() + rand())%V[i] + V[i])%V[i];
			int w = rand()%30 - 10;
			cout<<u<<" "<<v<<" "<<w<<'\n';
		} 
	}
	
}