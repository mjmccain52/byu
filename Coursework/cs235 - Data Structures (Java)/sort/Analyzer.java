
package cs235.sort;

public interface Analyzer {

    /**
     * Analyze the data to determine the BigOh function
     *
     * @throws IllegalArgumentException if either argument is null
     */
    void analyze(int[] sizes, long[] data);

    /**
     * Returns the array of ratios computed by analyze
     *
     * @return Returns the array of ratios computed by analyze
     */
    double[] getRatios();

    /**
     * Returns an error indicating the accuracy of the BigOh function
     *
     * @return Returns an error indicating the accuracy of the BigOh function
     */
    double getError();

    /**
     * Returns the BigOh function determined by analyze
     *
     * @return Returns the BigOh function determined by analyze
     */
    String getBigOh();
}

