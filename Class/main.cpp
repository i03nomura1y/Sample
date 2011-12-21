#include<iostream>
using namespace std;

#define PP(MSG) std::cout << ":" << __LINE__ << ": " << MSG << std::endl

class A{
public:
  explicit A(const std::string &n) : name(n){ PP("'" << name << "' constructor"); }
  ~A(){ PP("'" << name << "' de"); }
  A(const A &obj) : name(obj.name){ PP("'" << name << "' copy constructor"); }
  A &operator=(const A &obj){ PP("'" << name << "' = " << obj.name); name = obj.name; return *this; }
public:
  std::string name;
};

A global("global");

A getA(){ return global; }
A &getRef(){ return global; }

A getB(){ return A("inB"); }
//A &getRefB(){ return A("inB"); } // 一時変数 -> 参照は返せない

int main(){

#if 0
  A a  = getA();   // copy -> cost 1
  // A &b = getA();   // エラー
  A c  = getRef(); // copy -> cost 1
  A &d = getRef(); // 参照渡し -> cost 0
#endif

  A a  = getB();   // getB() 内でコンストラクタ1回 -> cost 1
  // A &b = getB();   // エラー
  A c  = getRefBc();   // getB() 内でコンストラクタ1回 -> cost 1
  A &d = getRefBc();   // エラー


  return 0;
}
