package cs235.sort;

import java.util.Random;

public class SortAnalyzer 
{
	public static void main(String[] args) 
	{
		final String[] SORTS = {"INSERTION", "SELECTION", "MERGE", "QUICK"};
		final String[] ORDER = {"SORTED", "REVERSE", "RANDOM"};
		final int THREE = 3;
		final int FOUR = 4;
		final int[] SIZES = {100, 200, 400, 800, 1600};
		Sort[] sorts = {new InsertionSort(), new SelectionSort(),new MergeSort(), new QuickSort()};
		Integer[][][] allData = {new Integer[ORDER.length][SIZES[0]],
				new Integer [ORDER.length][SIZES[1]],
				new Integer [ORDER.length][SIZES[2]],
				new Integer [ORDER.length][SIZES[THREE]],
				new Integer [ORDER.length][SIZES[FOUR]]}; 
		Random r = new Random();
		
		/*
		 * creates a 3-dimensional array with
		 * 1st- different data sizes (5)
		 * 2nd- Order of the data (3)
		 * 3rd- data itself (100-1600)
		 */
		for (int i = 0; i < SIZES.length; i++)
		{
			for (int j = 0; j < SIZES[i]; j++)
				allData[i][0][j] = j * 2; //ordered
			for (int j = 0; j < SIZES[i]; j++)
				allData[i][1][j] = SIZES[FOUR] - j; //reversed
			for (int j = 0; j < SIZES[i]; j++)
				allData[i][2][j] = r.nextInt(SIZES[FOUR]); // random
		}

		Analyzer analyze = new AnalyzerImpl();
		for (int i = 0; i < SORTS.length; i ++)//all tests
		{
			for (int j = 0; j < ORDER.length; j++) //different orders
			{
				long[] data = new long[SIZES.length];
				System.out.println(SORTS[i] + " sort with " + ORDER[j] + " data");
				System.out.print("sizes: ");
				for (int k =0; k < SIZES.length; k++) //sizes
					System.out.print(SIZES[k] + " ");
				System.out.println();
				System.out.print("compares: ");
				for (int k = 0; k <SIZES.length; k++) //compares
				{
					sorts[i].sort(allData[k][j]);
					data[k] = sorts[i].getCompares();
					System.out.print(data[k] + " ");
				}
				analyze.analyze(SIZES, data);
				System.out.println();
				System.out.println(analyze.getBigOh()); //big oh analysis
				System.out.println();
			}

		}

	}

}
