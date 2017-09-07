package cs235.javaskills;

/*
 * Implements the Pair interface to store and access two comparable values.
 * METHODS:
 *		PairImpl(Comparable, Comparable)
 *		getFirst(): Comparable
 *		getSecond(): Comparable
 *		equals (Object): boolean
 *		toString () : String 
 */
public class PairImpl implements Pair {

	private Comparable first;
	private Comparable second;
	
	/** 
	 * Initializes the PairImpl class.
	 * 
	 * @param first value of the Comparable class.
	 * @param second value of the Comparable class.
	 */
	public PairImpl (Comparable first, Comparable second) {
		this.first = first;
		this.second = second;
	}
	
	/**
	* Retrieves the first Comparable contained in the class that implements Pair
	* 
	* @return the first Comparable.
	*/
	public Comparable getFirst() {
		return first;
	}

	/**
	* Retrieves the second Comparable contained in the class that implements Pair
	* 
	* @return the second Comparable.
	*/
	public Comparable getSecond() {
		return second;
	}
	
	/** 
	 * Compares two Pair object for value equality.
	 * 
	 * @param obj is the Pair object to be compared with the current object. (Must cast)
	 * @return true if the Pair objects are equal.
	 */
	public boolean equals(Object obj) {
		if (obj instanceof Pair) {
			Pair temp = (Pair)obj; 
			return first.equals(temp.getFirst()) && second.equals(temp.getSecond());
		}
		else
			return false;
	}
	
	/**
	 * Returns a String representation of the Pair.
	 * 
	 * @return Strings of the two values in Pair.
	 */
	public String toString () {
		return getFirst() + " " +getSecond();
	}

}
