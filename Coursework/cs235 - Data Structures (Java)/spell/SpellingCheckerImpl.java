package cs235.spell;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class SpellingCheckerImpl implements SpellingChecker
{
	private Dictionary masterDict;
	
	public SpellingCheckerImpl ()
	{
		masterDict = new Dictionary();
	}
	/**
     * Loads the dictionary contained in the specified file
     * 
     * @param filename The name of the dictionary file to be loaded
     * @return true If the file was successfully loaded, false
     *          if the file could not be loaded or was invalid
     * @throws IllegalArgumentException if filename is null
     */
    public boolean loadDictionary(String filename)
	{
		paramCheck(filename);
		
		return masterDict.addWords(filename);
	}
    
    /**
     * Check the document for misspelled words
     *
	 * @param filename The name of the document file to be checked
     * @return A list of misspelled words and
     *         the line numbers where they occur.
     * @throws IllegalArgumentException if filename is null
     */
    public String checkDocument(String filename)
	{
		paramCheck(filename);
		
		Index index = new Index();
		try 
		{
			Scanner docScan = new Scanner (new File (filename));

			/* What we do here is break the File into Lines, then make
			   separate Scanners for each line
			*/
			for (int i = 1; docScan.hasNextLine(); i++)
			{
				String line = docScan.nextLine();
				line = line.toLowerCase();
				Scanner lineScan = new Scanner (line);
				lineScan = lineScan.useDelimiter ("[^A-Za-z]+");
				while (lineScan.hasNext())
				{
					String temp = lineScan.next();
					if (!masterDict.contains(temp))
					{
						index.addToIndex (temp, i);
					}
				}
			}
		}
		catch (FileNotFoundException e)
		{
			System.out.println ("document file not found");
		}
		return index.toString();
	}
	
	/**
	* Check String parameters for null values
	*
	* @param filename The String variable to be checked
	* @throws IllegalArgumentException if filename is null
	*/
	public void paramCheck (String filename)
	{
		if (filename == null)
			throw new IllegalArgumentException ("null filename");
	}
}
