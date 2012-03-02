// pair の実験
//  http://homepage2.nifty.com/well/pair.html
#include <string>
#include <utility>
using namespace std;

int main() {
  // 変数型の typedef
  typedef pair<int, string>                 HEIGHTandPREFECTURE;
  typedef pair<string, HEIGHTandPREFECTURE> MOUNTNAME_ATTRIBUTE;
  // クラスメンバへのポインタの定義、ここは、料理で言えば仕込みの部分
  string              MOUNTNAME_ATTRIBUTE::*mpstrMountName  = &MOUNTNAME_ATTRIBUTE::first;
  HEIGHTandPREFECTURE MOUNTNAME_ATTRIBUTE::*mpAttribute     = &MOUNTNAME_ATTRIBUTE::second;
  int                 HEIGHTandPREFECTURE::*mpiHeight       = &HEIGHTandPREFECTURE::first;
  string              HEIGHTandPREFECTURE::*mpstrPrefecture = &HEIGHTandPREFECTURE::second;
  // オブジェクトの定義
  MOUNTNAME_ATTRIBUTE mountname_attribute;
  // メンバ変ポインタを使ってメンバにアクセスする。
  mountname_attribute.*mpstrMountName               = "富士山";
  mountname_attribute.*mpAttribute.*mpiHeight       = 3776;
  mountname_attribute.*mpAttribute.*mpstrPrefecture = "静岡";
}
