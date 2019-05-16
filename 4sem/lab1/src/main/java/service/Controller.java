package service;

import writers.OutputStreamWriterCSV;
import report.GeneratorReport;
import report.ReportRow;
import report.StatisticsReport;

import java.io.*;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Controller {
	private final TextStatistics textStatistics;

	public Controller(InputStream inputStream, OutputStream outputStream) {
		textStatistics = new TextStatistics();
		readData(inputStream);
		try {
			writeCSVReport(outputStream);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void readData(InputStream inputStream){
		Scanner scanner = new Scanner(inputStream);
		try {
			while (true) {
				String word = scanner.next();
				if (word != null && !word.isEmpty()) {
					textStatistics.addWord(word);
				}
			}
		} catch (NoSuchElementException e) {
			scanner.close();
		}
	}

	private void writeCSVReport(OutputStream outputStream) throws IOException {
		GeneratorReport generator = new GeneratorReport(textStatistics);

		StatisticsReport report = new StatisticsReport();

		for (WordStat wordStat : generator.getWordStats()) {
			report.addReportRow(generator.generateRow(wordStat));
		}

		OutputStreamWriterCSV writerCSV = new OutputStreamWriterCSV(outputStream);

		for (ReportRow row : report.getReportRows()){
			writerCSV.writeRow(row.getElements());
		}
		writerCSV.close();
	}
}
