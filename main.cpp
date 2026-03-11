#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// ต้องประกาศบรรทัดนี้ก่อน include stb_image.h เพื่อให้ใช้งานฟังก์ชันโหลดภาพได้
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "siamese_network.h"

using namespace std;

int main() {
    cout << "\n--- Food Contest: C++ Version ---" << endl;
    
    // 1. จำลองการโหลดโมเดล AI
    SiameseNetwork model;
    model.build();

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

        // 2. ให้โมเดลอ่านภาพและตัดสินใจ (ห้ามใช้ rand() แล้ว!)
        int winner = model.predict(img1, img2);
        
        outFile << img1 << "," << img2 << "," << winner << endl;
        count++;
    }

    testFile.close();
    outFile.close();

    cout << "Step 2: Prediction Completed." << endl;
    cout << "SUCCESS: Processed " << count << " rows." << endl;
    cout << "Result saved to: test_result_ready_to_submit.csv" << endl;
    cout << "\nMISSION ACCOMPLISHED! Good luck tomorrow!" << endl;

    return 0;
}