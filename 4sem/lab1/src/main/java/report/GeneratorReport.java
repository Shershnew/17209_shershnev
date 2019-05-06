package report;

import service.TextStatistics;
import service.WordStat;

import java.util.Iterator;
import java.util.TreeSet;

public class GeneratorReport implements Iterable<WordStat> {
	private final TreeSet<WordStat> treeSet;

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
	}

	public static ReportRow generateRow(WordStat wordStat, int count) {
		double frequency = (double)wordStat.getCount() / count;
		if (!Double.isFinite(frequency)) {
			frequency = -0.0;
		}

		return new ReportRow(wordStat.getWord(),Integer.toString(wordStat.getCount()),String.format("%.4f",frequency));
	}

	@Override
	public Iterator<WordStat> iterator() {
		return treeSet.iterator();
	}
}
