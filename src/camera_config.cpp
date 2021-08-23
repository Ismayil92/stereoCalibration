#include "camera_config.hpp"



GsCamera::GsCamera(int _sensor_id = CAM_LEFT, int _cap_w = 3264, int _cap_h = 2464, int _disp_w = 640, int _disp_h = 480, int _frm_rate = 21, int _flip_method = 2)
    :sensor_id{_sensor_id}, capture_width{_cap_w}, capture_height{_cap_h}, display_width{_disp_w}, display_height{_disp_h}, frame_rate{_frm_rate}, flip_method{_flip_method}
{
           cam_pipeline = "nvarguscamerasrc sensor-id=" + std::to_string(sensor_id)+ " ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(frame_rate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

GsCamera::~GsCamera()
{

}

GsStereoCamera::GsStereoCamera(int _cap_w, int _cap_h, int _disp_w, int _disp_h, int _frm_rate, int _flip_method)
    :cam_left{GsCamera(CAM_LEFT, _cap_w, _cap_h, _disp_w, _disp_h, _frm_rate, _flip_method)}, cam_right{GsCamera(CAM_RIGHT, _cap_w, _cap_h, _disp_w, _disp_h, _frm_rate, _flip_method)}
{
            cam_left_pipeline = cam_left.getGsPipeline();
            cam_right_pipeline = cam_right.getGsPipeline();
}   

GsStereoCamera::~GsStereoCamera()
{

}

