#include<stdio.h>
#include<stdlib.h>

// This is the very basic factorial function, with reursion method
// for the LC-3 version, please see recursion.asm
int factorial(int n) {  // we assume that n is non-negative
    if(n == 0) {
        return 1;
    }
    return n * factorial(n-1);
}

// Another 2 basic function of recursion: 
//      Fibonacci Series and Combinatorial Number
// Though it is very inefficient, we can still use it, to see the recursion
int fibonacci(int n) {
    if(n == 0 || n == 1) {
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}


int choose(int n, int k) {
    if(n == k || k == 0) {
        return 1;
    }
    return choose(n-1, k) + choose(n-1, k-1);
}


// This function is used to print a decimal with the form of char
// Assume that n is positive
void outDecimal(int n) {
    int q = n % 10;
    if(n / 10 > 0) {
        outDecimal(n / 10);
    }
    printf("%d", q);

}

// This is a little bit more advanced topic: binary searching based on recursion.
// Given an array = {....} with ascending elements, and left, right bound, and x
// if the index of x is within l and r, return its index, else return -1
int binarysearch(int array[], int left, int right, int x) {
    if(left > right) {
        return -1;
    }

    int mid = (left + right) / 2;

    if(x > array[mid]) {
        return binarysearch(array, mid + 1, right, x);
    }
    else if(x < array[mid]) {
        return binarysearch(array, left, mid-1, x);
    }
    else{
        return mid;
    }
}


// Another seems more useful function: Recursive Quick Sort Function
void swap(int * a, int * b) {
    int c = *b;
    *b = *a;
    *a = c;
}

int partition(int array[], int low, int high) { 
    // The i points to the boundary of lower and higher relative to chosen pivot (high one)
    // This function will lay pivot at a place where its left is less than or equal to it
    // while the right one will be larger or equal to it. And, we will return its index.
    int i = low - 1;
    int pivot = array[high];

    for(int j = low; j <= high - 1; j++) {
        if(array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[high]);
    return i + 1;
}

// The Divide and Conquer Method 
// Divide + Conquer + Combine
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);
        quickSort(array, low, p - 1);
        quickSort(array, p + 1, high);
    }
    else{
        return;
    }
}


// Recrusive Bubble sort
void bubbleSort(int array[], int size) {
    if(size == 0) {
        return ;
    }

    int swapped = 0;
    for(int i = 1; i < size; i ++) {
        if( array[i-1] > array[i]) {
            int temp = array[i-1];
            array[i-1] = array[i];
            array[i] = temp;
            swapped = 1;
        }
    }

    if(swapped == 1) {
        bubbleSort(array, size - 1);
    }
}


// Recursive Merge-Insertion sorting.
// only when we set i = 1 can we sort the array correctly
void merge_insert_Sorting(int array[], int size, int i) {
    if(i == size) {
        return;
    }

    int temp = array[i];
    int j;
    for(j = i - 1;(j >= 0 && array[j] > temp); j--) {
        array[j + 1] = array[j]; // right shift all the element larger than temp
    }
    array[j+1] = temp;

    merge_insert_Sorting(array, size, i+1);
}


void printArray(int array[], int size) {
    // We assume that size != 0
    printf("{");
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("}\n");
}


int main() {
    printf("factorial(5) = %d\n", factorial(5));
    printf("fibonacci(10) = %d\n", fibonacci(10));
    printf("choose(4,2) = %d\n", choose(4,2));

    printf("\n");
    printf("The stupid outDecimal(114514) = ");
    outDecimal(114514);

    printf("\n\n");
    int array[12] = {-1, 6, 3, 506, 23, -21, 5, 63, 53, 56, 324};
    int array_1[12] = {-1, 6, 3, 506, 23, -21, 5, 63, 53, 56, 324};
    int array_2[12] = {-1, 6, 3, 506, 23, -21, 5, 63, 53, 56, 324};
    int array_3[12] = {-1, 6, 3, 506, 23, -21, 5, 63, 53, 56, 324};
    printf("The below is the sorting method, the original array is:\n");
    printArray(array_1, 12);

    quickSort(array_1, 0, 11);
    printf("Quick Sort:\n");
    printArray(array_1, 12);

    bubbleSort(array_2, 12);
    printf("Bubble Sort:\n");
    printArray(array_2, 12);

    merge_insert_Sorting(array_3, 12, 1);
    printf("Merge Insert Sort:\n");
    printArray(array_3, 12);

    printf("\n");
    for(int i = 0; i < 12; i++) {
        printf("the index of %d is %d\n", array[i], binarysearch(array_2, 0, 11, array[i]));
    }

    return EXIT_SUCCESS;
}