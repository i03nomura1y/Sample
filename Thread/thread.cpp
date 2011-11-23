// created date : 2008/11/14
// last updated : 2011/11/23 20:47:21
// http://kiiroitori2012.seesaa.net/category/1250221-1.html
// マルチスレッドのサンプル
// gcc -o thread thread.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//mutex生成
pthread_mutex_t mutex;

void *func(void *arg);

int main(){
  pthread_t thread1, thread2,thread3;
  int arg1=1,arg2=2,arg3=3;
  void *ret;
  //mutexの初期化
  pthread_mutex_init(&mutex,NULL);
  // スレッド生成 引数を渡す。
  // (pthread_t *,pthread_attr_t *,関数ポインタ,void *arg)
  pthread_create(&thread1,NULL,func,&arg1);
  pthread_create(&thread2,NULL,func,&arg2);
  pthread_create(&thread3,NULL,func,&arg3);

  //メインスレッドの処理

  // threadの終了を待つ
  // 戻り値を受け取る。   (pthread_t , void **ret)
  pthread_join(thread1,&ret);
  printf("thread1 : %d\n",*(int *)ret);
  pthread_join(thread3,&ret);
  printf("thread3 : %d\n",*(int *)ret);
  pthread_join(thread2,&ret);
  printf("thread2 : %d\n",*(int *)ret);

  return 0;
}

void *func(void *arg){
  static int ret[]={0,1,2,3,4,5};
  int arg_i=0;
  //新しく作成した子スレッドの処理
  if(arg != NULL){
	arg_i = *(int *)arg;
  }
  if(arg_i > 5 || arg_i <0){
	arg_i = 5;
  }
  //mutexのロック
  //pthread_mutex_lock(&mutex);

  //ここに排他処理を記述
  printf("処理開始 func(%d)\n",arg_i);
  for(int i=0;i<10;i++){
	printf("%d - %d\n",arg_i,i);
	for(int j=0;j<arg_i;j++){
	  usleep(100000);
	}
  }
  printf("処理終了 func(%d)\n",arg_i);
  //mutexのアンロック
  //pthread_mutex_unlock(&mutex);
  // スレッド終了
  // 戻り値を渡す。  (void *retval)
  pthread_exit(&ret[arg_i]);
}
