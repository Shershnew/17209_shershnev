import service.Controller;

import java.io.*;

public class App {
	public static void main(String[] args) {
	    InputStream inputStream;
	    OutputStream outputStream;
		if (args.length > 0) {
            try {
                inputStream = new FileInputStream(new File(args[0]));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                return;
            }
        } else {
			System.err.println("no arguments");
			return;
		}


		if (args.length > 1) {
            try {
                outputStream = new FileOutputStream(args[1]);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                return;
            }
        } else {
		    outputStream = System.out;
        }

        Controller controller = new Controller(inputStream, outputStream);
    }
}

