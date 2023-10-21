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

	Mat frame;
	WorldCoordinate* _WorldCoordinate = new WorldCoordinate;

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
		imagePoints = _WorldCoordinate->DetectVertex(frame, objectPoints, imagePoints);
		// ���⿡�� �̹��� �ȼ���ǥ �� ����ִ��� Ȯ��
		if (imagePoints.empty())
		{
			imshow(window_capture_name, frame);
		}
		else
		{
			vector<Point2f> calDist;
			calDist = _WorldCoordinate->CalculateDistance(frame, objectPoints, imagePoints);
			imshow(window_capture_name, frame);
		}
	
		char key = (char)waitKey(30); //30ms���� ������ �޾ƿ� : waitKey
		if (key == 'q' || key == 27) //q �Ǵ� Escape Ű ������ Ż��
		{
			break;
		}
		
	}
	
	delete _WorldCoordinate;
	return 1;
}
