package report;

import java.util.ArrayList;
import java.util.Collection;

public class ReportRow {
	private final Collection<String> elements;

	ReportRow(String ... args) {
		elements = new ArrayList<>();
		for (String element : args) {
			elements.add(element);
		}
	}

	public Collection<String> getElements() {
		return elements;
	}
}
