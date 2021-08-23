#ifndef CAMERA_CONFIG_HPP
#define CAMERA_CONFIG_HPP

#include <tuple>
#include <string>

namespace constants{
    const std::string CONFIG_FILE_PATH = "../config/cam_config.json";
    const int CONF_ID = 2;
}

enum FLIP_METHODS{
    NONE,                   //(0): none             - Identity (no rotation)
    COUNTER_CLOCKWISE,      //(1): counterclockwise - Rotate counter-clockwise 90 degrees
    ROTATE_180,             //(2): rotate-180       - Rotate 180 degrees
    CLOCKWISE,              //(3): clockwise        - Rotate clockwise 90 degrees
    HORIZONTAL_FLIP,        //(4): horizontal-flip  - Flip horizontally
    UPPER_RIGHT_DIAGONAL,   //(5): upper-right-diagonal - Flip across upper right/lower left diagonal
    VERTICAL_FLIP,          //(6): vertical-flip    - Flip vertically
    UPPER_LEFT_DIAGONAL     //(7): upper-left-diagonal - Flip across upper left/low               
};
// LEFT OR RIGHT CAMERA
enum CAMERA{
            CAM_LEFT,
            CAM_RIGHT
};
// Struct for parsing from json configuration file 
struct camConfigJson {
    CAMERA sensor_id;
    int capture_width;
    int capture_height;
    int display_width;
    int display_height;
    int frame_rate;
    FLIP_METHODS flip_method;
};


class GsCamera {
    protected:
        std::string cam_pipeline;
        int sensor_id;
        int capture_width;
        int capture_height;
        int display_width;
        int display_height;
        int frame_rate;
        int flip_method;
    public: 
        explicit GsCamera(int, int , int, int , int , int , int );           
        ~GsCamera();

        // returning camera pipeline path
        std::string getGsPipeline() const {return cam_pipeline;}        
};

class GsStereoCamera{

    private:
        GsCamera cam_left;
        GsCamera cam_right; 
        std::string cam_left_pipeline;
        std::string cam_right_pipeline;   
    public:
        explicit GsStereoCamera(int, int , int, int, int, int);       
        ~GsStereoCamera();

        // returning both cameras pipeline path in a tuple
        std::tuple<std::string, std::string> getStereoGsPipeline() const {
            return {cam_left_pipeline, cam_right_pipeline};
        }
        
        GsCamera getLeftCamera() const {
            return cam_left;
        }
        GsCamera getRightCamera() const {
            return cam_right;
        }
};

#endif