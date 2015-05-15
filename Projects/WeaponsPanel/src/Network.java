import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Network {
	private Socket sock;
	private String ip = "192.168.0.108";
	private int port = 5003;
	private OutputStreamWriter output;
	private InputStreamReader input;
	
	public Network(){
		try {
			sock = new Socket(ip, port);
			 output =
					new OutputStreamWriter(sock.getOutputStream(), "UTF-8");
			 input =
					new InputStreamReader(sock.getInputStream(), "UTF-8");
			
			output.flush();
			output.write("WEP@");
			output.flush();
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
	}
	public void Sendout(String s){
		try {
			output.flush();
			output.write(s + "@");
			output.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public String Readin(){
		char[] buffer = new char[8048];
		try {
			output.flush();
			input.read(buffer);
			return String.valueOf(buffer);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return "you fucked up";
		}
	}
	public void close(){
		try {
			sock.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
