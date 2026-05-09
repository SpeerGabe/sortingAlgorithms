#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// Generates random integers and writes them to a file
void generateRandomData(const string &filename, int size, int min, int max) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << " for writing." << endl;
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        file << (rand() % (max - min + 1) + min) << endl;
    }
    file.close();
}

// Reads integers from a file into a vector
vector<int> readDataFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << " for reading." << endl;
        exit(1);
    }
    vector<int> data;
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    file.close();
    return data;
}

// Writes sorted integers back to a file
void writeDataToFile(const string &filename, const vector<int> &data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << " for writing." << endl;
        exit(1);
    }
    for (int num : data) {
        file << num << endl;
    }
    file.close();
}

// Insertion sort — O(n²) — shifts elements right to insert each key in place
void insertionSort(vector<int> &data) {
    for (int i = 1; i < static_cast<int>(data.size()); ++i) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

// Counting sort — O(n + k) — tallies occurrences then reconstructs the sorted array
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
    // Seed random number generator so data differs on each run
    srand(static_cast<unsigned int>(time(0)));

    const string dataFile = "data.txt";
    const string resultFileInsertion = "result_insertion.txt";
    const string resultFileCounting = "result_counting.txt";
    const int dataSize = 10000;
    const int minValue = 0;
    const int maxValue = 1000;

    // Generate 10,000 random integers between 0 and 1000
    generateRandomData(dataFile, dataSize, minValue, maxValue);

    // Load the generated data into memory
    vector<int> data = readDataFromFile(dataFile);

    // Run and time insertion sort on a copy of the data
    vector<int> dataForInsertion = data;
    auto start = high_resolution_clock::now();
    insertionSort(dataForInsertion);
    auto stop = high_resolution_clock::now();
    writeDataToFile(resultFileInsertion, dataForInsertion);
    auto durationInsertion = duration_cast<milliseconds>(stop - start).count();

    // Run and time counting sort on a copy of the data
    vector<int> dataForCounting = data;
    start = high_resolution_clock::now();
    countingSort(dataForCounting, maxValue);
    stop = high_resolution_clock::now();
    writeDataToFile(resultFileCounting, dataForCounting);
    auto durationCounting = duration_cast<milliseconds>(stop - start).count();

    // Print results
    cout << "Insertion Sort: " << durationInsertion << " ms" << endl;
    cout << "Counting Sort:  " << durationCounting << " ms" << endl;

    return 0;
}
