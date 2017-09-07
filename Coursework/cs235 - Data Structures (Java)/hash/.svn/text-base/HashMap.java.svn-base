package cs235.hash;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public class HashMap implements Map {

	private Set hashTable = new HashSet();
	
	public HashMap(){
		clear();
	}
	public void clear() {
		hashTable.clear();
	}

	public Object get(Object key) {
		nullCheck(key);
		Pair pair = ((HashSet)hashTable).containsKey(new Pair(key, null));
		if (pair != null)
			return pair.getValue();
		return null;
	}

	public boolean isEmpty() {
		return hashTable.isEmpty();
	}
	
	private void nullCheck(Object o){
		if (o == null)
			throw new IllegalArgumentException();
	}
	
	public Object put(Object key, Object value) {
		nullCheck(key);
		Pair toAdd = new Pair (key, value);
		Pair replaced = ((HashSet)hashTable).replace(toAdd);
		if (replaced != null)
			return replaced.getValue();
		return null;
	}

	public Object remove(Object key) {
		Pair temp = ((HashSet)hashTable).containsKey(new Pair (key, null));
		hashTable.remove(new Pair (key, null));
		if (temp != null)
			return temp.getValue();
		return null;
	}

	public int size() {
		return hashTable.size();
	}

	public boolean containsKey(Object arg0) {
		throw new UnsupportedOperationException();
	}

	public boolean containsValue(Object arg0) {
		throw new UnsupportedOperationException();
	}

	public Set entrySet() {
		throw new UnsupportedOperationException();
	}

	public Set keySet() {
		throw new UnsupportedOperationException();
	}
	
	public Collection values() {
		throw new UnsupportedOperationException();
	}

	public void putAll(Map t) {
		throw new UnsupportedOperationException();		
	}
}
