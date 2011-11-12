/// ヒストグラム
// http://opencv.jp/sample/gradient_edge_corner.html
// gcc -o cvtest cvtest.c -I/usr/local/include/opencv -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux
// gcc -o cvtest2 cvtest2.c `pkg-config --cflags --libs opencv`

#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main(int argc, char **argv){
  int i, j, bin_w;
  int hist_size = 256;
  int sch = 0, ch_width = 260;
  float max_value = 0;
  float range_0[] = { 0, 256 };
  float *ranges[] = { range_0 };
  IplImage *src_img = 0, *dst_img[4] = { 0, 0, 0, 0 }, *hist_img;
  CvHistogram *hist;

  // 画像ロード
  if(argc < 2 ||
     (src_img = cvLoadImage(argv[1], CV_LOAD_IMAGE_ANYCOLOR)) == 0){
	fprintf(stderr,"Usage: $ %s img_file\n",argv[0]);
    return -1;
  }

  // 入力画像のチャンネル数分の画像領域を確保
  sch = src_img->nChannels;
  for(i = 0; i < sch; i++) {
    dst_img[i] = cvCreateImage( cvSize(src_img->width, src_img->height),
								src_img->depth, 1);
  }

  // ヒストグラム構造体，ヒストグラム画像領域を確保
  hist     = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
  hist_img = cvCreateImage(cvSize(ch_width * sch, 200), 8, 1);

  // 入力画像がマルチチャンネルの場合，画像をチャンネル毎に分割
  if(sch == 1) cvCopy(src_img, dst_img[0], NULL);
  else         cvSplit(src_img, dst_img[0], dst_img[1], dst_img[2], dst_img[3]);

  // ヒストグラム画像をクリア
  cvSet(hist_img, cvScalarAll(255), 0);
  for(i = 0; i < sch; i++) {
    // ヒストグラムを計算して，スケーリング
    cvCalcHist(&dst_img[i], hist, 0, NULL);
    cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);
    cvScale(hist->bins, hist->bins,((double) hist_img->height) / max_value, 0);
    // ヒストグラムの描画
    bin_w = cvRound((double) ch_width / hist_size);
    for(j = 0; j < hist_size; j++)
      cvRectangle(hist_img,
				  cvPoint(j * bin_w +(i * ch_width), hist_img->height),
				  cvPoint((j + 1) * bin_w +(i * ch_width),
						  hist_img->height - cvRound(cvGetReal1D(hist->bins, j))),
				  cvScalarAll(0), -1, 8, 0);
  }

  // ヒストグラム画像を表示，キーが押されたときに終了
  cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
  cvShowImage("Image", src_img);
  cvNamedWindow("Histogram", CV_WINDOW_AUTOSIZE);
  cvShowImage("Histogram", hist_img);

  cvWaitKey(0);

  cvDestroyWindow("Image");
  cvDestroyWindow("Histogram");
  cvReleaseImage(&src_img);
  cvReleaseImage(&hist_img);
  for(i = 0; i < sch; i++) cvReleaseImage(&dst_img[i]);
  cvReleaseHist(&hist);

  return 0;
}
