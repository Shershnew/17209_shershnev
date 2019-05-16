package report;

import service.TextStatistics;
import service.WordStat;
import java.util.TreeSet;

public class GeneratorReport {
	private final TreeSet<WordStat> treeSet;
    private int countWords;

	public GeneratorReport(TextStatistics textStatistics) {
		treeSet = new TreeSet<>((ws1, ws2) -> {
			if (ws1.getCount() == ws2.getCount()) {
				return ws1.getWord().compareTo(ws2.getWord());
			} else {
				return ws2.getCount() - ws1.getCount();
			}
		});

		for (WordStat wordStat : textStatistics) {
			treeSet.add(wordStat);
		}

		countWords = textStatistics.getCountWords();
	}

	public ReportRow generateRow(WordStat wordStat) {
		double frequency = (double)wordStat.getCount() / countWords;
		return new ReportRow(wordStat.getWord(), Integer.toString(wordStat.getCount()), String.format("%.4f",frequency));
	}

	public TreeSet<WordStat> getWordStats(){
		return treeSet;
	}

}
