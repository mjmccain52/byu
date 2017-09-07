package cs235.javaskills;

public class JavaSkillsFactory {
	/**
	* Creates, initializes, and returns a new object that implements the PairSet interface
	*    from the given Pair objects.
	* 
	* @param pairdata An array of Pair objects that will be added into the PairSet object.
	* @return a reference to the new PairSet object
	* @throws IllegalArgumentException if any pair in pairdata or it's members is invalid. 
	*/ 
	public static PairSet createPairSet(Pair[] pairdata) {
		if (pairdata == null) {
			throw new IllegalArgumentException ();
		}
		return new PairSetImpl(pairdata);
	}
	
	/**
	* Creates new object that implements the PairSet interface.
	* 
	* @return a reference to the object that implements the PairSet interface.
	*/ 
	public static PairSet createEmptyPairSet() {
		return new PairSetImpl ();
	}
	
	/**
	* Creates a new instance of the class that implements the Pair interface.
	* @param first Value to be placed as the 1st element of the new Pair object.
	* @param second Value be placed as the 2nd element of the new Pair object. 
	* @return a new instance of the class that implements the Pair interface.
	* @throws IllegalArgumentException if either first or second are null.
	*/	
	public static Pair createPair(Comparable first, Comparable second) {
		if (first == null || second == null)
				throw new IllegalArgumentException();
		return new PairImpl (first, second);
	}

}
