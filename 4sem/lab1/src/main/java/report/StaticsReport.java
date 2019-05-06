package report;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StaticsReport implements Iterable<ReportRow> {
	private final List<ReportRow> reportRowList;

	public StaticsReport() {
		reportRowList = new ArrayList<>();
		reportRowList.add(new ReportRow("Word", "Count" , "Frequency"));
	}

	public void addReportRow(ReportRow reportRow) {
		reportRowList.add(reportRow);
	}

	@Override
	public Iterator<ReportRow> iterator() {
		return reportRowList.iterator();
	}
}
