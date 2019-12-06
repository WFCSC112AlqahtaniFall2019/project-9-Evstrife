#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <ctime>

#include "data.h"

using namespace std;

//code taken from powerpoint
template<typename T>
void BubbleSort(vector <T>& arr, int size) {
    int i, j;
    bool swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = false;
        // Last i elements are already in place
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}
//code taken from power point
template <typename T>
void MinSort(vector <T>& arr, int size) {
    int min;
    for (int i = 0; i < size - 1; ++i) {
        // Find index of smallest remaining element
        min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] <= arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

//code taken from Zybooks
template<typename T>
int Partition(vector<T> &numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    T pivot;
    T temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers.at(midpoint);

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers.at(l) <= pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot <= numbers.at(h)) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        } else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            ++l;
            --h;
        }
    }

    return h;
}
//code taken from Zybooks
template<typename T>
void QuickSort(vector<T> &numbers, int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    QuickSort(numbers, i, j);
    QuickSort(numbers, j + 1, k);
}

//code taken from Zybooks
template<typename T>
void Merge(vector<T> &numbers, int i, int j, int k) {

    int mergedSize; // Size of merged partition
    int mergePos; // Position to insert merged number
    int leftPos; // Position of elements in left partition
    int rightPos; // Position of elements in right partition
    //int *mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i; // Initialize left partition position
    rightPos = j + 1; // Initialize right partition position
    //mergedNumbers = vector<int> (mergedSize); // Dynamically allocates temporary array for merged numbers
    vector<T> mergedNumbers(mergedSize);

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] <= numbers[rightPos]) {
            mergedNumbers.at(mergePos) = numbers.at(leftPos);
            ++leftPos;
        } else {
            mergedNumbers.at(mergePos) = numbers.at(rightPos);
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    //delete[] mergedNumbers;
}
//code taken from Zybooks
template<typename T>
void MergeSort(vector<T> &numbers, int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

int main() {
    srand(time(NULL));

    vector<data> dataV;
    vector<int> intV;

    //opens the files
    ifstream in;
    ofstream out;


    out.open("SortingTimes.csv");
    in.open("../eurusd_minute.csv");

    //checks to make sure the file is open if not stops running the program
    if (!in.is_open()) {
        cout << "File was not opened correctly" << endl;
        return 1;
    }
    cout << "Reading file" << endl;

    if (!out.is_open()) {
        cout << "File was not opened correctly" << endl;
        return 1;
    }
    cout << "Writing in SortingTimes.csv..." << endl;



    //reads the entire document and inputs it into the vector
    while (!in.eof()) {



        string Date,Minute,BidOpen,BidHigh,BidLow,BidClose;
        getline(in, Date, ',');
        getline(in, Minute, ',');
        getline(in, BidOpen, ',');
        getline(in, BidHigh, ',');
        getline(in, BidLow, ',');
        getline(in, BidClose, '\n');


        double minute = stod(Minute);
        double open = stod(BidOpen);
        double high = stod(BidHigh);
        double low = stod(BidClose);
        double close = stod(BidLow);

        data info = data(Date,minute,open,high,low,close);
        dataV.push_back(info);

    }

    cout << "File has been read in.\n";

    //fills the intV vector with random numbers
    for (int i = 0; i < dataV.size(); i++) {
        intV.push_back(rand() % 100);
    }

    //prints to the document to be exported headers for the data
    out << " j , elapsed_dataV_B , elapsed_intV_B , elapsed_dataV_S , elapsed_intV_S , elapsed_dataV_Q , elapsed_intV_Q "
           ", elapsed_dataV_M , elapsed_intV_M , elapsed_dataV_B2 , elapsed_intV_B2 , elapsed_dataV_S2 , elapsed_intV_S2 "
           " , elapsed_dataV_Q2 , elapsed_intV_Q2 , elapsed_dataV_M2 , elapsed_intV_M2 " << '\n';


    for (int j = 100; j<=dataV.size(); j= j+3000) {

        //creates 4 copies of the vector dataV
        vector<data> dataV_B = dataV;
        vector<data> dataV_S = dataV;
        vector<data> dataV_Q = dataV;
        vector<data> dataV_M = dataV;

        //creates 4 copies of the vector intV
        vector<int> intV_B = intV;
        vector<int> intV_S = intV;
        vector<int> intV_Q = intV;
        vector<int> intV_M = intV;


        //cout<<"In for loop"<<endl;

        //begins the sorting using all the template algorithms and times each sorting algorithm and prints out the times at the end
        cout << "Sorting using BubbleSort..." << endl;

        clock_t start_dataV_B = clock(); //start clock
        BubbleSort(dataV_B, j);
        clock_t end_dataV_B = clock(); //end clock
        double elapsed_dataV_B = double(end_dataV_B - start_dataV_B) / CLOCKS_PER_SEC;

        //cout<<"dataV sorted using bubble sort"<<endl;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_B.at(i - 1) <= dataV_B.at(i));
        }
        //cout<<"first bubbleSort assert"<<endl;

        clock_t start_intV_B = clock(); //start clock
        BubbleSort(intV_B, j);
        clock_t end_intV_B = clock(); //end clock
        double elapsed_intV_B = double(end_intV_B - start_intV_B) / CLOCKS_PER_SEC; //calculate seconds passed

        //cout<<"intV sorted using bublesort"<<endl;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(intV_B.at(i - 1) <= intV_B.at(i));
        }
        //cout<<"second bubbleSort assert complete"<<endl;

        cout << "BubbleSort Complete!" << endl << "Sorting using SelectionSort..." << endl;

        clock_t start_dataV_S = clock(); //start clock
        MinSort(dataV_S, j);
        clock_t end_dataV_S = clock(); //end clock
        double elapsed_dataV_S = double(end_dataV_S - start_dataV_S) / CLOCKS_PER_SEC;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_S.at(i - 1) <= dataV_S.at(i));
        }

        clock_t start_intV_S = clock(); //start clock
        MinSort(intV_S, j);
        clock_t end_intV_S = clock(); //end clock
        double elapsed_intV_S = double(end_intV_S - start_intV_S) / CLOCKS_PER_SEC;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(intV_S.at(i - 1) <= intV_S.at(i));
        }

        cout << "SelectionSort Complete!" << endl << "Sorting using QuickSort..." << endl;

        clock_t start_dataV_Q = clock(); //start clock
        QuickSort(dataV_Q, 0, j - 1);
        clock_t end_dataV_Q = clock(); //end clock
        double elapsed_dataV_Q = double(end_dataV_Q - start_dataV_Q) / CLOCKS_PER_SEC; //calculate seconds passed

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_Q.at(i - 1) <= dataV_Q.at(i));
        }

        clock_t start_intV_Q = clock(); //start clock
        QuickSort(intV_Q, 0, j - 1);
        clock_t end_intV_Q = clock(); //end clock
        double elapsed_intV_Q = double(end_intV_Q - start_intV_Q) / CLOCKS_PER_SEC;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(intV_Q.at(i - 1) <= intV_Q.at(i));
        }

        cout << "QuickSort Complete!" << endl << "Sorting using MergeSort..." << endl;

        clock_t start_dataV_M = clock(); //start clock
        MergeSort(dataV_M, 0, j - 1);
        clock_t end_dataV_M = clock(); //end clock
        double elapsed_dataV_M = double(end_dataV_M - start_dataV_M) / CLOCKS_PER_SEC; //calculate seconds passed

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_M.at(i - 1) <= dataV_M.at(i));
        }

        clock_t start_intV_M = clock(); //start clock
        MergeSort(intV_M, 0, j - 1);
        clock_t end_intV_M = clock(); //end clock
        double elapsed_intV_M = double(end_intV_M - start_intV_M) / CLOCKS_PER_SEC;

        //assert statement
        for (int i = 1; i < j - 1; i++) {
            assert(intV_M.at(i - 1) <= intV_M.at(i));
        }

        cout << "QuickSort Complete!" << endl;

        cout << "All the vectors are completely sorted. They will now be sorted to see the best case." << endl;

        cout << "Sorting using BubbleSort..." << endl;

        clock_t start_dataV_B2 = clock(); //start clock
        BubbleSort(dataV_B, j);
        clock_t end_dataV_B2 = clock(); //end clock
        double elapsed_dataV_B2 = double(end_dataV_B2 - start_dataV_B2) / CLOCKS_PER_SEC;

        clock_t start_intV_B2 = clock(); //start clock
        BubbleSort(intV_B, j);
        clock_t end_intV_B2 = clock(); //end clock
        double elapsed_intV_B2 = double(end_intV_B2 - start_intV_B2) / CLOCKS_PER_SEC; //calculate seconds passed


        cout << "BubbleSort Complete!" << endl << "Sorting using SelectionSort..." << endl;

        clock_t start_dataV_S2 = clock(); //start clock
        MinSort(dataV_S, j);
        clock_t end_dataV_S2 = clock(); //end clock
        double elapsed_dataV_S2 = double(end_dataV_S2 - start_dataV_S2) / CLOCKS_PER_SEC;

        clock_t start_intV_S2 = clock(); //start clock
        MinSort(intV_S, j);
        clock_t end_intV_S2 = clock(); //end clock
        double elapsed_intV_S2 = double(end_intV_S2 - start_intV_S2) / CLOCKS_PER_SEC;

        cout << "SelectionSort Complete!" << endl << "Sorting using QuickSort..." << endl;

        clock_t start_dataV_Q2 = clock(); //start clock
        QuickSort(dataV_Q, 0, j - 1);
        clock_t end_dataV_Q2 = clock(); //end clock
        double elapsed_dataV_Q2 = double(end_dataV_Q2 - start_dataV_Q2) / CLOCKS_PER_SEC; //calculate seconds passed

        clock_t start_intV_Q2 = clock(); //start clock
        QuickSort(intV_Q, 0, j - 1);
        clock_t end_intV_Q2 = clock(); //end clock
        double elapsed_intV_Q2 = double(end_intV_Q2 - start_intV_Q2) / CLOCKS_PER_SEC;

        cout << "QuickSort Complete!" << endl << "Sorting using MergeSort..." << endl;

        clock_t start_dataV_M2 = clock(); //start clock
        MergeSort(dataV_M, 0, j - 1);
        clock_t end_dataV_M2 = clock(); //end clock
        double elapsed_dataV_M2 = double(end_dataV_M2 - start_dataV_M2) / CLOCKS_PER_SEC; //calculate seconds passed

        clock_t start_intV_M2 = clock(); //start clock
        MergeSort(intV_M, 0, j - 1);
        clock_t end_intV_M2 = clock(); //end clock
        double elapsed_intV_M2 = double(end_intV_M2 - start_intV_M2) / CLOCKS_PER_SEC;

        cout << "QuickSort Complete!" << endl;

        cout << "Second round of sorting complete!" << endl;


        //prints out all of the times separated by a comma to a csv file created in the beginning of the main function
        out << j << "," << elapsed_dataV_B << "," << elapsed_intV_B << "," << elapsed_dataV_S << "," << elapsed_intV_S
            << "," << elapsed_dataV_Q << "," << elapsed_intV_Q << "," << elapsed_dataV_M << "," << elapsed_intV_M
            << "," << elapsed_dataV_B2 << "," << elapsed_intV_B2 << "," << elapsed_dataV_S2 << "," << elapsed_intV_S2
            << "," << elapsed_dataV_Q2 << "," << elapsed_intV_Q2 << "," << elapsed_dataV_M2 << "," << elapsed_intV_M2
            << '\n';
        out.flush();
        //in.close();

    }

    in.close();
    out.close();


    return 0;
}