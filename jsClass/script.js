// クラスを定義したファイルを include
document.write('<script type=\"text/javascript\" src=\"class.js\"></script>');

function test(){
    var arr = [];
    // オブジェクト生成
    arr.push( new myns.Text("Hello, world!!",0,0) );
    arr.push( new myns.Text("Taro, world!!",0,20) );
    arr.push( new myns.Image("image.jpg",20,40)   );
    
    var txt = "";
    for(var i=0;i<arr.length; i++){
        txt += arr[i].dump()+"\n";
    }
    document.getElementById("cout").innerText = txt;
}
