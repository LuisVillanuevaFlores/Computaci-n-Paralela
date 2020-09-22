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
			A[i][j]=rand()%60;
			B[i][j]=rand()%60;
			C[i][j] = 0;
		}
		
	}

    clock_t t;
  	t=clock();
	int block_size=200;

	for (int k = 0; k < MAX; k += block_size)
		for (int j = 0; j < MAX; j += block_size)
			for (int i = 0; i < MAX; ++i)
				for (int jj = j; jj < min(j + block_size, MAX); ++jj)
					for (int kk = k; kk < min(k + block_size, MAX); ++kk)
						C[i][jj] += A[i][kk] * B[kk][jj];

    t=clock()-t;
	//cout<<"Tiempo de multipliación: "<<(float)t/CLOCKS_PER_SEC<<endl;

    /*
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;        
    }
    */
    return 0;

}