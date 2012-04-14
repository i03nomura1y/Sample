// created date : 2012/04/14 12:43:00
// last updated : 2012/04/14 12:50:54
// enum と map挿入 の実験
// -Wl,--enable-auto-import

#include <iostream>
#include <map>
using namespace std;

enum Pref{
  Yamaguchi = 0,
  Fukuoka,
  Tokyo,
  Hokkaido
};


void test();

int main(){
  test();
  test();
  return 0;
}


void test(){
  static bool init_flg = false;
  static std::map<int ,std::string> m;
  cout << " -- test()" << endl;
  if(!init_flg){ // マップ初期化
#define ADD( NAME ) m.insert( std::pair<int,std::string>(NAME, #NAME) )
	cout << "init enum-map" << endl;
	init_flg = true;
	ADD( Yamaguchi );
	ADD( Fukuoka );
	ADD( Tokyo );
	ADD( Hokkaido );
	// ADD に渡しているのは enum
	// (0 "Yamaguchi") (1 "Fukuoka) のように、enum と 文字列がペアになって入る
#undef ADD
  }

  cout << m.find(Yamaguchi)->second << endl;
  cout << m[Tokyo] << endl;

}
