#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "C:\Users\ghmgj\OneDrive\שולחן העבודה\project\code\correcting_codes\functions.h"

//int* vec_product(int a[], int b[],int n,int m);

int main ()
{
	int m; // n = x * m + y
	int n; //code length
	int q; //modulo q
	int b; // error burst
	int cyclic; //cyclic/not cyclic code
	int* s_n; //here we store the code
	int k_plus,k_minus; //error magnitude
//----------------------------------------------------------------------------------
//                            get inputs
//----------------------------------------------------------------------------------
	printf("Enter n: ");
    scanf("%d", &n);
	printf("Enter b: ");
    scanf("%d", &b);
	printf("Enter k+: ");
    scanf("%d", &k_plus);
	printf("Enter k-: ");
    scanf("%d", &k_minus);
	printf("cyclic?: ");
    scanf("%d", &cyclic);

//----------------------------------------------------------------------------------
//                           2 burst error (1,0) magnitude no cyclic
//----------------------------------------------------------------------------------

	if (b==2 && k_plus == 1 && k_minus == 0 && cyclic == 0){
		s_n = two_burst_1_0_mag_uncyclic(n);

		}
//----------------------------------------------------------------------------------
//                           2 burst error (1,0) magnitude cyclic
//----------------------------------------------------------------------------------
	else if (b==2 && k_plus == 1 && k_minus == 0 && cyclic== 1 && ((n%6) == 1 || (n%6) == 4)) {//start case 2
		s_n = two_burst_1_0_mag_cyclic(n);

	}

	else if (b%2 ==0 && b!=2 && k_plus == 1 && k_minus == 0 && cyclic == 0){
        	int n_temp = n;
            int b_temp = b;
            int counter = 0;
            int i;
            while (b_temp != 2){
                b_temp = b_temp / 2;
                counter++;
            }
            int j = pow(2,counter);
            int div = n/j;
            for (i = 0 ; i< j ; i++){
                if (i%2 == 0){
                    s_n = two_burst_1_0_mag_uncyclic(div+1);
                }
                else {
                    s_n = two_burst_1_0_mag_uncyclic(div);
                }
		}
		}

	return 0;
}


int* s_n1;
int* vec_product(int a[], int b[],int n,int m){ // operator between 2 vectors as in the article
	int* c = malloc(n * m * sizeof(int));
	int i,j;
	for (j=0;j<m;j++){
		for (i=0;i<n;i++){
			c[j*n + i]=a[i]+b[j];
		}
	}
	return c;
}

int* mergeArrays(int arr1[], int size1, int arr2[], int size2, int arr3[], int size3) {
    int index = 0;
    int *mergedArray = malloc((size1+size2+size3) * sizeof(int));

    // Copy arr1 elements to mergedArray
    for (int i = 0; i < size1; i++) {
        mergedArray[index++] = arr1[i];
    }

    // Copy arr2 elements to mergedArray
    for (int i = 0; i < size2; i++) {
        mergedArray[index++] = arr2[i];
    }

    // Copy arr3 elements to mergedArray
    for (int i = 0; i < size3; i++) {
        mergedArray[index++] = arr3[i];
    }

    return mergedArray;
}

void new_size(int n,int even_odd[2]){
    int even_size;
    int odd_size;
	if (n%2 == 0){
		even_size = n/2;
		odd_size = n/2;
	}
	else{
		even_size = ((n-1)/2)+1;
		odd_size = ((n-1)/2);
	}
	even_odd[0] = even_size;
	even_odd[1] = odd_size;
	}


void two_n_1_0_mag_uncyclic(int n, int b){
	int n_temp = n;
	int b_temp = b;
	int counter = 0;
	int vec_sizes[20];
	int i;
	while (b_temp != 2){
        b_temp = b_temp / 2;
        counter++;
	}
        int j = pow(2,counter);
        int div = n/j;
        for (i = 0 ; i<= j ; i++){
            if (i%2 == 0){
                s_n1 = two_burst_1_0_mag_uncyclic(div);
            }
            else {
                s_n1 = two_burst_1_0_mag_uncyclic(div);
            }
           // print_s(s_n1,div);
            //printf("\n");
        }
	}


void print_s(int s_n[],int n){
	int k;
    for (k=0; k<n; k++){
		printf("%d ", s_n[k]);
	}
	printf("\n");
}



int* two_burst_1_0_mag_uncyclic(int n){
    int* s_n = malloc(n * sizeof(int));
    int q;
    int m;
//----------------------------------------------------------------------------------
//                            case 1+2 => n = 2m+1
//----------------------------------------------------------------------------------
	if (n%2 != 0){//n is odd
		m = (n-1)/2;
        q = 4*m + 2;
		if (m%2 == 0){//m is even
			s_n = two_burst_case1(n,m);
		}
		else{// m is odd
			s_n = two_burst_case2(n,m);
		}
		}
//----------------------------------------------------------------------------------
//                            case 3+4 => n = 2m
//----------------------------------------------------------------------------------
	else{//n is even
        m = n/2;
		q = 4*m;
		if (m%2 == 0){//m is even
			s_n = two_burst_case3(n,m);
		}
		else{//m is odd
			s_n = two_burst_case4(n,m);
		}
	}
	print_s(s_n,n);
	printf("\n");
	printf("q = %d\n", q);
	printf("\n");
	return s_n;
}

int* two_burst_1_0_mag_cyclic(int n){
	int* s_n = malloc(n * sizeof(int));
	int q;
	if ((n-1)%6==0){
		int m = (n-1)/6;
		q = 4*m + 2;
		s_n = two_burst_cyclic_case1(n,m);
	}
	else if (((n-4)%6) == 0){
		int m = (n-4)/6;
		q = 4*m;
		s_n = two_burst_cyclic_case2(n,m);
	}
	print_s(s_n,n);
	printf("\n");
	printf("q = %d\n", q);
	printf("\n");
	return s_n;
}

int* two_burst_case1(int n, int m){
		int a[]= {m+1,3*m+3};
		int c[m+1];
		int j;
		int q = 4*m + 2;
		for (j=0; j<=m; j++){
			c[j] = j*2;
		}
		int* s =vec_product(a,c,2,m+1);
		int i;
		int* s_n = malloc(n * sizeof(int));
		for (i=0; i<n; i++){
			s_n[i] = (s[i])%(q);
		}
        return s_n;
}

int* two_burst_case2(int n, int m){
	int a[]= {3*m+2,m+2};
	int c[m+1];
	int j;
	int q = 4*m + 2;
	for (j=0; j<=m; j++){
		c[j] = j*2;
	}
	int* s =vec_product(a,c,2,m+1);
	int* s_n = malloc(n * sizeof(int));
	int i;
	for (i=0; i<n; i++){
		s_n[i] = (s[i])%(q);
	}
	return s_n;
}

int* two_burst_case3(int n, int m){
	int a[]= {m+1,3*m+1};
	int c[m];
	int j;
	int q = 4*m;
	for (j=0; j<m; j++){
		c[j] = j*2;
	}
	int* s =vec_product(a,c,2,m);
	int* s_n = malloc(n * sizeof(int));
	int i;
	for (i=0; i<n; i++){
		s_n[i] = (s[i])%(q);
	}
	return s_n;
}

int* two_burst_case4(int n, int m){
	int* s1 = malloc((m-1) * sizeof(int));
	int* s2 = malloc((int)floor(m/2) * sizeof(int));
	int* s3 = malloc((int)floor(m/2) * sizeof(int));

	int i;
	int j = 0;

	for (i=0 ; i<m-1 ; i++){
		s1[i] = 2*i +1;
	}

	for (i=0 ; i<m ; i++){
		if (i%2 == 0){
			s2[j] = 2*m +1 + 2*i;
			j = j + 1;
		}
	}

	j = 0;

	for (i=0 ; i<m ; i++){
		if (i%2 == 0){
			s3[j] = 4*m -3 - 2*i;
			j = j+1;
		}
	}

	int* s_n = mergeArrays(s1,m-1,s2,(int)floor(m/2),s3,(int)floor(m/2));

	free(s1);
	free(s2);
	free(s3);

	return s_n;
}

int* two_burst_cyclic_case1(int n,int m){
    int q = 12*m+3;
    int a = 3*m + 1;
    int b = 3*m + 2;
    int c = 6*m + 2;
    int d = 6*m + 4;
    int e = 2;
    int f = 9*m + 5;
    int g[]= {a,b,c,d,e,f};
    int h[m+1];
    int i;
    for (i=0 ; i<m+1 ; i++){
        h[i] = 3*i;
    }
    int* s =vec_product(g,h,6,m+1);
    int* s_n = malloc(n * sizeof(int));
    for (i=0; i<n; i++){
        s_n[i] = (s[i])%(q);
    }
    return s_n;
}

int* two_burst_cyclic_case2(int n,int m){
	int q = 12*m+9;
	int a = 1;
	int b = 9*m + 10;
	int c = 3*m + 2;
	int d = 3*m + 7;
	int e = 6*m + 7;
	int f = 6*m + 8;
	int g[]= {a,b,c,d,e,f};
	int h[m];
	int i;
	for (i=0 ; i<m ; i++){
		h[i] = 3*i;
	}
	int* s =vec_product(g,h,6,m+1);
	int* s_n = malloc(n * sizeof(int));
	for (i=0; i<n; i++){
		s_n[i] = (s[i])%(q);
	}
	return s_n;
}












