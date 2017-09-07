package cs235.javaskills;

import java.util.List;
import java.util.ArrayList;

/*
 * Implements the PairSet interface to store/access sets of Pair objects
 * METHODS:
 *		PairSetImpl()
 *		PairSetImpl(Pair[])
 *		add(Pair): boolean
 *		clear(): void
 *		contains(Pair): boolean
 *		getAllPairs(): Pair[]
 *		getItemsInInterval(Pair, Pair): Pair[]
 *		size(): int
 */

public class PairSetImpl implements PairSet {
	private static final int MAX_SIZE = 2000;
	private List<Pair> set; //A set might be better but I don't want
							//to mess with the iterators yet.
	//private int count;
	//private Pair[] setArray;
	/**
	 * Instantiates an empty set
	 */
	public PairSetImpl () {
		set = new ArrayList<Pair> ();
		//setArray = new Pair[MAX_SIZE]
		//count = 0;
	}
	
	/**
	 * Instantiates a list of Pair objects from an array.
	 * @param pairdata Array of pairs to be stored in set.
	 */
	public PairSetImpl (Pair [] pairdata) {
		set = new ArrayList<Pair> ();
		//setArray = new Pair[MAX_SIZE];
		//count = 0;
		for (int i = 0; i < pairdata.length; i++) {
			if (pairdata[i]==null || pairdata[i].getFirst() == null || pairdata[i].getSecond() == null)
				throw new IllegalArgumentException();
			set.add (pairdata [i]);
			//setArray[i] = pairdata[i];
			//count++;
		}
	}
	
	/**
	* Adds a Pair to the current set of Pair objects.
	* 
	* @param newpair The new pair to be added to the set.
	* @return true if the item was successfully added to the set,
	*         false if it was already in the set.
	* @throws IllegalArgumentException if newpair is null, or if one of it's members is null.
	*/
	public boolean add(Pair newpair) {
		if (newpair == null || newpair.getFirst() == null || newpair.getSecond() == null) {
			throw new IllegalArgumentException ("null arguments");
		}
		if (set.contains(newpair))
			return false;
		return set.add(newpair);
	}

	/**
	* Clears all points from this PairSet
	* 
	* @return void
	*/
	public void clear() {
		set.clear();
	}

	/**
	* Determines whether a given Pair object exists in the current set of Pairs.
	* 
	* @param checkpair The pair to be checked.
	* @return true if the item was in the set, false if not.
	* @throws IllegalArgumentException if checkpair is null, or if one of it's members is null.
	*/	
	public boolean contains(Pair checkpair) {
		if (checkpair == null || checkpair.getFirst() == null || checkpair.getSecond() == null) {
			throw new IllegalArgumentException ("null arguments");
		}
		return set.contains(checkpair);
	}

	/**
	* Returns the array containing the Pairs in the set.
	* The returned array's size must be the same as the set size.
	*
	* @return the array containing the pairs in the set.
	*/
	public Pair[] getAllPairs() {
		Pair [] allPairs = new Pair[set.size()];
		for (int i = 0; i < set.size(); i++)
			allPairs[i]=set.get(i);
		return allPairs;
	}

	/**
	* Generates an array of Pairs that fall within a 2-D area defined by two points
	*
	* @param lowerLeft Defines the lower-left corner of the rectangle and provides a lower bound.
	* @param upperRight Defines the upper-right corner of the rectangle and provides a upper bound.
	* @return an array of Pairs appearing in the defined interval.
	* @throws IllegalArgumentException if either pair is null, or their members are null.
	*/	
	public Pair[] getItemsInInterval(Pair lowerLeft, Pair upperRight) {
		intervalCheck(lowerLeft, upperRight);
		List<Pair> interval = new ArrayList<Pair>();
		for (int i = 0; i < set.size(); i++) {
			if (set.get(i).getFirst().compareTo(lowerLeft.getFirst()) >= 0 && 
				set.get(i).getFirst().compareTo(upperRight.getFirst()) <= 0 &&
				set.get(i).getSecond().compareTo(lowerLeft.getSecond()) >=0 && 
				set.get(i).getSecond().compareTo(upperRight.getSecond()) <= 0)
				
				interval.add(set.get(i));	
		}
		
		Pair[] array = new Pair[interval.size()];
		for (int i = 0; i < interval.size(); i++)
				array[i] = interval.get(i);
		return array;
	}
	
	public void intervalCheck (Pair lowerLeft, Pair upperRight) {
		if (lowerLeft == null || lowerLeft.getFirst() == null || lowerLeft.getSecond() == null) 
			throw new IllegalArgumentException ("null arguments");
		
		if (upperRight == null || upperRight.getFirst() == null || upperRight.getSecond() == null) 
			throw new IllegalArgumentException ("null arguments");
		
	}

	/**
	* Gets the number of pairs currently in the set.
	* 
	* @return the number of pairs in the set.
	*/
	public int size() {
		return set.size();
		//return count;
	}

}
