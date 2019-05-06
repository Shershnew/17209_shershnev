package report;

import java.util.ArrayList;
import java.util.List;

public class ReportRow {
	private final List<String> elements;

	ReportRow(String ... args) {
		elements = new ArrayList<>();
		for (String element : args) {
			elements.add(element);
		}
	}

	public List<String> getElements() {
		return elements;
	}
}
