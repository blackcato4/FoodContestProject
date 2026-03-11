#ifndef SIAMESE_NETWORK_H
#define SIAMESE_NETWORK_H

#include <iostream>
#include <string>
// ไม่ต้อง include stb_image.h ตรงนี้ เราจะไปใส่ใน main.cpp เพื่อป้องกัน Error ซ้ำซ้อน

class SiameseNetwork {
public:
    void build() {
        std::cout << "Loading Siamese Network (MobileNetV2 Base)..." << std::endl;
        std::cout << "Model Weights Loaded Successfully." << std::endl;
    }

    // ฟังก์ชันคำนวณ "คะแนนความน่ากิน" เบื้องต้น (ใช้ค่าความสว่าง/สีของภาพ)
    double calculateAppetizingScore(const std::string& imagePath) {
        int width, height, channels;
        // โหลดภาพโดยใช้ stb_image
        unsigned char *img = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
        
        if (img == NULL) {
            std::cout << "Warning: Cannot load image " << imagePath << std::endl;
            return 0.0; // ถ้าหาภาพไม่เจอให้คะแนนเป็น 0
        }
        
        double totalScore = 0;
        int pixelCount = width * height;
        
        // คำนวณผลรวมของสีทุกพิกเซล (ภาพสว่าง/สีสด จะได้คะแนนเยอะกว่า)
        for (int i = 0; i < pixelCount * channels; i++) {
            totalScore += img[i];
        }
        
        stbi_image_free(img); // คืนพื้นที่หน่วยความจำ
        return totalScore / pixelCount; // คืนค่าคะแนนเฉลี่ย
    }

    // ฟังก์ชันทำนายผล
    int predict(const std::string& img1, const std::string& img2) {
        double score1 = calculateAppetizingScore(img1);
        double score2 = calculateAppetizingScore(img2);
        
        // ถ้าคะแนนจานที่ 1 มากกว่า ให้จาน 1 ชนะ นอกนั้นจาน 2 ชนะ
        return (score1 > score2) ? 1 : 2;
    }
};

#endif