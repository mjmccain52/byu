package cs235.javaskills;

import java.util.Scanner;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.List;
import java.util.ArrayList;

/*
 * Handles the Input/Output of PairSet files.
 * METHODS:
 * 		loadPointFile(String): PairSet
 * 		savePointFile(PairSet, String): boolean
 */

public class FileIO {
	/**
	* Loads a set of Pair objects stored in the specified file and returns them as a PairSet object.
	* 
	* @param fileName The name of the file to be loaded
	* @return a reference to a PairSet object, which has the points that were read in from the file.
	*      If the file cannot be opened or the contents of the file are invalid, null is returned
	* @throws IllegalArgumentException if fileName is null
	*/
	public static PairSet loadPointFile(String fileName) {
		if (fileName == null)
			throw new IllegalArgumentException();
		
		List<Pair> load = new ArrayList<Pair>();
		try
		{
			Scanner fileScan = new Scanner (new File(fileName));
			
			while (fileScan.hasNext())
			{
				Comparable first = fileScan.next();
				Comparable second = fileScan.next();		
				
				load.add (JavaSkillsFactory.createPair(first, second));				
			}
			Pair[] loadArray = new PairImpl[load.size()];
			for (int i = 0; i < load.size(); i++)
			{
				loadArray[i] = load.get(i);
			}
			
			return JavaSkillsFactory.createPairSet(loadArray);
		}
		
		catch (FileNotFoundException exception)
		{
			System.out.println("File not found.");
		}
		
		return null;
	}

	/**
	* Saves a PairSet to a file, in the form specified in the lab write-up.
	* 
	* @param points The PairSet object containing the Pair objects to be saved to fileName.
	* @param fileName the name of the file to be saved
	* @return true if the Pair objects were successfully written to the file,
	*         or false if an error occurred
	* @throws IllegalArgumentException if points and/or fileName is null
	*/
	public static boolean savePointFile(PairSet points, String fileName)
	{
		if (points == null || fileName == null)
			throw new IllegalArgumentException();

		boolean success = false;
		try
		{
			FileWriter fw = new FileWriter (fileName);
			BufferedWriter bw = new BufferedWriter (fw);
			PrintWriter outFile = new PrintWriter (bw);
			Pair[] pairSet = points.getAllPairs();
			
			for (int i = 0; i < pairSet.length; i++)
			{
				outFile.println(pairSet[i]);
			}			

			outFile.close();
			success = true;
		}
		catch (IOException exception)
		{
			success = false;
		}
        return success;
	}
}
