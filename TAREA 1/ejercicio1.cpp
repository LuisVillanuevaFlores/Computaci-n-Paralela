#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
using namespace std;
#define MAX 500

int main(){

	clock_t t;
	double A[MAX][MAX],x[MAX],y[MAX];

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			A[i][j]=rand()%MAX;
		}
		x[i]=rand()%MAX;
		y[i]=0;
	}

  	t=clock();

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			y[i]+=A[i][j]*x[j];
		}
	}

	t=clock()-t;
	cout<<(float)t/(double)CLOCKS_PER_SEC<<endl;
 	cout<<"---------------------------"<<endl;


///////////////////////////////////////////////

	for(int i=0;i<MAX;i++){
		y[i]=0;
	}

	t=clock();

	for(int j=0;j<MAX;j++){
		for(int i=0;i<MAX;i++){
			y[i]+=A[i][j]*x[j];
		}
	}

	t=clock()-t;
	cout<<(float)t/(double)CLOCKS_PER_SEC<<endl;
 	cout<<"---------------------------"<<endl;
}
