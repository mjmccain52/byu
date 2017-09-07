package cs235.spell;

import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

@SuppressWarnings("unchecked")
public class Index
{
	private Map<String, List> index;
	
	public Index ()
	{
		index = new TreeMap<String, List>();
	}
	
	/**
	* Adds a word and its line number to the index
	*
	* @param word Acts as Key in the Map
	* @param line Stored in a List to be the Value
	*/
	public void addToIndex (String word, int line)
	{
		//makes a new List for the Value
		if (!index.containsKey(word))
		{
			List<Integer> temp = new ArrayList<Integer>();
			temp.add (new Integer(line));
			index.put(word, temp);
		}
		//removes the Value List and adds the new Value, reinstating it
		else
		{
			List temp = (ArrayList)index.remove(word);
			temp.add(new Integer(line));
			index.put(word, temp);
		}
	}
	
	public String toString ()
	{
		String output = "";
		Set keySet = index.keySet();
		Iterator i = keySet.iterator();
		while (i.hasNext())
		{
			String key = (String)i.next();
			output += key + ": ";
			List values = (ArrayList)index.get(key);
			
			for (int j = 0; j < values.size(); j++)
			{
				output += values.get(j);
				if (!(j + 1 == values.size()))
					output += ", ";
			}
			output += "\n";
		}
		
		return output;
	}
}
