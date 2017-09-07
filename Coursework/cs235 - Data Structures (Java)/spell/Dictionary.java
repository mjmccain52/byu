package cs235.spell;

import java.util.Set;
import java.util.TreeSet;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Dictionary
{
	private Set<String> dictionary;
	
	/**
	* Instantiates Dictionary class
	*/
	public Dictionary ()
	{
		dictionary = new TreeSet<String>();
	}
	
	/**
	* Adds a .txt file containing words to the dictionary
	*
	* @param filename Name of the .txt file to add
	* @return true If the file was successfully loaded, false
    *          if the file could not be loaded
	*/
	public boolean addWords (String filename)
	{
		try
		{
			Scanner fileScan = new Scanner (new File (filename));
			
			while (fileScan.hasNext())
			{
				dictionary.add (fileScan.next());
			}
			return true;
		}
		catch (FileNotFoundException e)
		{
			System.out.println ("file not found");
			return false;
		}
	}
	
	/**
	* Scans the Dictionary object for an instance of the word given
	*
	* @param word To be compared with dictionary
	* @return true if dictionary contains the word,
	*		  false if not found
	*/
	public boolean contains (String word)
	{
		return dictionary.contains (word);
	}
	
}
