// Webカメラから入力
// g++ -o camera camera.cpp `pkg-config --cflags --libs opencv`
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;

int main (int argc, char **argv){
  CvCapture* capture = cvCreateCameraCapture(-1);
  if(capture == NULL){
	cerr << "Web camera not found." << endl;
	return 1;
  }
  
  cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
  IplImage *img;
  do{
	img = cvQueryFrame(capture);
	if( img->origin != IPL_ORIGIN_TL ){
	  cvFlip( img,img );
	  img->origin = IPL_ORIGIN_TL;
	}
	cvShowImage("input",img);
  }while((cvWaitKey(10)&0xff)!=27); // ESCで終了
  cvDestroyWindow("input");
}
