#include <iostream>
#include <ctime>

using namespace std;
void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);
const int NUMBERS_SIZE = 50000;
int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main() {
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr1, arr2, arr3);

    const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; //clock per milliseconds
    //...
    clock_t Start = clock();
    //call sort function here
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE-1);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quicksort (midpoint) runtime: " << elapsedTime << " ms" << endl;

    Start = clock();
    //call sort function here
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quicksort (medianOfThree) runtime: " << elapsedTime << " ms" << endl;

    Start = clock();
    //call sort function here
    InsertionSort(arr3, NUMBERS_SIZE-1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "InsertionSort runtime: " << elapsedTime << " ms" << endl;

}

int Quicksort_Partition(int numbers[], int lowIndex, int highIndex) {
    // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2; 
        int pivot = numbers[midpoint];

        bool done = false;
        while (!done) {
            // Increment lowIndex while numbers[lowIndex] < pivot
            while (numbers[lowIndex] < pivot) {
                lowIndex += 1;
            }

            // Decrement highIndex while pivot < numbers[highIndex]
            while (pivot < numbers[highIndex]) {
                highIndex -= 1;
            }

            // If zero or one elements remain, then all numbers are
            // partitioned. Return highIndex.
            if (lowIndex >= highIndex) {
                done = true;
            }
            else {
                // Swap numbers[lowIndex] and numbers[highIndex]
                int temp = numbers[lowIndex];
                numbers[lowIndex] = numbers[highIndex];
                numbers[highIndex] = temp;

                    // Update lowIndex and highIndex
                lowIndex += 1;
                highIndex -= 1;
            }
        }

        return highIndex;
}

/*this function sorts the given array in the range from i to k
using quicksort method. In this function, pivot is the midpoint
element (numbers[(i+k)/2]). (implementation of this function is
given in section 21.5)*/
void Quicksort_midpoint(int numbers[], int i, int k) {
    if (i >= k) {
        return;
    }
    

    int lowEndIndex = Quicksort_Partition(numbers, i, k);
        Quicksort_midpoint(numbers, i, lowEndIndex);
      
        Quicksort_midpoint(numbers, lowEndIndex + 1, k);
        
}
int medianOfThree(int numbers[], int left, int right) {
    int center = (left + right) / 2;
    if (numbers[center] < numbers[left]) {
        swap(numbers[left], numbers[center]);
    }
    if (numbers[right] < numbers[left]) {
        swap(numbers[left], numbers[right]);
    }
    if (numbers[right] < numbers[center]) {
        swap(numbers[center], numbers[right]);
    }

    //place pivot at position right - 1
    swap(numbers[center], numbers[right - 1]);

    int median = (left + right) / 2;
    int pivot = numbers[median]; //assign pivot to be the median

    bool done = false;
    int lowIndex = left;
    int highIndex = right;

    while (!done) {
        // Increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot) {
            lowIndex += 1;
        }

        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]) {
            highIndex -= 1;
        }

        // If zero or one elements remain, then all numbers are
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // Swap numbers[lowIndex] and numbers[highIndex]
            int temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;

            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }

    return highIndex;
   
}
/*this function utilizes different pivot selection technique in
quicksort algorithm. The pivot is the median of the following
three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2])
and rightmost (numbers[k]). You should modify the partition function
given in section 21.5 to select the pivot using median-of-three technique.*/
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k) {
        return;
    }
    
    int lowEndIndex = medianOfThree(numbers, i, k);
    
    Quicksort_medianOfThree(numbers, i, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}

/*this function sorts the given array using InsertionSort method. (implementation of this method is provided in section 21.3).*/
void InsertionSort(int numbers[], int numbersSize) {
    int i = 0;
    int j = 0;
    int temp = 0; // Temporary variable for swap

        for (i = 1; i < numbersSize; ++i) {
            j = i;
                // Insert numbers[i] into sorted part
                // stopping once numbers[i] in correct position
                while (j > 0 && numbers[j] < numbers[j - 1]) {

                    // Swap numbers[j] and numbers[j - 1]
                    temp = numbers[j];
                    numbers[j] = numbers[j - 1];
                    numbers[j - 1] = temp;
                    --j;
                }
        }
}

