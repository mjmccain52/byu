package cs235.xml;

public abstract class NodeImpl implements Node {

	 /**
     * These constants represent the different kinds of XML nodes.
     * 
     * DOCUMENT_NODE - a node that represents an XML document (must be the root)
     * ELEMENT_NODE - a node that represents an XML element
     * TEXT_NODE - a node that represents text content
     */
    @SuppressWarnings("unused")
    private static final int DOCUMENT_NODE = 1;
    @SuppressWarnings("unused")
	private static final int ELEMENT_NODE = 2;
    @SuppressWarnings("unused")
	private static final int TEXT_NODE = 3;
    private NodeImpl parent;
    private NodeImpl firstChild;
    private NodeImpl lastChild;
    private NodeImpl nextSib;
    private NodeImpl prevSib;
    
    public NodeImpl (){
    	parent = null;
    	firstChild = null;
    	lastChild = null;
    	nextSib = null;
    	prevSib = null;
    }

    /**
     * @return the type of this node (DOCUMENT_NODE, ELEMENT_NODE, or TEXT_NODE)
     */
	public abstract int getType();

	/**
     * @return the parent node of this node, or null if it has no parent
     */
	public Node getParent() {
		return parent;
	}
	
	/**
     * @return the first child of this node, or null if it has no children
     */
	public Node getFirstChild() {
		return firstChild;
	}

	/**
     * @return the last child of this node, or null if it has no children
     */
	public Node getLastChild() {
		return lastChild;
	}
	
	/**
     * @return the next sibling of this node, or null if it has no next sibling
     */
	public Node getNextSibling() {
		return nextSib;
	}

	/**
     * @return the previous sibling of this node, or null if it has no 
     * previous sibling
     */
	public Node getPreviousSibling() {
		return prevSib;
	}
	
	/**
     * Inserts a new child node under the target node.
     * 
     * @param newChild the new child node to be inserted
     * @param child the child node before which the new node should be inserted
     * @throws IllegalArgumentException if newChild is null
     * @throws IllegalArgumentException if child is null
     * @throws IllegalArgumentException if child is not a child of the 
     * target node
     */
	public void insertChildBefore(Node newChild, Node child) {
		nullCheck(newChild);
		nullCheck(child);
		childCheck(child);
		
		NodeImpl newChildImpl = (NodeImpl)newChild;
		NodeImpl childImpl = (NodeImpl)child;
		
		newChildImpl.parent = this;
		newChildImpl.nextSib = childImpl;
		newChildImpl.prevSib = childImpl.prevSib;
		if (childImpl.prevSib != null)
			childImpl.prevSib.nextSib = newChildImpl;
		else
			this.firstChild = newChildImpl;
		childImpl.prevSib = newChildImpl;
	}
	
    /**
     * Appends a child to the target node's list of children.
     * 
     * @param newChild the new child node to be appended
     * @throws IllegalArgumentException if newChild is null
     */
	public void appendChild(Node newChild) {
		nullCheck(newChild);
		
		NodeImpl newChildImpl = (NodeImpl)newChild;
		newChildImpl.parent = this;
		if (hasChild())
			this.lastChild.nextSib = newChildImpl;
		else
			this.firstChild = newChildImpl;
		newChildImpl.prevSib = this.lastChild;
		this.lastChild = newChildImpl;
	}

	/**
     * Removes a child from the target node's list of children.
     * 
     * @param child the child to be removed
     * @throws IllegalArgumentException if child is null
     * @throws IllegalArgumentException if child is not a child of the 
     * target node
     */
	public void removeChild(Node child) {
		nullCheck(child);
		childCheck(child);
		
		NodeImpl childImpl = (NodeImpl)child;
		
		if (childImpl.nextSib != null)
			childImpl.nextSib.prevSib = childImpl.prevSib;
		else
			this.lastChild = childImpl.prevSib;
		if (childImpl.prevSib != null)
			childImpl.prevSib.nextSib = childImpl.nextSib;
		else
			this.firstChild = childImpl.nextSib;

	}

	/**
     * Replaces an existing child node with a new node.
     * 
     * @param newChild the new node that is replacing the old node
     * @param oldChild the old node that is being replaced
     * @throws IllegalArgumentException if newChild is null
     * @throws IllegalArgumentException if oldChild is null
     * @throws IllegalArgumentException if oldChild is not a child of the 
     * target node
     */
	public void replaceChild(Node newChild, Node oldChild) {
		nullCheck(newChild);
		nullCheck(oldChild);
		childCheck(oldChild);
		
		NodeImpl newChildImpl = (NodeImpl)newChild;
		NodeImpl oldChildImpl = (NodeImpl)oldChild;
		
		newChildImpl.parent = this;
		newChildImpl.nextSib = oldChildImpl.nextSib;
		newChildImpl.prevSib = oldChildImpl.prevSib;
		if (oldChildImpl.nextSib != null)
			oldChildImpl.nextSib.prevSib = newChildImpl;
		else
			this.lastChild = newChildImpl;
		if (oldChildImpl.prevSib != null)
			oldChildImpl.prevSib.nextSib = newChildImpl;
		else
			this.firstChild = newChildImpl;
	}
	
	/**
	 * Checks for null argument
	 * 
	 * @param o The object to be tested
	 * @throws IllegalArgumentException if o is null
	 */
	public void nullCheck (Object o){
		if (o == null)
			throw new IllegalArgumentException("null arg");
	}
	
	/** 
	 * Checks for a child=parent relationship between target and child node
	 * 
	 * @param child Node to be tested
	 * @throws IllegalArgumentException if target node is not parent
	 */
	public void childCheck(Node child){
		if (child.getParent() != this)
			throw new IllegalArgumentException ("unrelated nodes");
	}
	
	/**
	 * Tests for children
	 * @return true if the target node has at least one child
	 */
	public boolean hasChild (){
		return lastChild != null;
	}
}
