#include <iostream>
#include <exception>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <stdio.h>
#include <cmath>
#include <opencv2/ovis.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* const* argv) {

    // Resource for Sinbad entity
    cv::ovis::addResourceLocation("/packs/Sinbad.zip");

    // Window
    cv::Ptr<cv::ovis::WindowScene> win;
    std::string windowname = "Window";
    const cv::Size2i imsize(500, 500);
    win = cv::ovis::createWindow(windowname, imsize, cv::ovis::SCENE_INTERACTIVE | cv::ovis::SCENE_AA);

    // Entities
    win->createEntity("sinbad", "Sinbad.mesh", cv::Vec3f(0, 0, 0), cv::Vec3f(1.57, 0.0, 0.0));
    win->createLightEntity("sun", cv::Vec3f(0, 0, 100));

    // Needed waitKey
    cv::ovis::waitKey();
}