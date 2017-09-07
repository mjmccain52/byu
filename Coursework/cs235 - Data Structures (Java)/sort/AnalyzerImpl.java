package cs235.sort;

public class AnalyzerImpl implements Analyzer 
{
	private double errorSum;
	private double mean;
	private double sum;
	private int size;
	private double []errors;
	private double[] ratios;
	private int[] sizes;
	private long[] data;
	
	private final int TO_THE_THIRD = 3;
	private final int FUNCTIONS = 7;
	
	private final int CONST = 0;
	private final int LOG = 1;
	private final int LIN = 2;
	private final int NLOG = 3;
	private final int SQ = 4;
	private final int CUBE = 5;
	private final int EXP = 6;
	private int[] func;
	private final String[] names = {
			"O(1)",
			"O(log N)",
			"O(N)",
			"O(N log N)",
			"O(N^2)",
			"O(N^3)",
			"O(2^N)"};

	/**
	 * determines Big Oh functions
	 * @param sizes Array of different data sizes (100, 200, 400...) 
	 * @param data Array of runtime for each data size
	 */
	public void analyze(int[] sizes, long[] data) 
	{
		if (sizes == null || data == null)
			throw new IllegalArgumentException("null values");
		if (sizes.length != data.length)
			throw new IllegalArgumentException("unequal arrays");
		int[] funct ={CONST,LOG,LIN,NLOG,SQ,CUBE,EXP};
		func = funct;
		errors = new double[FUNCTIONS];
		size = sizes.length;
		ratios = new double[size];
		this.sizes = sizes;
		this.data = data;
		
		constant();
		log();
		linear();
		nLog();
		squared();
		cubed();
		exp();
		
		//Coincidentally enough, now it's time to sort those values.

		for (int i = 0; i < errors.length-1; i++)
		{
		    int min = i;
		    for (int j = i+1; j < errors.length; j++)
		    {
		    	if (errors[j] < errors[min])
		    		min = j;
		    }

		    double tmp = errors[min];
		    int t = func[min];
		    errors[min] = errors[i];
		    func[min] = func[i];
		    errors[i] = tmp;
		    func[i]= t;
		}		
	}

	/**
	 * Check for constant Big Oh.
	 */
	public void constant()
	{
		sum = 0;
		errorSum = 0;
		mean = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i];
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[CONST] = errorSum / size;
	}
	
	/**
	 * Check for logarithmic Big Oh.
	 */
	public void log()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / Math.log10(sizes[i]);
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[LOG] = errorSum / size;
	}
	
	/**
	 * Check for linear Big Oh.
	 */
	public void linear()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / (double)sizes[i];
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[LIN] = errorSum / size;
	}
	
	/**
	 * Check for N*log(N) Big Oh.
	 */
	public void nLog()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / (sizes[i] * Math.log10(sizes[i]));
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[NLOG] = errorSum / size;
	}
	
	/**
	 * Check for quadratic Big Oh.
	 */
	public void squared()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / Math.pow(sizes[i], 2);
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[SQ] = errorSum / size;
	}
	
	/**
	 * Check for cubed Big Oh.
	 */
	public void cubed()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / Math.pow(sizes[i], TO_THE_THIRD);
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[CUBE] = errorSum / size;
	}
	
	/**
	 * Check for exponential Big Oh.
	 */
	public void exp()
	{
		sum = 0;
		errorSum = 0;
		for (int i = 0; i <size; i++){
			ratios[i] = data[i] / Math.pow(2, sizes[i]);
			sum+=ratios[i];
		}
		mean = sum / size;
		for (int i = 0; i < size; i++ )
			errorSum += Math.abs(ratios[i] - mean) / mean;
		errors[EXP] = errorSum / size;
	}
	
	/**
	 * Returns Big Oh function in String form
	 * @return Big Oh function
	 */
	public String getBigOh() {
		return names[func[0]];
	}
	
	/**
	 * Returns average error for the correct function
	 * @return average error
	 */
	public double getError() {
		return errors[0];
	}

	public double[] getRatios() {
		
		return null;
	}

}
