#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> // เพิ่มเข้ามาเพื่อใช้คำสั่ง system()

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "siamese_network.h"

using namespace std;

int main() {
    cout << "\n--- Food Contest: Winner Gallery Version (Compat) ---" << endl;
    
    SiameseNetwork model;
    model.build();

    // 1. สร้างโฟลเดอร์สำหรับเก็บรูปที่ชนะ (ใช้คำสั่ง Windows)
    system("mkdir Winners_Gallery 2> nul");

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

    // แก้ชื่อโฟลเดอร์ให้ตรงกับที่อาจารย์แจกพรุ่งนี้
    string imageFolder = "Test Images/"; 

    int count = 0;
    while (getline(testFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string img1, img2;
        getline(ss, img1, ',');
        getline(ss, img2, ',');

        string path1 = imageFolder + img1;
        string path2 = imageFolder + img2;

        int winner = model.predict(path1, path2);
        outFile << img1 << "," << img2 << "," << winner << endl;

        // --- ส่วนที่ก๊อปปี้รูป: ใช้คำสั่ง copy ของ Windows ---
        string winnerFilename = (winner == 1) ? img1 : img2;
        
        // แปลง / เป็น \ เพื่อให้ Windows เข้าใจ (ถ้ามี)
        string src = imageFolder + winnerFilename;
        string dst = "Winners_Gallery\\" + winnerFilename;
        
        // สร้างคำสั่ง copy "src" "dst" /Y (ทับไฟล์เดิมได้เลย)
        string cmd = "copy /Y \"" + src + "\" \"" + dst + "\" > nul";
        system(cmd.c_str());
        // ----------------------------------------------

        count++;
    }

    testFile.close();
    outFile.close();

    cout << "Step 2: Prediction & Gallery Collection Completed." << endl;
    cout << "SUCCESS: Processed " << count << " pairs." << endl;
    cout << "Check your winners in: /Winners_Gallery" << endl;

    return 0;
}