#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;
using namespace chrono;

// Function to generate random data and write to a file
void generateRandomData(const string &filename, int size, int min, int max) {
    ofstream file(filename);
    for (int i = 0; i < size; ++i) {
        file << (rand() % (max - min + 1) + min) << endl;
    }
    file.close();
}

// Function to read data from a file into a vector
vector<int> readDataFromFile(const string &filename) {
    ifstream file(filename);
    vector<int> data;
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    file.close();
    return data;
}

// Function to write sorted data to a file
void writeDataToFile(const string &filename, const vector<int> &data) {
    ofstream file(filename);
    for (int num : data) {
        file << num << endl;
    }
    file.close();
}

// Insertion Sort
void insertionSort(vector<int> &data) {
    for (size_t i = 1; i < data.size(); ++i) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

// Counting Sort
void countingSort(vector<int> &data, int max) {
    vector<int> count(max + 1, 0);
    for (int num : data) {
        count[num]++;
    }
    int index = 0;
    for (int i = 0; i <= max; ++i) {
        while (count[i]-- > 0) {
            data[index++] = i;
        }
    }
}

int main() {
    const string dataFile = "data.txt";
    const string resultFileInsertion = "result_insertion.txt";
    const string resultFileCounting = "result_counting.txt";
    const int dataSize = 10000;
    const int minValue = 0;
    const int maxValue = 1000;

    // Step 1: Generate random data
    generateRandomData(dataFile, dataSize, minValue, maxValue);

    // Step 2: Read data from file
    vector<int> data = readDataFromFile(dataFile);

    // Step 3: Sort using Insertion Sort
    vector<int> dataForInsertion = data;
    auto start = high_resolution_clock::now();
    insertionSort(dataForInsertion);
    auto stop = high_resolution_clock::now();
    writeDataToFile(resultFileInsertion, dataForInsertion);
    auto durationInsertion = duration_cast<milliseconds>(stop - start).count();
    cout << "Insertion Sort Time: " << durationInsertion << " ms" << endl;

    // Step 4: Sort using Counting Sort
    vector<int> dataForCounting = data;
    start = high_resolution_clock::now();
    countingSort(dataForCounting, maxValue);
    stop = high_resolution_clock::now();
    writeDataToFile(resultFileCounting, dataForCounting);
    auto durationCounting = duration_cast<milliseconds>(stop - start).count();
    cout << "Counting Sort Time: " << durationCounting << " ms" << endl;

    // Step 5: Compare results
    cout << "Comparison: " << endl;
    cout << "Insertion Sort: " << durationInsertion << " ms" << endl;
    cout << "Counting Sort: " << durationCounting << " ms" << endl;

    return 0;
}
