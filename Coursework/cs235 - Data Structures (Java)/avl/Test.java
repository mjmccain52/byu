package cs235.avl;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		java.util.Set test = SetFactory.createSet();
		test.add("hi");
		test.add("4");
		test.add("z");
		System.out.println(test.contains("hi"));
		System.out.println(test.contains("0"));
		/*java.util.Iterator i = test.iterator();
		while (i.hasNext()){
			System.out.println(i.next());
		}
		Object []arr = test.toArray();
		for (int j = 0; j < arr.length; j++)
			System.out.println(arr[j]);
*/
	}

}
