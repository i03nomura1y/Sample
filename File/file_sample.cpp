// created date : 2011/10/30 21:54:32
// last updated : 2011/10/30 21:57:10
// ファイル/ディレクトリ操作のサンプル
// tmp/foo/bar と
// tmp/foo1/bar/buz を作成
// tmp/foo を削除

// $ g++ file_sample.cpp -o test
// $ ./test

#include <stdio.h> // remove
#include <string.h>
#include <string>

#include <sys/types.h> // stat
#include <sys/stat.h>  // stat
#include <time.h>   // time() for srandom
#include <stdlib.h> // random


#ifdef __GNUC__
#  include <dirent.h>    // opendir, readdir
#endif

#ifdef _WIN32
#  include <direct.h>    // _mkdir, _rmdir (windows only)
#  ifndef __GNUC__
// VC++
#    define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#    include <windows.h>
#  endif
#else
#  include <unistd.h>
#  define _rmdir(arg) rmdir(arg)
#  define _mkdir(arg) mkdir(arg, 0755)
#endif

// 親ディレクトリのパスを返す
std::string getParentPath(const std::string &path){
  int pos = path.find_last_of('/');
  if(pos > 0) return path.substr( 0, pos );
  if(pos == 0) return "/";
  return "";
}

bool mkdirs(const std::string &dir){
  if(dir.length() == 0) return true;  // パス長さ 0  -> return
  struct stat status;
  if( stat(dir.c_str(),&status)==0 && (status.st_mode & S_IFDIR) ) return true ; // exists -> return
  // 親ディレクトリ作成
  mkdirs( getParentPath(dir) );
  // ディレクトリ作成
  return (_mkdir(dir.c_str()) == 0 ); // 0 : 成功
}

// ファイル/ディレクトリ削除
bool removeFile(const std::string &path){
  int ret_val = 0;
  struct stat status;
  if(path.length() == 0 ||
	 stat(path.c_str(), &status) != 0 ) return false;  // パス長さ 0 or stat に失敗  -> return
  
  if( S_ISDIR(status.st_mode) ){
	// ディレクトリ -> 中身をぜんぶ消して _rmdir

#ifdef __GNUC__
	DIR *dp;
	if( (dp = opendir ( path.c_str() )) != NULL ){
	  struct dirent *ep;     
	  while( (ep = readdir(dp)) != NULL ){
		char *name = ep->d_name;
		if( strcmp(".", name)==0 || strcmp("..", name)==0 ) continue; // 自分と親は無視 (消さない)
		removeFile( path+"/"+name ); // recursive
	  }
	  closedir(dp);
	}
#else
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFileEx( ( path + "/*" ).c_str(),
								FindExInfoStandard, &fd,
								FindExSearchNameMatch, NULL, 0 );
	if( INVALID_HANDLE_VALUE != h ){
	  do {
		char *name = fd.cFileName;
		if( strcmp(".", name)==0 || strcmp("..", name)==0 ) continue; // 自分と親は無視
		removeFile( path+"/"+name ); // recursive
	  } while ( FindNextFile( h, &fd ) );
	  FindClose( h );
	}
#endif

	ret_val = _rmdir(path.c_str()); // 成功したら 0
	//DBGP("rmdir " << path);
  }else{
	// ファイル -> remove関数
	ret_val = remove(path.c_str()); // 成功したら 0
	//DBGP("remove " << path);
  }
  return (ret_val == 0); // 成功 : 0 -> true を返す
}


int main(){
  mkdirs("tmp/foo/bar");
  mkdirs("tmp/foo1/bar/baz");
  removeFile("tmp/foo");
  return 0;
}
