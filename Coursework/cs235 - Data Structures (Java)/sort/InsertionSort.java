package cs235.sort;

public class InsertionSort extends SortImpl 
{

	public void sort(Comparable[] a) 
	{

		reset();
		for( int p = 1; p < a.length; p++ )
        {
            Comparable tmp = a[ p ];
            int j = p;

            for( ; j > 0 && compare (tmp,a[ j - 1 ] ) < 0; j-- )
                a[ j ] = a[ j - 1 ];
         
            a[ j ] = tmp;
        }

	}

}
