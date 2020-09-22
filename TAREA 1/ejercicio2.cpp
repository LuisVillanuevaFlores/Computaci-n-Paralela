#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define MAX 800

int main(){

	int f,c,z;
	int A[MAX][MAX];
	int B[MAX][MAX];
	int C[MAX][MAX];

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			A[i][j]=rand()%1000;
			B[i][j]=rand()%1000;
		}
		
	}

	clock_t t;
  	t=clock();
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			C[i][j]=0;
		
			for(int k=0;k<MAX;k++){
				C[i][j]=C[i][j]+A[i][k]*B[k][j];
			}
		}	
	}

	t=clock()-t;
	cout<<(float)t/CLOCKS_PER_SEC<<endl;

	/*
	for(int i=0;i<MAX-500;i++){
		for(int j=0;j<MAX-500;j++){
			cout<<C[i][j]<<" ";
		}
		cout<<endl;
	}
	*/


}