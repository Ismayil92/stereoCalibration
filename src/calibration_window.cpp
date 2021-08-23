#include "calibration_window.hpp"
#include "ui_calibration.hpp"

CalibrationWindow::CalibrationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalibrationWindow)
{
    ui->setupUi(this);
    ui->leftFrame->setScene(new QGraphicsScene(this));
    ui->leftFrame->scene()->addItem(&pixmap_left);
    ui->leftFrame->fitInView(&pixmap_left, Qt::IgnoreAspectRatio);
    ui->rightFrame->setScene(new QGraphicsScene(this));
    ui->rightFrame->scene()->addItem(&pixmap_right);
    ui->rightFrame->fitInView(&pixmap_right, Qt::IgnoreAspectRatio);
    //connect(ui->btnAdd, SIGNAL(clicked(bool)),this, SLOT(on_btnAdd_clicked()));
    //connect(ui->btnCalibrate, SIGNAL(clicked()), this, SLOT(on_btnCalibrate_clicked())); 
    

}

CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}


void CalibrationWindow::on_btnSave_clicked()
{
    cv::FileStorage fs("../config/intrinsic_parameters.yml", cv::FileStorage::WRITE);
    if(fs.isOpened())
    {
        fs<<"Left Camera Matrix"<<intrinsics[0]<<"Left Distorting Coeffs"<<distCoeff[0];
        fs<<"Right Camera Matrix"<<intrinsics[1]<<"Right Distorting Coeffs"<<distCoeff[1];
        fs.release();
    }
    else{
        std::cerr<<"Camera intrinsics could not be saved. \n";
    }

    fs.open("../config/extrinsic_parameters.yml", cv::FileStorage::WRITE);
    if(fs.isOpened())
    {
        fs<<"R:"<<R;
        fs<<"t:"<<t;
        fs<<"E:"<<E;
        fs<<"F:"<<F;
        fs.release();
    }
    else
    {
        std::cerr<<"Camera extrinsics could not be saved. \n";
    }    
}

void CalibrationWindow::on_btnCalibrate_clicked()
{
    stereoCalibrate();
    
    // to show error metric in textBox
    QString valueAsString = QString::number(repr_error);
    ui->textErrorMetrics->setText(valueAsString);
}

void CalibrationWindow::on_btnAdd_clicked()
{
    
    if(patternFound[0] == true && patternFound[1] == true)
    {
        addVector(leftimg_corners, rightimg_corners);
        ui->lblNumber->setText(QString::number(++num_imgs));
    }
    else{
        std::cerr<<"Chessboard not found on the one or both of the images"<<std::endl;
    }
    
}


void CalibrationWindow::addVector(const std::vector<cv::Point2f>& input_left_vector ,const std::vector<cv::Point2f>& input_right_vector)
{
    totalLeftImagePoints.push_back(input_left_vector);
    totalRightImagePoints.push_back(input_right_vector);

    for(int j = 0; j < patternSize.height; j++ ) //height 6
        for(int  k = 0; k < patternSize.width; k++ ) //width 9
            objectPointsPerImg.push_back(cv::Point3f(k*squareSize, j*squareSize, 0));

    std::cout<<"per image object Points"<<objectPointsPerImg.size()<<std::endl;
    totalObjectPoints.push_back(objectPointsPerImg);

    objectPointsPerImg.clear();   
    
    std::cout<<totalLeftImagePoints.size()<<std::endl;
}

void CalibrationWindow::stereoCalibrate()
{
    assert(totalObjectPoints.size() == totalLeftImagePoints.size() && "Size of totalObjectPoints vector and totalLeftImagePoints vector are not equal");
    assert(totalObjectPoints.size() == totalRightImagePoints.size() && "Size of totalObjectPoints vector and totalRightImagePoints vector are not equal");
    assert(totalLeftImagePoints.size() == totalRightImagePoints.size() && "Size of totalLeftImagePoints vector and totalRightImagePoints vector are not equal");
    // estimate initial camera matrix        
    intrinsics[0] = cv::initCameraMatrix2D(totalObjectPoints, totalLeftImagePoints, cv::Size(640,480), 0);
    intrinsics[1] = cv::initCameraMatrix2D(totalObjectPoints, totalRightImagePoints, cv::Size(640,480), 0);      

    repr_error = cv::stereoCalibrate(totalObjectPoints, totalLeftImagePoints, totalRightImagePoints,
                                        intrinsics[0], distCoeff[0],
                                        intrinsics[1], distCoeff[1],
                                        cv::Size(640,480),
                                        R, t, E, F, 
                                        cv::CALIB_USE_INTRINSIC_GUESS | cv::CALIB_SAME_FOCAL_LENGTH | cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_ASPECT_RATIO,
                                        cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 100,1e-5)
                                        );
}
