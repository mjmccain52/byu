package cs235.sort;

public class SelectionSort extends SortImpl 
{	
	public void sort(Comparable[] a) 
	{
		reset();
		for (int i = 0; i < a.length-1; i++)
		{
		    int min = i;
		    for (int j = i+1; j < a.length; j++)
		    {
		    	if (compare(a[j],a[min]) < 0)
		    		min = j;
		    }

		    Comparable tmp = a[min];
		    a[min] = a[i];
		    a[i] = tmp;
		}
	}
}
