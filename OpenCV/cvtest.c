/// ソーベルフィルタ
// http://opencv.jp/sample/gradient_edge_corner.html
// gcc -o cvtest cvtest.c -I/usr/include/opencv  -lcvaux -lcxcore -lcv -lhighgui
// gcc -o cvtest cvtest.c `pkg-config --cflags --libs opencv`

#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#define SRC "Gray"
#define DST "Sobel"

int main (int argc, char **argv){
  IplImage *src_img, *dst_img, *tmp_img;

  // 画像の読み込み(グレースケールで読み込み)
  if (argc != 2 ||
	  (src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_GRAYSCALE)) == 0){
	fprintf(stderr,"Usage: $ %s img_file\n",argv[0]);
    return -1;
  }
  
  tmp_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_16S, 1);
  dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U,  1);

  // Sobelフィルタによる微分画像の作成
  cvSobel(src_img, tmp_img, 1, 0, 3);
  cvConvertScaleAbs(tmp_img, dst_img,1,0);

  // 画像の表示
  cvNamedWindow(SRC, CV_WINDOW_AUTOSIZE);
  cvShowImage(SRC, src_img);
  cvNamedWindow(DST, CV_WINDOW_AUTOSIZE);
  cvShowImage(DST, dst_img);

  // ユーザ入力待ち
  cvWaitKey(0);

  // 後始末
  cvDestroyWindow(SRC);
  cvDestroyWindow(DST);
  cvReleaseImage(&src_img);
  cvReleaseImage(&dst_img);
  cvReleaseImage(&tmp_img);

  return 0;
}
