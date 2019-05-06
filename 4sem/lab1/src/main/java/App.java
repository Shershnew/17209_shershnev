import service.Controller;
import writers.OutputStreamWriterCSV;

import java.io.*;
import java.util.Scanner;

public class App {
	public static void main(String[] args) {
		Scanner scanner;
		if (args.length > 0) {
			try {
				scanner = new Scanner(new FileReader(new File(args[0])));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
				return;
			}
		} else {
			System.err.println("no arguments");
			return;
		}

		Controller controller = new Controller();
		controller.getData(scanner);

		OutputStreamWriterCSV CSVwriter = null;
		if (args.length > 1) {
			try {
				CSVwriter = new OutputStreamWriterCSV(new FileOutputStream(args[1]));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
		if (CSVwriter == null) {
			CSVwriter = new OutputStreamWriterCSV(System.out);
		}

		try {
			controller.writeCSVReport(CSVwriter);
			CSVwriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

