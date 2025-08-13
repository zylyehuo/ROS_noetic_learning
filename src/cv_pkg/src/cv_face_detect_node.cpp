#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;

// 主要是基于亮度特征来进行检测
// 所以输入需要是黑白图像
static CascadeClassifier face_cascade;  // 分类器

static Mat frame_gray;  // 存储黑白图像

static vector<Rect> faces;  // 存放人脸检测结果，检测了多少张人脸
static vector<cv::Rect>::const_iterator face_iter;

void CallbackRGB(const sensor_msgs::Image msg)
{
    // 从 sensor_msgs::Image 转换为 cv::Mat，保存在 imgOriginal
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    Mat imgOriginal = cv_ptr->image;

    // 转换成黑白图像
    cvtColor( imgOriginal, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

    // 检测人脸
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 9, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    // 在彩色原图中标注人脸位置
    if(faces.size() > 0)
    {
        vector<cv::Rect>::const_iterator i;
        for (face_iter = faces.begin(); face_iter != faces.end(); ++face_iter) 
        {
            cv::rectangle(
                imgOriginal,
                cv::Point(face_iter->x , face_iter->y),
                cv::Point(face_iter->x + face_iter->width, face_iter->y + face_iter->height),
                CV_RGB(255, 0 , 255),
                2);
        }
    }
    else
    {
        ROS_ERROR("未检测到人脸...");
        return;
    }

    imshow("faces", imgOriginal);
    waitKey(1);
}


int main(int argc, char **argv)
{
    cv::namedWindow("faces");
    ros::init(argc, argv, "cv_face_detect_node");

    ROS_INFO("demo_cv_face_detect");

    // 读取人脸特征文件，特征模板
    string strLoadFile;
    char const* home = getenv("HOME");
    strLoadFile = home;
    strLoadFile += "/ros_test_ws";
    strLoadFile += "/src/cv_pkg/config/haarcascade_frontalface_alt.xml";

    bool res = face_cascade.load(strLoadFile);
	if (res == false)
	{
		ROS_ERROR("fail to load haarcascade_frontalface_alt.xml");
        return 0;
	}

    ros::NodeHandle nh;
    ros::Subscriber rgb_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 1 , CallbackRGB);

    ros::spin();
    return 0;
}