package cs235.hash;

import java.util.Collection;
import java.util.Set;
import java.util.LinkedList;
import java.util.List;

public class HashSet implements Set {

	private static final int INIT_SIZE = 101;
	private List[] hashTable;
	private int hashTableSize;
	private int size;
	
	public HashSet(){
		clear();
	}
	public boolean contains(Object o) {
		nullCheck(o);

		return hashTable[Math.abs(o.hashCode() % hashTableSize)].contains(o);
	}
	public Pair containsKey(Pair p){
		if (contains(p)){
			List temp = hashTable[Math.abs(p.hashCode() % hashTableSize)];
			return (Pair) temp.get(temp.indexOf(p));
		}
		return null;
	}
	public Pair replace (Pair p){
		if (contains(p)){
			List temp = hashTable[Math.abs(p.hashCode() % hashTableSize)];
			Pair replaced = containsKey(p);
			temp.set(temp.indexOf(p), p);
			return replaced;
		}
		add(p);
		return null;
	}
	
	
	public boolean add(Object o) {
		nullCheck(o);
		
		if (contains(o))
			return false;
		if ((size + 1.0) / hashTableSize > 1)
			reHash();
		hashTable[Math.abs(o.hashCode() % hashTableSize)].add(o);
		size++;
		return true;
	}
	
	private void reHash(){
		int newSize = hashTableSize * 2 + 1;
		List[] temp = new LinkedList[newSize];
		for (int i = 0; i < newSize; i++)
			temp[i] = new LinkedList();
		Iterator it = iterator();
		while (it.hasNext()){
			Object o = it.next();
			temp[Math.abs(o.hashCode() % newSize)].add(o);
		}
		hashTable = temp;
		hashTableSize = newSize;
	}
	
	public boolean remove(Object o) {
		nullCheck(o);
		if (!contains(o))
			return false;
		size--;
		return hashTable[Math.abs(o.hashCode() % hashTableSize)].remove(o);
		
	}
	
	
	public void clear() {
		hashTable = new LinkedList[INIT_SIZE];
		size = 0;
		hashTableSize = INIT_SIZE;
		for (int i = 0; i < INIT_SIZE; i++)
			hashTable[i] = new LinkedList();
	}

	public boolean isEmpty() {
		return size == 0;
	}

	public int size() {
		return size;
	}
	
	public Object[] toArray() {
		Iterator i = iterator();
		int index = 0;
		Object[] array = new Object [size];
		while (i.hasNext()){
			array[index] = i.next();
			index++;
		}
		return array;
	}
	
	/**
	 * @return Iterator for HashSet
	 */
	public Iterator iterator() {
		return new Iterator();
	}
	
	/**
	 * Checks for null arguments
	 * 
	 * @param o Argument to be checked
	 * @throws IllegalArgumentException if o is null
	 */
	private void nullCheck(Object o){
		if (o == null)
			throw new IllegalArgumentException();
	}
	
	public String toString()
	{
		final int perLine = 5;
		String output = "[";
		Iterator i = iterator();
		int n = 0;
		while (i.hasNext()){
			output += i.next();
			n++;
			if (i.hasNext()){
				output+= ", ";
			}
			if (n == perLine && i.hasNext()){
				output+= "\n";
				n =0;
			}
		}
		output+= "]";
		return output;
	}
	
	
	private class Iterator implements java.util.Iterator{
		private int bucket;
		private int index;
		private int accessed;
		public Iterator(){
			bucket = 0;
			index = 0;
			accessed = 0;
		}
		public boolean hasNext() {
			return accessed < size ;
		}

		public Object next() {
			while (hashTable[bucket].size() == index){
				bucket++;
				index = 0;
			}
			Object temp = hashTable[bucket].get(index);
			index++;
			accessed++;
			return temp;
		}

		public void remove() {
			throw new UnsupportedOperationException();			
		}
		
	}

	public boolean containsAll(Collection c) {
		throw new UnsupportedOperationException();
	}
	
	public boolean removeAll(Collection c) {
		throw new UnsupportedOperationException();
	}

	public boolean retainAll(Collection c) {
		throw new UnsupportedOperationException();
	}
	
	public boolean addAll(Collection c) {
		throw new UnsupportedOperationException();
	}

	public Object[] toArray(Object[] array) {
		throw new UnsupportedOperationException();
	}
}
