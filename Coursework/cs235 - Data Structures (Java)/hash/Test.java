package cs235.hash;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		HashSet test = new HashSet();
		test.add("Hello");
		test.add("My");
		test.add("Name");
		test.add("Is");
		test.add("Is");
		test.add("Michael");
		test.remove("My");
		test.remove("Fake");
		System.out.println(test);
		System.out.println(test.size());

	}

}
