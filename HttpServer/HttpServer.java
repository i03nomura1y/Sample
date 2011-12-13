// created date : 2011/12/13 16:03:07
// last updated : 2011/12/13 16:06:58
// $ javac HttpServer.java -encoding utf-8
// $ java HttpServer
// ブラウザから http://localhost:8080/ にアクセスして確認
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer implements Runnable{
	private ServerSocket svsock;
	
	public HttpServer(int port) throws IOException{
		svsock = new ServerSocket();
		svsock.bind(new InetSocketAddress(port));
		svsock.setReuseAddress(true);
	}
	
	/**
	 * ServerSocket.accept() の結果を返す
	 * @return close() されていたら null
	 */
	private Socket accept(){
	    try { return svsock.accept(); } catch (Exception e) { }
	    return null;
	}
	
	/**
	 * サービス開始
	 */
	public void run(){
	    for (Socket sock = accept(); sock != null; sock = accept()) {
	    	try{
	    		response(new HttpRequest(sock), sock.getOutputStream());
	    		sock.close();
	    	}catch(IOException e){
	    		e.printStackTrace();
	    	}
	    }
	}
	
	/**
	 * サービス終了
	 */
	public void close(){
		try{ svsock.close(); }catch(Exception e){ e.printStackTrace(); }
	}
	
	/**
	 * Response を返す
	 * このメソッドをオーバーライドする
	 */
	protected void response(HttpRequest r, OutputStream os){
		response("<html><head></head><body>"
				+"Server is working successfully.<br>"
				+"Method : "+r.method()+"<br>"
				+"URI : "+r.uri()+"<br>"
				+"</body></html>", os);
	}

	/**
	 * レスポンスコード 200(OK)
	 * text/htlm として文字列を出力
	 */
	protected void response(String content, OutputStream os){
		PrintWriter prn = new PrintWriter(os);
		prn.print("HTTP/1.1 200 OK\r\n");
		prn.print("Connection: close\r\n");
		prn.print("Content-Length: "); prn.print(content.length()); prn.print("\r\n");
		prn.print("Content-Type: text/html\r\n");
		prn.print("\r\n");
		
		prn.print(content);
		
		prn.flush();
	}

	public static void main(String[] args){
		try{
			new Thread(new HttpServer(8080)).start();
			System.out.println("Server Start");
			System.out.println(" now you can access to http://localhost:8080/");
			System.out.println(" (Stop server to type ^C)");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("Server error: cannot start");
		}
	}
}
