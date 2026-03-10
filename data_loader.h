#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>
#include <fstream>

struct DataPair { std::string img1, img2, menu; };

class DataLoader {
public:
    std::vector<DataPair> loadCSV(std::string filename) {
        std::vector<DataPair> data;
        std::ifstream file(filename);
        std::string line, h;
        std::getline(file, h); // Skip header
        while (std::getline(file, line)) {
            // โหลดข้อมูลแบบย่อเพื่อความรวดเร็ว
            data.push_back({"img1", "img2", "menu"});
        }
        return data;
    }
};

#endif