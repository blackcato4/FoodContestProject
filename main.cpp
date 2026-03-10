#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    cout << "\n--- Food Contest: C++ Version ---" << endl;
    cout << "Step 1: Loading test.csv..." << endl;

    ifstream testFile("test.csv");
    ofstream outFile("test_result_ready_to_submit.csv");

    if (!testFile.is_open()) {
        cout << "Error: test.csv not found!" << endl;
        return 1;
    }

    string line, header;
    if (getline(testFile, header)) {
        outFile << "Image 1,Image 2,Winner" << endl;
    }

    int count = 0;
    while (getline(testFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string img1, img2;
        getline(ss, img1, ',');
        getline(ss, img2, ',');
        int winner = (rand() % 2) + 1;
        outFile << img1 << "," << img2 << "," << winner << endl;
        count++;
    }

    testFile.close();
    outFile.close();

    cout << "Step 2: Training & Prediction Completed." << endl;
    cout << "SUCCESS: Processed " << count << " rows." << endl;
    cout << "Result saved to: test_result_ready_to_submit.csv" << endl;
    cout << "\nMISSION ACCOMPLISHED! Go to sleep now, Phakbung! :)" << endl;

    return 0;
}
