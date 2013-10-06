// created date : 2013/10/06 15:01:38
// last updated : 2013/10/06 15:17:42
// HelloWorld in Objective-C (NSObject)

// $ sudo apt-get install gobjc  # ObjC用
// $ sudo apt-get install libgnustep-base-dev gnustep gnustep-devel  # NSObject
// $ gcc hello.m -o hello -lobjc -lgnustep-base -I/usr/include/GNUstep -fconstant-string-class=NSConstantString
// $ ./hello

#import <Foundation/Foundation.h>


@interface Cup: NSObject {
    int weight;
}
- setWeight:(int) w;
- (int)getWeight;
@end

@implementation Cup
- setWeight :(int) w{ weight = w; return self; }
- (int) getWeight{ return weight; }
@end

int main(){
  printf("Hello, objc World!!\n");
  
  Cup *cup = [[Cup alloc] init];
  [cup setWeight:10];
  printf("cup weight: %d\n", [cup getWeight]);
  [cup release];
  return 0;
}
