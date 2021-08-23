#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <QtGui/QImage>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtGui/QPixmap>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QMessageBox>

#include <vector>
#include <type_traits>
#include <assert.h>
#include <cassert>
#include <opencv2/opencv.hpp>
#include "opencv2/calib3d.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class CalibrationWindow; }
QT_END_NAMESPACE

class CalibrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalibrationWindow(QWidget *parent = nullptr);
    ~CalibrationWindow();
    void addVector(const std::vector<cv::Point2f>& ,const std::vector<cv::Point2f>&);
    void stereoCalibrate();
   
    

private slots:
    void on_btnSave_clicked();
    void on_btnCalibrate_clicked();
    void on_btnAdd_clicked();
    

public:
    Ui::CalibrationWindow *ui;
    
public:
    QGraphicsPixmapItem pixmap_left;
    QGraphicsPixmapItem pixmap_right;
    std::vector<cv::Point2f> leftimg_corners;
    std::vector<cv::Point2f> rightimg_corners;
    std::vector<cv::Point3f> objectPointsPerImg; 
    std::vector<std::vector<cv::Point2f>> totalLeftImagePoints;
    std::vector<std::vector<cv::Point2f>> totalRightImagePoints;
    std::vector<std::vector<cv::Point3f>> totalObjectPoints; 
    cv::Size patternSize = cv::Size(9,6); //interior number of corners  width, height
    float squareSize{17}; //mm
     // 0 left , 1 right
    cv::Mat intrinsics[2]; 
    cv::Mat distCoeff[2];
    double repr_error;
    cv::Mat R, t, E, F;
    bool patternFound[2];
    int num_imgs = 0;
    
};
#endif // CALIBRATIONWINDOW_H
