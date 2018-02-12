//  ImageEditor.hpp
//  Image Manipulator

#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <iostream>
#include <opencv2/opencv.hpp>

class ImageEditor {
private:
    std::string windowName = "Edited Image";
    std::string imageName;
    
    cv::Mat source;
    cv::Mat destination;
    
    void createNegativeImage(int size);
    void rotateImage(int rotation);
    void dilateImage(int dSize);
    void erodeImage(int eSize);
    
public:
    ImageEditor() { };
    void run();
};

#endif /* ImageEditor_hpp */
