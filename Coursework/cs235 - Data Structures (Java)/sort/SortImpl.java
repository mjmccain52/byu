package cs235.sort;

public abstract class SortImpl implements Sort {

	private static long compares;
	public long getCompares() {
		return compares;
	}
	protected static void reset ()
	{
		compares = 0;
	}
	protected static int compare (Comparable a, Comparable b)
	{
		compares++;
		return a.compareTo(b);
	}

	public abstract void sort(Comparable[] a);

}
