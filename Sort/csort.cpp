#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Getopt
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// #define DEBUG
#define DEFAULT_TEST_SIZE 1000000

void print_usage_exception() {
    printf("Usage: csort -g | csort -c <algorithm> -f <filename> -n <test_size>\n");
    exit(241);
}

void print_algorithm_exception() {
    printf("Error: invalid algorithm argument.\n");
    printf("Usage: -c {bubble, selection, insertion, merge, qsort}\n");
    exit(242);
}

void print_file_exception() {
    printf("Error: fail to open file.\n");
    exit(243);
}

void print_size_exception() {
    printf("Error: specified test size is greater than data size.\n");
    exit(244);
}

void bubbleSort(const vector<int>& numbers) {
    #ifdef DEBUG
    printf("Running bubbleSort...\n");
    #endif
    vector<int> vec(numbers);
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i+1; j < vec.size(); j++) {
            if (vec[i] > vec[j]) {
                swap(vec[i], vec[j]);
            }
        }
    }
    #ifdef DEBUG
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "done with bubbleSort." << endl;
    #endif
}

void selectionSort(const vector<int>& numbers) {
    #ifdef DEBUG
    printf("Running selectionSort...\n");
    #endif
    vector<int> vec(numbers);
    for (int i = 0; i < vec.size(); i++) {
        int min = i;
        for (int j = i+1; j < vec.size(); j++) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        // TODO: swap smallest value to proper place
        if (min != i) {
            swap(vec[min], vec[i]);
        }
    }

    #ifdef DEBUG
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "done with selectionSort." << endl;
    #endif
}

void insertionSort(const vector<int>& numbers) {
    #ifdef DEBUG
    printf("Running insertionSort...\n");
    #endif
    vector<int> vec(numbers);
    // the first element do not have to move
    for (int i = 1; i < vec.size(); i++) {
        int temp = vec[i];
        // TODO: slide elements in sorted list right to make room for numbers[i]
        int j = i;
        while (j >= 1 && vec[j-1] > temp) {
            vec[j] = vec[j-1];
            j--;
        }
        vec[j] = temp;
    }
    #ifdef DEBUG
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "done with insertionSort." << endl;
    #endif
}


void mergeSortHelper(vector<int>& vec) {
    if (vec.size() > 1) {
        // TODO: split array in half
        int halfSize = vec.size() / 2;
        vector<int> left(vec.begin(), vec.begin() + halfSize);
        vector<int> right(vec.begin() + halfSize, vec.end());
        // TODO: sort halves
        mergeSortHelper(left);
        mergeSortHelper(right);
        // TODO: merge
        int pl = 0;
        int pr = 0;
        int i = 0;
        while ((pl < left.size()) && (pr < right.size())) {
            if (left[pl] < right[pr]) {
                vec[i++] = left[pl];
                pl++;
            }
            else {
                vec[i++] = right[pr];
                pr++;
            }
        }
        while (pl < left.size()) {
            vec[i++] = left[pl++];
        }
        while (pr < right.size()) {
            vec[i++] = right[pr++];
        }
    }
}

void mergeSort(const vector<int>& numbers) {
    #ifdef DEBUG
    printf("Running mergeSort...\n");
    #endif
    vector<int> vec(numbers);
    mergeSortHelper(vec);
    #ifdef DEBUG
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "done with mergeSort." << endl;
    #endif
}

void quickSortHelper(vector<int>& vec, int l, int r) {
    if (l < r) {
        int pivot = l + ((r - l) >> 1);
        int i = l;
        int j = r;
        while (i < j) {
            while ((vec[i] < vec[pivot]) && (i < r)) i++;
            while ((vec[j] >= vec[pivot]) && (j > l)) j--;

            if (i < j) {
                swap(vec[i], vec[j]);
            }
        }
        swap(vec[pivot], vec[i]);
        quickSortHelper(vec, l, i - 1);
        quickSortHelper(vec, i + 1, r);
    }
}

void quickSort(const vector<int>& numbers) {
    #ifdef DEBUG
    printf("Running quickSort...\n");
    #endif
    vector<int> vec(numbers);
    quickSortHelper(vec, 0, vec.size()-1);
    #ifdef DEBUG
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "done with quickSort." << endl;
    #endif
}

void readFromFile(vector<int>& numbers, const string filename) {
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail()) {
        print_file_exception();
    }
    int number;
    while (infile >> number) {
        numbers.push_back(number);
    }
    infile.close();
}

int RandomInteger(int low, int high) {
    // Normalization: the reason for typecast here is RAND_MAX is the max number for int
    double d = rand() / (double(RAND_MAX) + 1);
    // typecast: "high - low" may overflow when comes to int
    double scale = d * (double(high) - low + 1);

    return int(floor(low + scale));
}

void dataGenerator(const string filename, int size) {
    ofstream outfile(filename.c_str()); // create and write
    for (int i = 0; i < size; i++) {
        outfile << RandomInteger(100, 1000) << " ";
    }
    outfile.close();
}

int main(int argc, char* argv[]) {
    int option;
    int gFlag = 0;
    int cFlag = 0;
    int fFlag = 0;
    int nFlag = 0;
    string algorithm;  // which algorithm to run
    string filename;    // data file
    int size;          // test with data [0, size)
    while ((option = getopt(argc, argv, "gc:f:n:")) != -1) {
        switch (option) {
        case 'g':
            gFlag = 1;
            break;
        case 'c':
            // algorithm = strdup(optarg);
            algorithm = string(optarg);
            cFlag = 1;
            break;
        case 'f': 
            filename = string(optarg);
            fFlag = 1;
            break;
        case 'n':
            size = atoi(optarg);
            nFlag = 1;
            break;
        case '?':
            print_usage_exception();
            break;
        default:
            printf("Error: getopt.\n");
            exit(240);
            break;
        }
    }

    // TODO: check correctness of flag status
    // -g is exclusive to -c and -f
    if ((gFlag == 1) && ((cFlag | fFlag) == 1)) {
        print_usage_exception();
    }
    int valid = 0;
    if (gFlag == 1) {
        valid = 6;
    }

    if (((cFlag & fFlag) != 1) && (gFlag == 0)) {
        print_usage_exception();
    } 
    else {
        // TODO: check algorithm validation
        if (cFlag) {
            // -c <algorithm> -f <file>
            if (algorithm == "bubble") valid = 1;
            if (algorithm == "insertion") valid = 2;
            if (algorithm == "selection") valid = 3;
            if (algorithm == "merge") valid = 4;
            if (algorithm == "qsort") valid = 5;
            if (valid == 0) {
                print_algorithm_exception();
            }
        }
        
        // TODO: read data from input file
        vector<int> numbers;
        int defaultSize = DEFAULT_TEST_SIZE;
        int dataSize = 0;
        if (gFlag == 0) {
            readFromFile(numbers, filename);
            dataSize = numbers.size();
        }
        
        if (nFlag == 0) {
            size = min(defaultSize, dataSize); 
        }
        else {
            if (size > dataSize) {
                print_size_exception();
            }
        }

        vector<int> testData(numbers.begin(), numbers.begin() + size);
        #ifdef DEBUG
        // TODO: display input data
        printf("Total size of test data: %lu\n", testData.size());
        for (int i = 0; i < testData.size(); i++) {
            printf("%d ", testData[i]);
        }
        printf("\n");
        #endif

        enum {BUBBLE = 1, INSERTION, SELECTION, MERGE, QSORT, GENERATOR};
        switch (valid)
        {
        case BUBBLE:
            bubbleSort(testData);
            break;
        case INSERTION:
            insertionSort(testData);
            break;
        case SELECTION:
            selectionSort(testData);
            break;
        case MERGE:
            mergeSort(testData);
            break;
        case QSORT:
            quickSort(testData);
            break;
        case GENERATOR:
            dataGenerator("data", DEFAULT_TEST_SIZE);
            break;
        default:
            break;
        }
    }

    return 0;
}
