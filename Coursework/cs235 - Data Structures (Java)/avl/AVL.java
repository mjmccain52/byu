package cs235.avl;

import java.util.Collection;

public class AVL implements Tree {

	private Node root;
	private int size;
	private boolean contains;  //I use this puppy to shave off
					// and additional log(N) to my time.
	
	public AVL(){
		root = null;
		size = 0;
	}
	
	/**
     * Returns the root node for this tree
     * 
     * @return the root node for this tree.
     */
	public BinaryTreeNode getRootNode(){
		return root;
	}
	
	/**
	 * Checks the tree to see if it contains the object
	 * 
	 * @param o Object to be checked
	 * @return true if the tree contains the object.
	 */
	public boolean contains(Object o) {
		nullCheck(o);

		return contains((Comparable)o, root);
	}
	
	/**
	 * Recursively goes down the tree for "contains"
	 * @param c Comparable to be checked
	 * @param n current Node
	 * @return true if object is found.
	 */
	private boolean contains(Comparable c, Node n){
		if (n == null)
			return false;
		else if (c.compareTo(n.data) < 0)
			return contains(c, n.left);
		else if (c.compareTo(n.data) > 0)
			return contains(c, n.right);
		return true;
	}
	
	/**
	 * Adds a non-duplicate Object to the tree.
	 * 
	 * @param o Object to be added
	 * @return true if added successfully
	 */
	public boolean add(Object o) {
		nullCheck(o);
		
		contains = false;
		root = add((Comparable)o, root);
		if (!contains)
			size++;
		return !contains;
	}
	
	/**
	 * Recursively finds the correct place to add an object.
	 * 
	 * @param c Comparable to be added
	 * @param n current Node
	 * @return subtree of current node.
	 */
	private Node add (Comparable c, Node n){
		if (n == null)
			n = new Node (c);
		else if (c.compareTo(n.data) < 0)
			n.left = add(c, n.left);
		else if (c.compareTo(n.data) > 0)
			n.right = add(c, n.right);
		else
			contains = true;
		n = balance(n);
		return n;
	}
	
	/**
	 * Removes an object from the tree
	 * 
	 * @param o Object to be removed
	 * @return true if object was successfully removed.
	 */
	public boolean remove(Object o) {
		nullCheck(o);
		contains = false;

		root = remove ((Comparable)o, root);
		if (contains)
			size--;
		return contains;

	}
	
	/**
	 * Recursively searches tree for object to remove
	 * 
	 * @param c Comparable to be removed
	 * @param n current Node
	 * @return subtree of current node
	 */
	private Node remove (Comparable c, Node n){
		if (n!= null){
			if (c.compareTo(n.data) < 0)
				n.left = remove(c, n.left);
			else if (c.compareTo(n.data) > 0)
				n.right = remove(c, n.right);
			else if(n.left == null){
					n = n.right;
					contains = true;
			}
			else if (n.right == null){
				n = n.left;	
				contains = true;
			}
			else{
				n.data = findMin(n.right);
				n.right = remove (n.data, n.right);
				contains = true;
			}
			n = balance(n);
			n = balance(n); // just in case...
			
		}
		return n;
	}
	
	/**
	 * Recursively finds smallest value in tree.
	 * 
	 * @param n current Node
	 * @return smallest value
	 */
	private Comparable findMin (Node n){
		if (n == null)
			return null;
		else if (n.left == null)
			return n.data;
		else
			return findMin(n.left);
	}
	
	/**
	 * Returns height of given Node
	 * @param n Node
	 * @return height of node, -1 if null
	 */
	private int getHeight (Node n){
		if (n == null)
			return -1;
		return n.height;
	}

	/**
	 * Balances the AVL tree.  Handles single and double rotations
	 * 
	 * @param n Subtree to balance
	 * @return balanced subtree
	 */	
	private Node balance(Node n){
		Node temp = n;
		Node doub;
		if (n==null)
			return null;
		
			
		if (this.getHeight(n.left) - this.getHeight(n.right) > 1){
			//requires right rotation
			temp = n.left;
			if(this.getHeight(temp.right) - 
					this.getHeight(temp.left) > 0){
				//requires double rotation
				doub = temp.right;
				temp.right = doub.left;
				doub.left = temp;
				temp.height = Math.max(this.getHeight(temp.left), 
						this.getHeight(temp.right)) + 1;
				temp = doub;
				temp.height = Math.max(this.getHeight(temp.left), 
						this.getHeight(temp.right)) + 1;
			}
				
			n.left = temp.right;
			temp.right = n;
		}
		 
		else if (this.getHeight(n.right) - this.getHeight(n.left) > 1){
			//requires left rotation
			temp = n.right;
			if(this.getHeight(temp.left) - 
					this.getHeight(temp.right) > 0){
				//requires double rotation
				doub = temp.left;
				temp.left = doub.right;
				doub.right = temp;
				temp.height = Math.max(this.getHeight(temp.left), 
						this.getHeight(temp.right)) + 1;
				temp = doub;
				temp.height = Math.max(this.getHeight(temp.left), 
						this.getHeight(temp.right)) + 1;
			}
			n.right = temp.left;
			temp.left = n;
		}
		n.height = Math.max(this.getHeight(n.left), 
				this.getHeight(n.right)) + 1;
		return temp;
	}
	
	/**
	 * Clears the tree.
	 */
	public void clear() {
		root = null;
		size = 0;
	}

	/**
	 * @return true if tree is empty
	 */
	public boolean isEmpty() {
		return root == null;
	}

	/**
	 * @return size of tree (total nodes)
	 */
	public int size() {
		return size;
	}
	
	/**
	 * Creates a pre-order array of the objects in the tree
	 * 
	 * @return pre-order array
	 */
	public Object[] toArray() {
		Object [] array = new Object[size];
		Iterator it = iterator();
		for (int i = 0; it.hasNext(); i++)
			array[i] = it.next();
		return array;
	}
	
	/**
	 * @return Iterator for the tree
	 */
	public Iterator iterator() {
		return new Iterator(root);
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
	
	private class Node implements BinaryTreeNode {
		private Comparable data;
		private Node left;
		private Node right;
		private int height;
		
		Node (Comparable data){
			this.data = data;
			left = null;
			right = null;
			height = 0;
		}

		public Object getData() {
			return data;
		}

		public int getHeight() {
			return height;
		}

		public BinaryTreeNode getLeftChild() {
			return left;
		}

		public BinaryTreeNode getRightChild() {
			return right;
		}
	}
	
	private class Iterator implements java.util.Iterator{

		private java.util.Stack<Node> stack;
		
		public Iterator (Node root){
			stack = new java.util.Stack<Node>();
			stack.push(root);
		}
		public boolean hasNext() {
			return !stack.isEmpty() && !isEmpty();
		}

		public Object next() {
			Node n = stack.pop();
			if (n.right != null)
				stack.push (n.right);
			if (n.left != null)
				stack.push(n.left);
			return n.data;
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
