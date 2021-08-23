#include <stdio.h>
#include <stdlib.h> 
#include <string>
#include <jsoncpp/json/json.h> // to parse configuration parameters from json file
#include <fstream>
#include <thread>
#include <mutex>
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "camera_config.hpp"
#include "calibration_window.hpp"
#include <QtWidgets/QApplication>

void detectCorners(cv::Mat &img, cv::Size _patternSize, bool& patternFound,  std::vector<cv::Point2f>& corners);
std::mutex s;
// Read Json File
camConfigJson jsonReader(const std::string _config_file_path, const int _CONF_ID)
{   camConfigJson _config_params;    
    std::ifstream config_doc(_config_file_path, std::ifstream::binary);
    Json::Value root; 
    Json::CharReaderBuilder rbuilder;
    std::string errs;
    bool parsingSuccessful = Json::parseFromStream(rbuilder, config_doc, &root, &errs);
    if(!parsingSuccessful)
    {
        std::cout << "Failed to parse configuration\n"<<errs<<std::endl;
        std::exit(1);
    }

    const Json::Value& root_node = root["configurations"];    
    _config_params.capture_width = root_node[_CONF_ID]["capture_width"].asInt();
    _config_params.capture_height = root_node[_CONF_ID]["capture_height"].asInt();
    _config_params.display_width = root_node[_CONF_ID]["display_width"].asInt();
    _config_params.display_height = root_node[_CONF_ID]["display_height"].asInt();
    _config_params.frame_rate = root_node[_CONF_ID]["frame_rate"].asInt();
    _config_params.flip_method = ROTATE_180;

    return _config_params;
}

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    CalibrationWindow w;
    w.show();

    // Reading camera configurations except intrinsics and extrinsics
    camConfigJson conf_struct_var; 
    // fetch all configuration parameters from json file to the argument
    conf_struct_var = jsonReader(constants::CONFIG_FILE_PATH, constants::CONF_ID);  
    // initialize stereo camera class 
    GsStereoCamera st_cam{conf_struct_var.capture_width, conf_struct_var.capture_height, conf_struct_var.display_width, conf_struct_var.display_height, conf_struct_var.frame_rate, conf_struct_var.flip_method};
    // fetch pipeline strings for each camera
    std::string pipeline1, pipeline2;
    std::tie(pipeline1, pipeline2) = st_cam.getStereoGsPipeline();

    cv::VideoCapture camLeft(pipeline1, cv::CAP_GSTREAMER);
    cv::VideoCapture camRight(pipeline2, cv::CAP_GSTREAMER); 

    if(!camLeft.isOpened())
    {
        printf("cam0 is not opened. \n");
        return -1;
    }
    if(!camRight.isOpened())
    {
          printf("cam1 is not opened. \n");
         return -1;
    }

    cv::Mat rgbLeft, rgbRight;
    cv::Mat grayLeft, grayRight;
    
    while(camLeft.isOpened() && camRight.isOpened())
    {        
        
        camLeft >> rgbLeft;
        camRight >> rgbRight; 

        if( !rgbLeft.data || !rgbRight.data )
        {
            std::cerr<< " --(!) Error reading images " << std::endl; 
            return -1; 
        }
        
        // Converting left right images to gray scale          
        cv::cvtColor(rgbLeft, grayLeft, cv::COLOR_BGR2GRAY);
        cv::cvtColor(rgbRight, grayRight, cv::COLOR_BGR2GRAY);

        //-- And create the image in which we will save our disparities
        assert((grayLeft.size() == grayRight.size()) && "Sizes of two camera images are not equal");        
        if( !grayLeft.data || !grayRight.data )
        {
            std::cout<< " --(!) Error reading images " << std::endl; 
            return -1; 
        }
              
        
        std::thread thr_1(detectCorners, std::ref(grayLeft), w.patternSize, std::ref(w.patternFound[0]), std::ref(w.leftimg_corners));
        std::thread thr_2(detectCorners, std::ref(grayRight), w.patternSize, std::ref(w.patternFound[1]), std::ref(w.rightimg_corners));  
        if (thr_1.joinable())
        {
            thr_1.join();
        }
        
        if (thr_2.joinable())
        {
            thr_2.join();
        }      
        
        // to show left and right images
        QImage qimgLeft(grayLeft.data, grayLeft.cols, grayLeft.rows, grayLeft.step, QImage::Format_RGB888);
        QImage qimgRight(grayRight.data, grayRight.cols, grayRight.rows, grayRight.step, QImage::Format_RGB888);
        w.pixmap_left.setPixmap(QPixmap::fromImage(qimgLeft.rgbSwapped()));
        w.pixmap_right.setPixmap(QPixmap::fromImage(qimgRight.rgbSwapped()));

        
        qApp->processEvents();        
    }
    return a.exec();;
}

void detectCorners(cv::Mat& grayimg, cv::Size _patternSize, bool& patternfound, std::vector<cv::Point2f>& corners)
{
        s.lock();
        //CALIB_CB_FAST_CHECK saves a lot of time on images
        //that do not contain any chessboard corners
        patternfound = findChessboardCorners(grayimg, _patternSize, corners,
        cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);
        if(patternfound)
        {
            cv::cornerSubPix(grayimg, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::Type::COUNT + cv::TermCriteria::Type::EPS, 30, 0.1));
        } 
        else{
            std::cerr << "Pattern could not be found"<<std::endl;               
        } 
        cv::cvtColor(grayimg, grayimg, cv::COLOR_GRAY2BGR,0);     
        // draw detected corners 
        cv::drawChessboardCorners(grayimg, _patternSize, corners, patternfound);
        s.unlock();
}