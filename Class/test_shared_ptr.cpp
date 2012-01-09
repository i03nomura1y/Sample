// created date : 2012/01/09 18:45:41
// last updated : 2012/01/09 19:15:54
// shared_ptr の実験

#include <iostream>
#include <tr1/memory>
using namespace std;

int alloc_cnt = 0;

class Obj{
public:
  Obj() { alloc_cnt++; }
  ~Obj(){ alloc_cnt--; }
};

//typedef Obj* Ptr;
typedef tr1::shared_ptr<Obj> Ptr;

class Container{
public:
  Container(){}
  void set(Obj* o){ obj = Ptr(o); }
private:
  Ptr obj;
};
int main(){
  {
	Container c;
	c.set(new Obj());
	c.set(new Obj());
  }

  cout << alloc_cnt << endl;
  return 0;
}
