package cs235.boggle;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class BogglePlayerImpl implements BogglePlayer {

	private boolean boardSet;
	private boolean dictLoaded;
	private boolean found;
	private boolean[][] flagged;
	private int min;
	private int side;
	private List<Integer> path;
	private SortedSet<String> allWords;
	private String matchee;
	private String[] dictionary;
	private String[][] board;

	public BogglePlayerImpl() {
		allWords = new TreeSet<String>();
		boardSet = false;
		dictLoaded = false;
		path = new ArrayList<Integer>();
	}

	/**
	 * Loads the dictionary into a data structure for later use.
	 * 
	 * @param fileName
	 *            A string containing the dictionary to be opened.
	 * @throws IllegalArgumentException
	 *             if fileName is null
	 * @throws IllegalArgumentException
	 *             if fileName cannot be opened.
	 */
	public void loadDictionary(String fileName) {
		nullCheck(fileName);

		List<String> tempDict = new ArrayList<String>();
		try {
			Scanner fileScan = new Scanner(new File(fileName));
			while (fileScan.hasNext()) {
				tempDict.add(fileScan.nextLine());
			}
			// dictionary = (String[])tempDict.toArray();
			dictionary = new String[tempDict.size()];
			for (int i = 0; i < dictionary.length; i++)
				dictionary[i] = tempDict.get(i);

			dictLoaded = true;
		} catch (FileNotFoundException e) {
			throw new IllegalArgumentException("file cannot be opened");
		}
	}

	/**
	 * Stores the incoming array of Strings in a fashion that will make it
	 * convenient to find words.
	 * 
	 * @param letterArray
	 *            Each string in this array corresponds to a die on the Boggle
	 *            board.
	 * @throws IllegalArgumentException
	 *             if letterArray is null, or is not square
	 */
	public void setBoard(String[] letterArray) {
		nullCheck(letterArray);
		if (Math.sqrt((double) letterArray.length) % 1 != 0)
			throw new IllegalArgumentException("board not square");

		side = (int) Math.sqrt(letterArray.length);
		board = new String[side][side];
		flagged = new boolean[side][side];
		for (int i = 0; i < side; i++)
			for (int j = 0; j < side; j++)
				board[i][j] = letterArray[(i * side) + j].toLowerCase();
		boardSet = true;
	}

	/**
	 * Retrieves all the words in the Boggle board that appear in the
	 * dictionary.
	 * 
	 * @param minimumWordLength
	 *            The minimum allowed length for strings that will be stated as
	 *            being on the board.
	 * @return java.util.SortedSet which contains all the words found from the
	 *         boggle board that appear in the dictionary.
	 * @throws IllegalArgumentException
	 *             if minimumWordLength < 1
	 * @throws IllegalStateException
	 *             if loadDictionary has not been called.
	 */
	public SortedSet<String> getAllValidWords(int minimumWordLength) {
		dictCheck();
		if (minimumWordLength < 1)
			throw new IllegalArgumentException("minimum word length < 1");

		allWords = new TreeSet<String>();
		min = minimumWordLength;
		for (int i = 0; i < side; i++)
			for (int j = 0; j < side; j++) {
				resetFlags();
				traverse(i, j, "");
			}

		return allWords;
	}

	/**
	 * Recursive process of traversing all possible permutations given a
	 * starting cube
	 * 
	 * @param row
	 *            Row index
	 * @param col
	 *            Column index
	 * @param last
	 *            Pieced-together word candidate
	 */
	public void traverse(int row, int col, String last) {
		if (row < 0 || row >= side || col < 0 || col >= side
				|| flagged[row][col])
			return;
		String word = last.concat(board[row][col]);
		if (!isValidPrefix(word))
			return;
		if (isValidWord(word) && word.length() >= min)
			allWords.add(word);
		flagged[row][col] = true;
		traverse(row - 1, col, word); // North
		traverse(row - 1, col + 1, word); // NE
		traverse(row, col + 1, word); // East
		traverse(row + 1, col + 1, word); // SE
		traverse(row + 1, col, word); // South
		traverse(row + 1, col - 1, word); // SW
		traverse(row, col - 1, word); // West
		traverse(row - 1, col - 1, word); // NW
		flagged[row][col] = false;
	}

	/**
	 * Determines if the given word is in the dictionary.
	 * 
	 * @param wordToCheck
	 *            The word to validate
	 * @return true if wordToCheck appears in dictionary, false otherwise.
	 * @throws IllegalArgumentException
	 *             if wordToCheck is null.
	 * @throws IllegalStateException
	 *             if loadDictionary has not been called.
	 */
	public boolean isValidWord(String wordToCheck) {
		nullCheck(wordToCheck);
		dictCheck();

		return Arrays.binarySearch(dictionary, wordToCheck) >= 0;
	}

	/**
	 * Determines if there is at least one word in the dictionary with the given
	 * prefix.
	 * 
	 * @param prefixToCheck
	 *            The prefix to validate
	 * @return true if prefixToCheck appears in dictionary, false otherwise.
	 * @throws IllegalArgumentException
	 *             if prefixToCheck is null.
	 * @throws IllegalStateException
	 *             if loadDictionary has not been called.
	 */
	public boolean isValidPrefix(String prefixToCheck) {
		nullCheck(prefixToCheck);
		dictCheck();

		int insertionPoint;
		if (isValidWord(prefixToCheck))
			return true;
		else {
			insertionPoint = -(Arrays.binarySearch(dictionary, prefixToCheck) + 1);
			return dictionary[insertionPoint].startsWith(prefixToCheck);
		}
	}

	/**
	 * Determines if the given word is in on the Boggle board. If so, it returns
	 * the path that makes up the word.
	 * 
	 * @param wordToCheck
	 *            The word to validate
	 * @return java.util.List containing java.lang.Integer objects with the path
	 *         that makes up the word on the Boggle board. If word is not on the
	 *         boggle board, return null.
	 * @throws IllegalArgumentException
	 *             if wordToCheck is null.
	 * @throws IllegalStateException
	 *             if loadDictionary has not been called.
	 */
	public List<Integer> isOnBoard(String wordToCheck) {
		nullCheck(wordToCheck);
		dictCheck();
		boardCheck();

		found = false;
		matchee = wordToCheck;
		path.clear();

		for (int i = 0; i < side; i++)
			for (int j = 0; j < side; j++) {
				resetFlags();
				matchTraverse(i, j, "");
			}
		return path;
	}

	/**
	 * Recursive process of traversing all possible permutations given a
	 * starting cube to match a word candidate
	 * 
	 * @param row
	 *            Row index
	 * @param col
	 *            Column index
	 * @param last
	 *            Pieced-together word candidate
	 */
	public void matchTraverse(int row, int col, String last) {
		if (row < 0 || row >= side || col < 0 || col >= side) {
			return;
		}
		if (flagged[row][col]) {
			return;
		}
		if (found)
			return;

		String word = last.concat(board[row][col]);
		if (!isValidPrefix(word))
			return;
		if (matchee.equals(word)) {
			found = true;
		}

		path.add(new Integer(row * side + col));
		flagged[row][col] = true;
		matchTraverse(row - 1, col, word); // North
		matchTraverse(row - 1, col + 1, word); // NE
		matchTraverse(row, col + 1, word); // East
		matchTraverse(row + 1, col + 1, word); // SE
		matchTraverse(row + 1, col, word); // South
		matchTraverse(row + 1, col - 1, word); // SW
		matchTraverse(row, col - 1, word); // West
		matchTraverse(row - 1, col - 1, word); // NW
		flagged[row][col] = false;
		if (!found)
			path.remove((Integer) (row * side + col));
	}

	/**
	 * Sets the grid of boolean flags to false.
	 */
	public void resetFlags() {
		for (int i = 0; i < side; i++)
			for (int j = 0; j < side; j++)
				flagged[i][j] = false;
	}

	/**
	 * Checks parameter for null value
	 * 
	 * @param o
	 *            Object to be checked
	 * @throws IllegalArgumentException
	 *             if o is null
	 */
	public void nullCheck(Object o) {
		if (o == null)
			throw new IllegalArgumentException("null object");
	}

	/**
	 * Checks if dictionary has been loaded
	 * 
	 * @throws IllegalStateException
	 *             if there is no dictionary
	 */
	public void dictCheck() {
		if (!dictLoaded)
			throw new IllegalStateException("dictionary not loaded");
	}

	/**
	 * Checks if board has been set up
	 * 
	 * @throws IllegalStateException
	 *             if board has not been set.
	 */
	public void boardCheck() {
		if (!boardSet)
			throw new IllegalStateException("board not set");
	}

	/**
	 * An optional method that gives a user-defined boggle board to the GUI.
	 * 
	 * @return a String array in the same form as the input to setBoard().
	 */
	public String[] getCustomBoard() {
		return null;
	}
}
