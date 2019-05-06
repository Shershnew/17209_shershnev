package service;

import java.util.*;

public class  TextStatistics implements Iterable<WordStat> {
	private final Map<String, WordStat> map;
	private int wordCounter;

	TextStatistics() {
		map = new HashMap<>();
	}

	void addWord(String word) {
		wordCounter++;
		//или создает или возвращает
		WordStat wordStat = map.computeIfAbsent(word, str -> new WordStat(str));
		wordStat.increase();
	}

	int getCountWords() {
		return wordCounter;
	}

	@Override
	public Iterator<WordStat> iterator() {
		return map.values().iterator();
	}
}
