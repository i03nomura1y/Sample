import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.HashMap;

public class HttpRequest {
	
	private String[] request_line; // 1行目を \s+ で split したやつ
	private HashMap<String, String> header; // メッセージヘッダを : で split したやつ
	
	public HttpRequest(Socket sock){
		request_line = null;
		header = new HashMap<String, String>();

		try{
			InputStream in = sock.getInputStream();
			String str = readLine(in);
			if(str.length() == 0) return;
			request_line = str.split("\\s+");
			if(request_line.length != 3){
				System.out.println("Invalid Request Line: "+str);
				request_line = null;
			}
			
			// 空行までが Header
			while( (str=readLine(in)).length() != 0){
				int idx = str.indexOf(":");
				if(idx > 0)
					header.put(str.substring(0,idx), str.substring(idx+1));
			}
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	private String readLine(InputStream in){
		ByteArrayOutputStream out = new ByteArrayOutputStream(256);
		try{
			int c;
			while( (c=in.read()) > 0 && c != '\n'){
				if( c == '\r' ) continue;
				out.write(c);
			}
		}catch (Exception e) {
			e.printStackTrace();
		}
		return out.toString();
	}
	
	public String method(){ return (request_line==null)?"":request_line[0]; }
	public String uri(){    return (request_line==null)?"":request_line[1]; }
}
