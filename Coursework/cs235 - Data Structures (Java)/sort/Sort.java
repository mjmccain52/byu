
package cs235.sort;

public interface Sort {

    /**
     * Sort the array into ascending order
     *
     * @throws IllegalArgumentException if the argument is null
     */
    void sort( Comparable [ ] a );

    /**
     * Returns the number of compares used in sort
     *
     * @return Returns the number of compares used in sort
     */
    long getCompares();

}

