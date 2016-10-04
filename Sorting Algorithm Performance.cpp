#include<iostream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
using namespace std;

void rand (int r, int *arr, int DIM) { srand(1891115+r); for(int i=0; i<DIM; i++) arr[i] = rand()%100; }
void reload (int *arr, int **v, int DIM) { for(int i=0; i<DIM; i++) v[i] = &arr[i]; }
void print (int *arr, int **v, int DIM);
void insertionSort (int **v, int DIM);
void bubbleSort (int **v, int DIM);
void selectionSort (int **v, int DIM);
void merge(int **v, int p, int m, int u);
void mergeSort(int **v, int p, int u);
void mergeS(int **v, int DIM) { mergeSort(v,0,DIM-1); }
int partition(int **v, int p, int u);
void quickSort(int **v, int p, int u);
void quickS(int **v, int DIM) { quickSort(v,0,DIM-1); }

int main() {
	const int DIM = 40000, TEST=5, N_ALGORITHM = 5;
	clock_t init, end;
	double time;
	int A[DIM], *b[DIM];

	void (*f[N_ALGORITHM]) (int **, int) = { quickS, mergeS, insertionSort, selectionSort, bubbleSort };
		
		for(int t=0; t<TEST; ) {
			rand(++t,A,DIM);
			cout << "\n > TEST " << t << " su " << TEST << "\n";
	
			for (int i=0; i<N_ALGORITHM; i++) {
				cout << right << setw(20) << ((i==0)?"QuickSort: ":(i==1)?"MergeSort: ":(i==2)?"InsertionSort: ":(i==3)?"SelectionSort: ":"BubbleSort: ");
				reload(A,b,DIM);		
				init = clock();
				f[i](b,DIM);
				end = clock();
				time = (end-init)*1000.0 / (double)CLOCKS_PER_SEC;
				cout << setw(10) << fixed << setprecision(2) << time << "ms" << endl;
				
				//cout << "\n\n"; print(A,b,DIM); cout << "\n\n";
			}
	}
}

//################################### FUNZIONI ###################################

void insertionSort (int **v, int DIM) {
	for(int i=1; i<DIM; i++) {
		int *key_address = v[i];
		int position = i;
		while( position>0 && *v[position-1] > *key_address ) {
			v[position] = v[position-1];
			position--;
		}
		v[position] = key_address;
	}
}

void bubbleSort (int **v, int DIM) {
	for(int pass=1; pass<DIM; pass++) {
		for(int i=0; i<DIM-pass; i++) {
			if(*v[i] > *v[i+1]) {
				int *tmp = v[i];
				v[i] = v[i+1];
				v[i+1] = tmp;
			}
		}
	}
}

void selectionSort (int **v, int DIM) {
	for(int index=0; index<DIM-1; index++) {
		int min = index;
		
		for(int i=index+1; i<DIM; i++)
			if( *v[i] < *v[min] ) min=i;
		
		int *tmp = v[min];
		v[min] = v[index];
		v[index] = tmp;
	}
}

void merge(int **v, int p, int m, int u) {
	int sx=p, dx=m+1;
	int *s[u-p+1];
	int i=0;
	 
		while(sx<=m && dx<=u) s[i++] = (*v[sx]<*v[dx]?v[sx++]:v[dx++]);

		while(sx<=m) s[i++] = v[sx++];
		while(dx<=u) s[i++] = v[dx++];
		
		for(i=0; i<u-p+1; i++) v[p+i] = s[i]; 
}

void mergeSort(int **v, int p, int u) {
	if(p==u) return;
	int m = (p+u)/2;
	mergeSort(v,p,m);
	mergeSort(v,m+1,u);
	merge(v,p,m,u);
}

void quickSort(int **v, int top, int bottom) {
	if (top < bottom) {
		int middle = partition(v, top, bottom);
		quickSort(v, top, middle);
		quickSort(v, middle+1, bottom);
    }
}

int partition(int **v, int top, int bottom) {
	int *x = v[top];
	int i = top - 1;
	int j = bottom + 1;
  
	  do {
    	do j--; while (*x < *v[j]);
			do i++; while (*x > *v[i]);

        if (i < j) {
					int *tmp = v[i];
					v[i] = v[j];
					v[j] = tmp;
				}
						
		}	 while (i < j);    
    
		return j;        
}

void print (int *arr, int **v, int DIM) {
	cout << "int  A[]: ";
	for(int i=0; i<DIM; i++) cout << arr[i] << " "; // *(arr+i) in modo analogo

	cout << "   int *b[]: ";
	for(int i=0; i<DIM; i++) cout << *v[i] << " "; // **(v+i) in modo analogo
	
	cout << endl;
}
