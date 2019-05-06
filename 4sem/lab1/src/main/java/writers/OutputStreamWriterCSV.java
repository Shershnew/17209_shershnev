package writers;

import report.ReportRow;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class OutputStreamWriterCSV extends OutputStreamWriter {

	public OutputStreamWriterCSV(OutputStream outputStream){
		super(outputStream);
	}

	public void writeRow(ReportRow reportRow) throws IOException {
		for (String element : reportRow.getElements()) {
			this.write(element);
			this.write(',');
		}
		this.write('\n');
		this.flush();
	}
}
