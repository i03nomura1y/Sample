// created date : 2012/01/09 18:45:41
// last updated : 2012/01/09 22:00:48
// shared_ptr の実験

#include <iostream>
#include <tr1/memory>
using namespace std;

int alloc_cnt = 0;

class Obj;
//typedef Obj* Ptr;
typedef tr1::shared_ptr<Obj> Ptr;

class Obj{
public:
  Obj() { alloc_cnt++; cout << "+" << endl; }
  ~Obj(){ alloc_cnt--; cout << "-" << endl; }
  Ptr p;
};


int main(){
  {
	Ptr p1;
	p1 = Ptr(new Obj());
	cout << "p: " << (bool)p1 << endl;
	p1 = Ptr(); // デフォルトコンストラクタ: NULL
	cout << "p: " << (bool)p1 << endl; // NULL なら false
	p1 = Ptr(new Obj());
	
	Obj *a = new Obj();
	Ptr p2 = Ptr(a);
	//Ptr p3 = Ptr(a); // error

	Ptr p3 = Ptr(new Obj);
	p2->p = p3;
	p3->p = p2;
	// p2 と p3 がループしてる( p2 <-> p3 )ので、このままだと消えない。
	p2->p.reset(); // p2 <- p3 の状態にすると消える。

	// 自己参照 も消えない。
	p1->p = p1;
	
  }

  cout << alloc_cnt << endl;
  return 0;
}
