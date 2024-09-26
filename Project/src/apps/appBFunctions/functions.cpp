#ifndef _FUNCTIONS_CPP_
#define _FUNCTIONS_CPP_

#include "functions.hpp"

// processFrame
processedInformation processFrame(cv::Mat &frame, cv::Mat K, cv::Mat D, cv::Mat mask, int drawingType){
    
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);



    processedInformation info;
    info.estimatedPose = false;


    if(drawingType == 1){
        cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
    }
    else if(drawingType == 2){
        for(int i = 0; i < markerIds.size(); i++){

            int markerId = markerIds[i];

            if(markerId == 1){
                double markerSize = 0.10;
                std::vector<cv::Point3f> corners3D = { cv::Point3f ( -markerSize, markerSize,0 ),
                                                cv::Point3f ( markerSize, markerSize ,0 ),
                                                cv::Point3f ( markerSize, -markerSize,0 ),
                                                cv::Point3f ( -markerSize, -markerSize,0 )  };
                cv::Mat rvec, tvec;
                cv::solvePnP(corners3D, markerCorners[i], K, D, rvec, tvec);
                info.estimatedPose = true; info.rvec = rvec.clone(); info.tvec = tvec.clone();
                corners3D.push_back(cv::Point3f(0,0,markerSize));
                corners3D.push_back(cv::Point3f(0,0,0));
                std::vector<cv::Point2f> points2D;
                cv::projectPoints(corners3D, rvec, tvec, K, D, points2D);
                // Base exterior
                cv::line(frame, points2D[0], points2D[1], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[1], points2D[2], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[2], points2D[3], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[3], points2D[0], cv::Scalar(150,71,38), 2);
                // Piramid
                cv::line(frame, points2D[0], points2D[4], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[1], points2D[4], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[2], points2D[4], cv::Scalar(150,71,38), 2);
                cv::line(frame, points2D[3], points2D[4], cv::Scalar(150,71,38), 2);
            }
            else if(markerId == 2){
                // Base exterior
                cv::line(frame, markerCorners[i][0], markerCorners[i][1], cv::Scalar(217, 160, 137), 2); 
                cv::line(frame, markerCorners[i][1], markerCorners[i][2], cv::Scalar(217, 160, 137), 2);
                cv::line(frame, markerCorners[i][2], markerCorners[i][3], cv::Scalar(217, 160, 137), 2);
                cv::line(frame, markerCorners[i][3], markerCorners[i][0], cv::Scalar(217, 160, 137), 2);
                // Corners
                cv::circle(frame, markerCorners[i][0], 5, cv::Scalar(150,71,38), -1);
                cv::circle(frame, markerCorners[i][1], 5, cv::Scalar(150,71,38), -1);
                cv::circle(frame, markerCorners[i][2], 5, cv::Scalar(150,71,38), -1);
                cv::circle(frame, markerCorners[i][3], 5, cv::Scalar(150,71,38), -1);
                // Id printing
                cv::Point2f center = (markerCorners[i][0]+markerCorners[i][1]+markerCorners[i][2]+markerCorners[i][3])/4.0;
                cv::putText(frame, "Id: "+std::to_string(markerId), center, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(150,71,38), 1, false); 
            }
            else if(markerId == 3){
                // Mask applying
                double numCols = mask.cols; double numRows = mask.rows;
                std::vector<cv::Point2f> cornersmask = {cv::Point2f(0, 0),
                                                        cv::Point2f(numCols, 0),
                                                        cv::Point2f(numCols, numRows),
                                                        cv::Point2f(0, numRows)};
                cv::Mat H = cv::findHomography(cornersmask, markerCorners[i]);
                cv::Mat perspectiveMat; 
                cv::warpPerspective(mask, perspectiveMat, H, cv::Size(frame.cols, frame.rows));
                cv::Mat frameCopy = frame.clone();
                perspectiveMat.copyTo(frameCopy);
                perspectiveMat.copyTo(frame, frameCopy);
            }

        }
    }



    return info;

}




// initializeOvisWindow
void initializeOvisWindow(cv::Ptr<cv::ovis::WindowScene>& win, std::string windowname, cv::Size imsize_aux, std::string CamParam, std::string customObjectFile) {

    auto fs = cv::FileStorage();
    fs.open(CamParam, cv::FileStorage::READ);
    cv::Mat K, D;
    fs["camera_matrix"] >> K;
    fs["distortion_coefficients"] >> D;

    win = cv::ovis::createWindow(windowname, imsize_aux, cv::ovis::SCENE_INTERACTIVE | cv::ovis::SCENE_AA);
    win->setCameraIntrinsics(K, imsize_aux);
    win->createLightEntity("sun", cv::Vec3f(0, 0, 100));

    if(customObjectFile == "-"){ // No custom object configuration
        win->createEntity("sinbad", "Sinbad.mesh", cv::Vec3f(0, 0, 0), cv::Vec3f(1.57, 0.0, 0.0));
        win->playEntityAnimation("sinbad", "Dance");
        /* // Posible animations for sinbad
            std::vector<cv::String> outt;
            win->getEntityAnimations("sinbad", outt);
            std::cout << "\nPossible animations:" << std::endl;
            for (int i = 0; i < outt.size(); i++) {
                std::cout << "\t- " << outt[i] << std::endl;
            }
            std::cout << std::endl;
        */
    }
    else{
        win->createEntity("customObject", customObjectFile, cv::Vec3f(0, 0, 0), cv::Vec3f(1.57, 0.0, 0.0));   
    }

}


#endif
