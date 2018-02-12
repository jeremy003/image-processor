//  ImageEditor.cpp
//  Image Manipulator

#include "ImageEditor.hpp"

using namespace std;
using namespace cv;

void ImageEditor::run() {
    cout << "Let's edit an image! First enter the name of the image you'd like to edit: ";
    cin >> imageName;

    source = imread(imageName);

    if (source.empty()) {
        cout << "Couldn't find the image, check spelling." << endl;
        return;
    }

    destination = source.clone();

    startWindowThread();

    imshow("original", source);
    moveWindow("original", 0, 0);
    waitKey(1);

    namedWindow(windowName);
    moveWindow(windowName, source.size().width, 0);

    bool quit = false;
    int choice = -1, secondChoice = 0;
    double scale;
    string savedImage;

    while (!quit) {
        cout << "Choose an option to edit the image: " << endl
        << "0: Done editing" << endl
        << "1: Save as" << endl
        << "2: Resize" << endl
        << "3: Rotate" << endl
        << "4: Negative" << endl
        << "5: Dialate" << endl
        << "6: Erode" << endl;

        cin >> choice;

        switch (choice) {
            case 0:
                quit = true;
                break;

            case 1:
                cout << "Enter name of new image: ";
                cin >> savedImage;
                imwrite(savedImage, destination);
                break;

            case 2:
                cout << "Enter scale of resizing between 0 and 2: ";
                cin >> scale;
                while (scale <= 0 || scale > 2) {
                    cout << "Enter scale of resizing between 0 and 2: ";
                    cin >> scale;
                }
                resize(destination, destination, Size(), scale, scale);
                imshow(windowName, destination);
                waitKey(1);
                break;

            case 3:
                cout << "Angle of rotation: ";
                cin >> secondChoice;
                rotateImage(secondChoice);
                imshow(windowName, destination);
                waitKey(1);
                break;

            case 4:
                cout << "Enter kernal size: ";
                cin >> secondChoice;
                while (secondChoice < 0) {
                    cout << "Enter kernal size: ";
                    cin >> secondChoice;
                }
                createNegativeImage(secondChoice);
                break;
                
            case 5:
                cout << "Enter dialation size: ";
                cin >> secondChoice;
                dilateImage(secondChoice);
                break;
                
            case 6:
                cout << "Enter erosion size: ";
                cin >> secondChoice;
                erodeImage(secondChoice);
                break;

            default:
                cout << "Invalid Option" << endl;
                break;
        }
    }

    destroyWindow("original");
    destroyWindow(windowName);
}

void ImageEditor::createNegativeImage(int size) {
    int operation = 5;
    int morph_element = 2;
    char option;

    Mat element = getStructuringElement(morph_element, Size(2*size + 1, 2*size+1), Point(size, size));
    
    Mat temp = destination.clone();

    /// Apply the specified morphology operation
    morphologyEx(destination, temp, operation, element );
    imshow(windowName, temp);
    waitKey(1);
    
    cout << "Keep this change? (y/n): ";
    cin >> option;
    
    if (option == 'y') {
        cout << "Keeping change..." << endl;
        destination = temp.clone();
    } else {
        cout << "Disregarding change..." << endl;
    }
    
    imshow(windowName, destination);
    waitKey(1);
}

void ImageEditor::rotateImage(int rotation){
    int length = max(destination.cols, destination.rows);
    Point2f center(length/2., length/2.);
    Mat rotationMat = getRotationMatrix2D(center, rotation, 1.0);
    warpAffine(destination, destination, rotationMat, destination.size());
}

void ImageEditor::dilateImage(int dSize) {
    char option;
    int size = (dSize*2) + 1;
    Mat temp = destination.clone();
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size, size), Point(dSize, dSize));
    dilate(destination, temp, element);
    
    imshow(windowName, temp);
    waitKey(1);
    
    cout << "Keep this change? (y/n): ";
    cin >> option;
    
    if (option == 'y') {
        cout << "Keeping change..." << endl;
        destination = temp.clone();
    } else {
        cout << "Disregarding change..." << endl;
    }
    
    imshow(windowName, destination);
    waitKey(1);
}

void ImageEditor::erodeImage(int eSize) {
    char option;
    int size = (eSize*2) + 1;
    Mat temp = destination.clone();
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(size, size), Point(eSize, eSize));
    erode(destination, temp, element);
    
    imshow(windowName, temp);
    waitKey(1);
    
    cout << "Keep this change? (y/n): ";
    cin >> option;
    
    if (option == 'y') {
        cout << "Keeping change..." << endl;
        destination = temp.clone();
    } else {
        cout << "Disregarding change..." << endl;
    }
    
    imshow(windowName, destination);
    waitKey(1);
}


