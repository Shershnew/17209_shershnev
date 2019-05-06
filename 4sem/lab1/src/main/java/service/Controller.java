package service;

import writers.OutputStreamWriterCSV;
import report.GeneratorReport;
import report.ReportRow;
import report.StaticsReport;

import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Controller {
	private final TextStatistics textStatistics;

	public Controller() {
		textStatistics = new TextStatistics();
	}

	public void getData(Scanner scanner){
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

	public void writeCSVReport(OutputStreamWriterCSV writerCSV) throws IOException {
		GeneratorReport generator = new GeneratorReport(textStatistics);

		StaticsReport report = new StaticsReport();

		for (WordStat wordStat : generator) {
			ReportRow row = GeneratorReport.generateRow(wordStat, textStatistics.getCountWords());
			report.addReportRow(row);
		}

		for (ReportRow row : report) {
			writerCSV.writeRow(row);
		}

		writerCSV.flush();
	}
}
