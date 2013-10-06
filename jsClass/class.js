// クラス定義

// namespace
var myns = {};

// abstract class BaseObject
myns.BaseObject = function(){
    // メンバ定義
    this.id = "";
    this.x = 0;
    this.y = 0;
};
myns.BaseObject.prototype = {
    // 関数定義
    setXY : function(x, y){ this.x = x; this.y = y; },
    isLoaded : function(){ return true; },
    // abstract な関数
    dump : 0
};
// クラスプロパティ
myns.BaseObject.value = 2;

/// class Text extends BaseObject
myns.Text = function(str,x,y){
    // arguments でデフォルト引数
    switch( arguments.length ){
    case 0: str    = '';			/* fall through */
    case 1: x      = 0;			/* fall through */
    case 2: y      = 0;			/* fall through */
    }
    this.string = str;
    this.setXY(x,y);
};
// 継承
myns.Text.prototype = new myns.BaseObject();
// オーバーライド
myns.Text.prototype.dump = function(){
    return "Text '"+this.string+"' "+this.x+","+this.y;
};


/// class Image extends BaseObject
myns.Image = function(src,x,y){
    this.img = new Image();
    this.img.src = src;
    this.setXY(x,y);
};
myns.Image.prototype = new myns.BaseObject();
myns.Image.prototype.dump = function(){
    return "Image '"+this.img.src+"' "+this.x+","+this.y;
};
myns.Image.prototype.isLoaded = function(){
    return this.img.complete;
};
