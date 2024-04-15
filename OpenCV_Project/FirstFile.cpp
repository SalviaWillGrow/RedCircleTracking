#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/types_c.h"

using namespace std;
using namespace cv;
/*
IplImage* imgTracking = 0;

int lastX1 = -1;
int lastY1 = -1;

int lastX2 = -1;
int lastY2 = -1;
*/
int ReadVideo() {

    //open the video file for reading
    VideoCapture cap("testvideo.gif");

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    //Uncomment the following line if you want to start the video in the middle
    //cap.set(CAP_PROP_POS_MSEC, 300); 

    //get the frames rate of the video
    double fps = cap.get(CAP_PROP_FPS);
    cout << "Frames per seconds : " << fps << endl;

    String window_name = "My First Video";

    namedWindow(window_name, WINDOW_NORMAL); //create a window

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop at the end of the video
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }

    return 0;
}

int OpenCamera() {

    //Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    string window_name = "My Camera Feed";
    namedWindow(window_name); //create a window called "My Camera Feed"

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get(); //Wait for any key press
            break;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop 
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }

    return 0;
}

int ReadImage() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    Mat image = imread("flower.jpg");

    if (image.empty()) {
        cout << "Can't open" << endl;
        cin.get();
        return -1;
    }

    String windowName = "The Flower";
    namedWindow(windowName);
    imshow(windowName, image);

    waitKey(0);
    destroyWindow(windowName);

}

int DetectRed() {

    VideoCapture cap(0); //capture the video from web cam

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    namedWindow("Control"); //create a window called "Control"

    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 130;
    int iHighS = 255;

    int iLowV = 40;
    int iHighV = 255;

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat imgHSV;

        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        Mat imgThresholded;

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        Mat imgBlur;
        medianBlur(imgThresholded, imgBlur, 1);

        imshow("Result Image", imgBlur);
        imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }
}

int DetectRedShape() {

    Mat imgRaw = imread("shapes.png");

    if (imgRaw.empty()) {
        cout << "Can't open" << endl;
        cin.get();
        return -1;
    }

    String windowRaw = "Raw image";
    namedWindow(windowRaw);
    imshow(windowRaw, imgRaw);

    namedWindow("Control"); //create a window called "Control"

    int iLowH = 170;
    int iHighH = 179;

    int iLowS = 130;
    int iHighS = 255;

    int iLowV = 40;
    int iHighV = 255;

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    while (true) {

        Mat imgHSV;

        cvtColor(imgRaw, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        Mat imgThresholded;

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        //imshow("Thresholded Image", imgThresholded); //show the thresholded image

        Mat imgBlur;
        medianBlur(imgThresholded, imgBlur, 7);

        imshow("Blurred Image", imgBlur);



        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }
}


void trackObject(IplImage* imgThresh) {
    CvSeq* contour;  //hold the pointer to a contour
    CvSeq* result;     //hold sequence of points of a contour
    CvMemStorage* storage = CreateMemStorage(0); //storage area for all contours

    //finding all contours in the image
    FindContours(imgThresh, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

    //iterating through each contour
    while (contour)
    {
        //obtain a sequence of points of the countour, pointed by the variable 'countour'
        result = ApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour) * 0.02, 0);

        //if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels
        if (result->total == 3 && fabs(ContourArea(result, CV_WHOLE_SEQ)) > 100)
        {
            //iterating through each point
            CvPoint* pt[3];
            for (int i = 0; i < 3; i++) {
                pt[i] = (CvPoint*)GetSeqElem(result, i);
            }

            int posX = (pt[0]->x + pt[1]->x + pt[2]->x) / 3;
            int posY = (pt[0]->y + pt[1]->y + pt[2]->y) / 3;

            if (posX > 360) {
                if (lastX1 >= 0 && lastY1 >= 0 && posX >= 0 && posY >= 0) {
                    // Draw a red line from the previous point to the current point
                    cvLine(imgTracking, cvPoint(posX, posY), cvPoint(lastX1, lastY1), cvScalar(0, 0, 255), 4);
                }

                lastX1 = posX;
                lastY1 = posY;
            }
            else {
                if (lastX2 >= 0 && lastY2 >= 0 && posX >= 0 && posY >= 0) {
                    // Draw a blue line from the previous point to the current point
                    cvLine(imgTracking, cvPoint(posX, posY), cvPoint(lastX2, lastY2), cvScalar(255, 0, 0), 4);
                }

                lastX2 = posX;
                lastY2 = posY;
            }
        }

        //obtain the next contour
        contour = contour->h_next;
    }

    ReleaseMemStorage(&storage);
}

int DetectShapes() {
    //load the video file to the memory
    CvCapture* capture = CaptureFromAVI("E:/Projects/Robot/IESL Robot/robot/a.avi");

    if (!capture) {
        printf("Capture failure\n");
        return -1;
    }

    IplImage* frame = 0;
    frame = QueryFrame(capture);
    if (!frame) return -1;

    //create a blank image and assigned to 'imgTracking' which has the same size of original video
    imgTracking = CreateImage(GetSize(frame), IPL_DEPTH_8U, 3);
    Zero(imgTracking); //covert the image, 'imgTracking' to black

    NamedWindow("Video");

    //iterate through each frames of the video     
    while (true) {

        frame = QueryFrame(capture);
        if (!frame) break;
        frame = CloneImage(frame);

        //smooth the original image using Gaussian kernel
        Smooth(frame, frame, CV_GAUSSIAN, 3, 3);

        //converting the original image into grayscale
        IplImage* imgGrayScale = CreateImage(cvGetSize(frame), 8, 1);
        CvtColor(frame, imgGrayScale, CV_BGR2GRAY);

        //thresholding the grayscale image to get better results
        threshold(imgGrayScale, imgGrayScale, 100, 255, CV_THRESH_BINARY_INV);

        //track the possition of the ball
        trackObject(imgGrayScale);

        // Add the tracking image and the frame
        add(frame, imgTracking, frame);

        ShowImage("Video", frame);

        //Clean up used images
        ReleaseImage(&imgGrayScale);
        ReleaseImage(&frame);

        //Wait 10mS
        int c = WaitKey(10);
        //If 'ESC' is pressed, break the loop
        if ((char)c == 27) break;
    }

    DestroyAllWindows();
    ReleaseImage(&imgTracking);
    ReleaseCapture(&capture);

    return 0;
}


int main() {

    DetectRedShape();

    return 0;
}
