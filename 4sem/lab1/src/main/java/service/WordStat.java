package service;

public class WordStat {
	private final String word;
	private int count;

	WordStat(String word) {
		this.word = word;
		this.count = 1;
	}

	void increase() { count++; }

	public String getWord() {
		return word;
	}

	public int getCount() {
		return count;
	}
}
