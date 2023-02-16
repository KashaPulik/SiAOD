#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define LOW 50000
#define HIGH 1000000
#define STEP 50000

uint32_t findMax(uint32_t* arr, int size);
uint32_t number(uint32_t arrit, int k);
void radixSort(uint32_t* arr, int size);
void selectionSort(uint32_t* arr, int arrLength);
void merge(uint32_t* arr, int low, int mid, int high);
void mergeSort(uint32_t* arr, int low, int high);
int getrand(int min, int max);
double wtime();

int main()
{
    uint32_t* testArr;
    uint32_t* copy1;
    uint32_t* copy2;
    uint32_t* copy3;

    int i, j;

    double startTime, resultTime;

    for (i = LOW; i <= HIGH; i += STEP) {
        testArr = (uint32_t*)malloc(i * sizeof(uint32_t));
        copy1 = (uint32_t*)malloc(i * sizeof(uint32_t));
        copy2 = (uint32_t*)malloc(i * sizeof(uint32_t));
        copy3 = (uint32_t*)malloc(i * sizeof(uint32_t));

        for (j = 0; j < i; j++) {
            testArr[j] = (uint32_t)getrand(0, 100001);
            copy1[j] = testArr[j];
            copy2[j] = testArr[j];
            copy3[j] = testArr[j];
        }

        printf("%d\t", i);

        startTime = wtime();
        radixSort(copy1, i);
        resultTime = wtime() - startTime;
        printf("%13.7lf", resultTime);

        startTime = wtime();
        selectionSort(copy2, i);
        resultTime = wtime() - startTime;
        printf("%13.7lf", resultTime);

        startTime = wtime();
        mergeSort(copy3, 0, i - 1);
        resultTime = wtime() - startTime;
        printf("%13.7lf", resultTime);

        printf("\n");

        free(testArr);
        free(copy1);
        free(copy2);
        free(copy3);
    }
}

uint32_t findMax(uint32_t* arr, int size)
{
    uint32_t max = 0;
    for (int i = 0; i < size; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

uint32_t number(uint32_t arrit, int k)
{
    return (arrit / (uint32_t)pow(10, k - 1)) % 10;
}

void radixSort(uint32_t* arr, int size)
{
    int i;
    int k = 1;
    uint32_t helpArr[size];
    uint32_t max = findMax(arr, size);

    while (max / (uint32_t)pow(10, k - 1) > 0) {
        uint32_t digits[10] = {0};

        for (i = 0; i < size; i++) {
            digits[number(arr[i], k)]++;
        }

        for (i = 1; i < 10; i++) {
            digits[i] += digits[i - 1];
        }

        for (i = size - 1; i >= 0; i--) {
            helpArr[--digits[number(arr[i], k)]] = arr[i];
        }

        for (i = 0; i < size; i++) {
            arr[i] = helpArr[i];
        }

        k++;
    }
}

void selectionSort(uint32_t* arr, int arrLength)
{
    int start, indexmin;
    uint32_t min;
    for (int i = 0; i < arrLength; i++) {
        indexmin = i;
        start = i;
        for (int j = start; j < arrLength - 1; j++) {
            if (arr[indexmin] > arr[j + 1]) {
                indexmin = j + 1;
            }
        }
        min = arr[indexmin];
        arr[indexmin] = arr[start];
        arr[start] = min;
    }
}

void merge(uint32_t* arr, int low, int mid, int high)
{
    uint32_t* helpArr = (uint32_t*)malloc((high + 1) * sizeof(uint32_t));
    for (int i = low; i <= high; i++) {
        helpArr[i] = arr[i];
    }
    int l = low;
    int r = mid + 1;
    int i = low;

    while ((l <= mid) && (r <= high)) {
        if (helpArr[l] <= helpArr[r]) {
            arr[i] = helpArr[l];
            l++;
        } else {
            arr[i] = helpArr[r];
            r++;
        }
        i++;
    }

    while (l <= mid) {
        arr[i] = helpArr[l];
        l++;
        i++;
    }

    while (r <= high) {
        arr[i] = helpArr[r];
        r++;
        i++;
    }
    free(helpArr);
}

void mergeSort(uint32_t* arr, int low, int high)
{
    if (low < high) {
        int mid = floor((low + high) / 2);
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}