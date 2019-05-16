package writers;

import report.ReportRow;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.Collection;

public class OutputStreamWriterCSV extends OutputStreamWriter {

	public OutputStreamWriterCSV(OutputStream outputStream){
		super(outputStream);
	}

	public void writeRow(Collection<String> elements) throws IOException {
		for (String element : elements) {
			this.write(element);
			this.write(',');
		}
		this.write('\n');
		this.flush();
	}
}
