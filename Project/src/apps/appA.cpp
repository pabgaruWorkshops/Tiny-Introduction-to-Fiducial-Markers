#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ovis.hpp>
#include "appAFunctions/functions.hpp"

// Colors
#define GREEN  "\x1B[32m"
#define BGREEN  "\033[1m\033[32m"
#define BRED  "\033[1m\033[31m"
#define RESET  "\x1B[0m"


// Alerts
void printAlert(cv::String message){
    std::cout<<BRED<<"[!] "+message+" [!]"<<RESET<<std::endl;
}


// OpenCV Parameters
const cv::String keys =
"{help h usage ? | | Print this message. }"
// Camera
"{@cameraId |<none>| Set camera index. }"
"{@camParamsPath |<none>| Set camera params path. }"
"{outputVideoPath |output.avi| Path for the output video. Default: output.avi. Recommended format: avi.}"
;


// Main
int main(int argc, char**argv){

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Reading the parameters
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Wand Painter");
    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }
    std::cout<<std::endl;
    std::cout<<BGREEN<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Parameters: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<RESET<<std::endl;
    // Camera
    double cameraId = -1;
    if(parser.has("@cameraId")){
        cameraId = parser.get<double>("@cameraId");
    }else{
        printAlert("No camera id configured");
        return -1;
    }
    std::string camParamsPath = ""; 
    if(parser.has("@camParamsPath")){
        camParamsPath = parser.get<std::string>("@camParamsPath");
    }else{
        printAlert("No camera parameters configured");
        return -1;
    }
    std::cout<<GREEN<<"- Camera id: "<<RESET<<cameraId<<std::endl;
    std::cout<<GREEN<<"- Cam params path: "<<RESET<<camParamsPath<<std::endl;
    // Output video
    auto outputVideoPath = parser.get<std::string>("outputVideoPath");
    std::cout<<GREEN<<"- Output video path: "<<RESET<<outputVideoPath<<std::endl;
    std::cout<<BGREEN<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<RESET<<std::endl<<std::endl;




    /*~~~~~~~~~~~~~~~~~~~~~~~~~
        Openning the camera
    ~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cv::VideoCapture cap; double videoWidth, videoHeight;
    cap = cv::VideoCapture(cameraId);
    if (!cap.isOpened()){
        printAlert("Cannot open the camera");
        return -1;
    }
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
    cap.set(cv::CAP_PROP_FRAME_WIDTH,1920); videoWidth = 1920.0;
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,1080); videoHeight = 1080.0;
    cv::Size frameSize(1920, 1080);


    /*~~~~~~~~~~~~~~~~~~~~~~~~~
        Camera parameters
    ~~~~~~~~~~~~~~~~~~~~~~~~~*/
    auto fs = cv::FileStorage();
    fs.open(camParamsPath, cv::FileStorage::READ);
    cv::Mat K, D;
    fs["camera_matrix"] >> K;
    fs["distortion_coefficients"] >> D;


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Output video configuration
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cv::VideoWriter outputVideo;
    outputVideo.open(outputVideoPath, cv::VideoWriter::fourcc('P', 'I', 'M', '1'), cap.get(cv::CAP_PROP_FPS), frameSize, true);


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        User input configuration
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    bool showUserInputHelp = false;
    int drawingMode = 0;
    std::vector<std::string> drawingModeMessage = {"0: No drawing",
                                                   "1: Default detections drawing",
                                                   "2: Customized detections drawing"};
    std::vector<cv::String> userInputsOptions;
        userInputsOptions.push_back("User input options: ");
        userInputsOptions.push_back("   Escape: Finishes the execution");
        userInputsOptions.push_back("   d: Changes drawing mode");
        userInputsOptions.push_back("      - "+drawingModeMessage[0]);
        userInputsOptions.push_back("      - "+drawingModeMessage[1]);
        userInputsOptions.push_back("      - "+drawingModeMessage[2]);
        userInputsOptions.push_back("   h: Shows/Hides help");



    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Processing information
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cv::namedWindow("Processed camera", cv::WINDOW_GUI_EXPANDED);
    int processed_frames = 0;
    cv::Mat frame, outputFrame;
    while (true){
        
        // Frame obtaining
        cap >> frame;
        outputFrame = frame.clone();
        // Info on frame
            int linePoint=15; int step=15;
            cv::putText(outputFrame, "Frame: "+std::to_string(processed_frames), cv::Point2f(5,linePoint), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255,255,255), 1, false); linePoint+=step;
            // Drawing mode
            cv::putText(outputFrame, "Drawing mode "+drawingModeMessage[drawingMode], cv::Point2f(5,linePoint), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255,255,255), 1, false); linePoint+=step;
            // Help
            if(showUserInputHelp){
                for(int o = 0; o < userInputsOptions.size(); o++){
                    cv::putText(outputFrame, userInputsOptions[o], cv::Point2f(5,linePoint), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(217, 160, 137), 1, false); linePoint+=step;
                }
            }else{
                cv::putText(outputFrame, "Pulse 'h' to show/hide help", cv::Point2f(5,linePoint), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(217, 160, 137), 1, false); linePoint+=step;    
            }
            


        // Processing frame
        processedInformation info = processFrame(outputFrame, K, D, outputFrame, drawingMode);

        // Output show
        cv::imshow("Processed camera", outputFrame);

        /*~~~~~~~~~~~~~~~~~
            User inputs
        ~~~~~~~~~~~~~~~~~*/
        // User input
        int key = cv::waitKey(1);
        if(key == 27){ // [ Esc ]
            break;
        }
        if(key == 100){ // [ d ]
            drawingMode++;
            if(drawingMode > 2)
                drawingMode = 0;
        }
        if(key == 104){ // [ h ]
            showUserInputHelp = !showUserInputHelp;
        }

        // Output save
        outputVideo << outputFrame;
        processed_frames++;

    }


    // Release camera & video management
    cap.release();
    outputVideo.release();

    
    return 0;

}