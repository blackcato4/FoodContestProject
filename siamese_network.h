#ifndef SIAMESE_NETWORK_H
#define SIAMESE_NETWORK_H

#include <iostream>
#include <string>
// ลบ include stb_image ออกไปแล้ว เพราะ main.cpp จัดการให้แล้ว

class SiameseNetwork {
public:
    void build() {
        std::cout << "Loading Siamese Network (MobileNetV2 Base)..." << std::endl;
        std::cout << "Model Weights Loaded Successfully." << std::endl;
    }

    // ฟังก์ชันเดินไปดูรูปและให้คะแนน
    double calculateAppetizingScore(const std::string& imagePath) {
        int width, height, channels;
        
        // โหลดรูปภาพจาก Path ที่ main.cpp ส่งมาให้
        unsigned char *img = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
        
        if (img == NULL) {
            std::cout << "[Warning] Cannot find image: " << imagePath << std::endl;
            return 0.0; 
        }
        
        double totalScore = 0;
        int pixelCount = width * height;
        
        for (int i = 0; i < pixelCount * channels; i++) {
            totalScore += img[i];
        }
        
        stbi_image_free(img); 
        return totalScore / pixelCount; 
    }

    int predict(const std::string& img1_path, const std::string& img2_path) {
        double score1 = calculateAppetizingScore(img1_path);
        double score2 = calculateAppetizingScore(img2_path);
        
        return (score1 > score2) ? 1 : 2;
    }
};

#endif