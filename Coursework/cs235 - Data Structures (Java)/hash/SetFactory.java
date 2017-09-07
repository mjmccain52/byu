
package cs235.hash;

public class SetFactory {
    /**
     * Creates and returns an object that implements the java.util.Set interface
     *
     * @return A new object that implements the java.util.Set interface
     */
    public static java.util.Set createSet() {
    	return new HashSet();
    }
}

