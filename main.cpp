#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// ประกาศใช้งาน stb_image สำหรับโหลดรูป
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "siamese_network.h"

using namespace std;

int main() {
    cout << "\n--- Food Contest: Final Version ---" << endl;
    
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

    // *** บรรทัดสำคัญ: เปลี่ยนชื่อโฟลเดอร์ให้ตรงกับที่อาจารย์แจก ***
    string imageFolder = "Test Images/"; 

    int count = 0;
    while (getline(testFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string img1, img2;
        
        // อ่านชื่อไฟล์จาก CSV
        getline(ss, img1, ',');
        getline(ss, img2, ',');

        // ประกอบร่างเป็น Path เต็ม
        string path1 = imageFolder + img1;
        string path2 = imageFolder + img2;

        // ส่ง Path เข้าไปให้โมเดลประมวลผล
        int winner = model.predict(path1, path2);
        
        outFile << img1 << "," << img2 << "," << winner << endl;
        count++;
    }

    testFile.close();
    outFile.close();

    cout << "Step 2: Prediction Completed." << endl;
    cout << "SUCCESS: Processed " << count << " pairs of food." << endl;
    cout << "Result saved to: test_result_ready_to_submit.csv" << endl;

    return 0;
}