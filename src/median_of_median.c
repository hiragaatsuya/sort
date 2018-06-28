#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int i, j, h, z, pivot;
  
// 中央の要素をピボットとする
  pivot = A[0];
  for(i = j = h = 1; i < n; i++){
    if(A[i] < pivot && h!=i){
      z = A[j];  A[j] = A[h];  A[h] = z;
      z = A[i];  A[i] = A[j];  A[j] = z;
      j++; h++;
    }
    else if(A[i]<pivot ){
        z=A[i];  A[i]=A[j];  A[j]=z;
        j++; h++;
    }
    else if(A[i]==pivot){
        z = A[h];
        A[h] = A[i];
        A[i] = z;
        h++;
    }
  }
  z=A[0];  A[0]=A[j-1];  A[j-1]=z;  j=j-1;
  if(h < k+1) return quick_select(A+h, n-h, k-h);
  else if(j < k+1) return pivot;
  else return quick_select(A, j, k);
}

int quick_Sep(int A[], int n, int pivot){
  int i, j, h, z;
  for(i = j = h = 0; i < n; i++){
    if(A[i] < pivot && h !=i){
      z = A[j];  A[j] = A[h];  A[h] = z;
      z = A[i];  A[i] = A[j];  A[j] = z;
      j++; h++;
    }
    else if(A[i]<pivot ){
        z=A[i];  A[i]=A[j];  A[j]=z;
        j++; h++;
    }
    else if(A[i]==pivot){
        z = A[h];  A[h] = A[i];  A[i] = z;  h++;
    }
  }
  return h;
}


int meOfme(int A[],int n,int k){
    if(n<=5) return quick_select(A,n,k);
    else {
        int i,r,z,pivot;
        for(i=0;5*i+4<n;i++){
            z=meOfme(A+5*i,5,2);  A[5*i+2]=A[i];  A[i]=z;
        }
        if(n-5*i>=1){
            z=meOfme(A+5*i,n-5*i,(n-5*i)/2);  A[5*i+(n-5*i)/2]=A[i];  A[i]=z;  i++;
        } 
        pivot=meOfme(A,i,i/2);
        r=quick_Sep(A,n,pivot)-1;
        if(r==k) return pivot;
        else if(r<k) return meOfme(A+r+1,n-r-1,k-r-1);
        else return meOfme(A,r,k);
    }
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(meOfme(A, N, i) != i) printf("ERROR %d %d\n", i,meOfme(A, N, i));
//    printf("%d th element is %d\n", i, meOfme(A, N, i));
  }
}
