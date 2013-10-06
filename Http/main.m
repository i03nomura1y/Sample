// created date : 2013/10/06 15:01:38
// last updated : 2013/10/06 16:03:08
// Http Client (ObjC)

// $ gcc main.m -o main -lobjc -lgnustep-base -I/usr/include/GNUstep -fconstant-string-class=NSConstantString

#import <Foundation/Foundation.h>

#define LOG_STR() [NSString stringWithFormat:@"%s(%d)", __FUNCTION__, __LINE__]
#define DBGP(...) NSLog(@"%@ %@", LOG_STR(), [NSString stringWithFormat:@""__VA_ARGS__])

void test(){
    NSString *url_ = @"http://example.com/";
    
    NSMutableURLRequest *request = [[[NSMutableURLRequest alloc] initWithURL:[NSURL URLWithString:url_]] autorelease];
    [request setHTTPMethod:@"GET"];

    /// ダウンロード
    NSData *data_;
    NSHTTPURLResponse *response = nil;
    NSError *error = nil;
    data_ = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    int statusCode = [response statusCode];
    
    // ステータスコードのチェック
    if( statusCode < 200 || 300<= statusCode ){
        DBGP(@"\nDownload Error : %@, status code %d,  error %@", url_, statusCode, error);
        return;
    }

    NSString *str= [[NSString alloc] initWithData:data_ encoding:NSUTF8StringEncoding];
    DBGP(@"response  %d: %d\n%@",statusCode, [data_ length], str);
    [str release];
}

int main(){
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    test();
    [pool release];

    return 0;
}
