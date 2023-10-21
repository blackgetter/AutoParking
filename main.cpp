#include "Common.h"
#include "WorldCoordinate.h"

const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";

int main()
{
	VideoCapture cap(0);//USB-1��
	if (!cap.isOpened())
	{
		cerr << "Camera open failed!" << endl;
		return -1;
	}

	Mat frame, frame_gray;
	WorldCoordinate _WorldCoordinate;

	while (true)
	{
		cap >> frame; //������ �޾ƿͼ� ��Ʈ������ ����
		if (frame.empty())
		{
			break;
		}

		// matching pairs
		vector<Point3f> objectPoints;	// 3d world coordinates
		vector<Point2f> imagePoints;	// 2d image coordinates

		// Insert the 3D coordinates into the vector
		objectPoints.push_back(Point3f(0.0, 10, 0.0));
		objectPoints.push_back(Point3f(0.0, 0.0, 0.0));
		objectPoints.push_back(Point3f(10, 0.0, 0.0));
		objectPoints.push_back(Point3f(10, 10, 0.0));

		// Detect edges in the pixel coordinates
		imagePoints = _WorldCoordinate.DetectVertex(frame, objectPoints, imagePoints);
		vector<Point2f> cameraPosition;
		cameraPosition = _WorldCoordinate.FindCameraPosition(frame, objectPoints, imagePoints);



		imshow(window_capture_name, frame);
		
		char key = (char)waitKey(10); //30ms���� ������ �޾ƿ� : waitKey
		if (key == 'q' || key == 27) //q �Ǵ� Escape Ű ������ Ż��
		{
			break;
		}
		
	}
	
	return 1;
}
