#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main(){

    std::cout<<"Printing aruco markers..."<<std::endl;

    cv::Mat markerImage;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);


    int numOfMarkers = 10;
    for(int i = 1; i <= numOfMarkers; i++){
        std::cout<<"\t> Marker id: "<<i<<std::endl;
        cv::aruco::drawMarker(dictionary, i, 500, markerImage, 1);
        cv::imwrite("Markers/marker"+std::to_string(i)+".png", markerImage);
    }


}