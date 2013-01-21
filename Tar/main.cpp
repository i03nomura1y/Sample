
#include <libtar.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main(){
    TAR *t;
    if( tar_open(&t, (char*)"ball.tar", NULL, O_RDONLY, 0644, TAR_GNU) < 0 ){
        perror("tar_open");
        return 1;
    }

    /// すべて out_dir に展開
    //tar_extract_all(t, "out_dir");
    
    /// ファイル名一覧を表示
    int ret;
    while( (ret = th_read(t)) == 0 ){ // tar header read
        cout << th_get_pathname(t) << endl; // ファイル名を出力
        // skip or extract
        if(1){
            // 本体をスキップ
            tar_skip_regfile(t);
        }else{
            // file, dir, ... を保存
            tar_extract_file(t, (char*)"保存ファイル名");
        }
    }
    if( ret < 0 ){ perror("th_read"); }
    tar_close(t);

    return 0;
}
