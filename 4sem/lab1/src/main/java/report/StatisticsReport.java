package report;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StatisticsReport {
	private final List<ReportRow> reportRowList;

	public StatisticsReport() {
		reportRowList = new ArrayList<>();
		reportRowList.add(new ReportRow("Word", "Count" , "Frequency"));
	}

	public void addReportRow(ReportRow reportRow) {
		reportRowList.add(reportRow);
	}

	public List<ReportRow> getReportRows(){
		return reportRowList;
	}

}
