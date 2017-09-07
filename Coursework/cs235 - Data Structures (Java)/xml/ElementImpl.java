package cs235.xml;

import java.util.List;
import java.util.ArrayList;

public class ElementImpl extends NodeImpl implements Element {

	private String tagName;
	private List<String> attributeNames;
	private List<String> attributeValues;

	public ElementImpl(String tagName) {
		this.tagName = tagName;
		attributeNames = new ArrayList<String>();
		attributeValues = new ArrayList<String>();
	}

	/**
	 * @return the type of this node (ELEMENT_NODE)
	 */
	public int getType() {
		return ELEMENT_NODE;
	}

	/**
	 * @return the name of this element
	 */
	public String getTagName() {
		return tagName;
	}

	/**
	 * Sets the name of this element.
	 * 
	 * @param the
	 *            new name of the element
	 * @throws IllegalArgumentException
	 *             if tagName is null
	 */
	public void setTagName(String tagName) {
		nullCheck(tagName);

		this.tagName = tagName;
	}

	/**
	 * Returns the value of the specified attribute.
	 * 
	 * @param name
	 *            the name of the attribute whose value is being requested
	 * @return the value of the specified attribute, or null if the element has
	 *         no attribute with that name
	 * @throws IllegalArgumentException
	 *             if name is null
	 */
	public String getAttributeValue(String name) {
		nullCheck(name);

		if (attributeNames.contains(name))
			return attributeValues.get(attributeNames.indexOf(name));
		return null;
	}

	/**
	 * @return the number of attributes that this element has
	 */
	public int getAttributeCount() {
		return attributeNames.size();
	}

	/**
	 * Returns the name of the ith attribute (indices start at 0)
	 * 
	 * @param i
	 *            the index of the attribute whose name is being requested
	 * @return the name of the ith attribute (indices start at 0)
	 * @throws IllegalArgumentException
	 *             if i is an invalid index
	 */
	public String getAttributeName(int i) {
		indexCheck(i);

		return attributeNames.get(i);
	}

	/**
	 * Returns the value of the ith attribute (indices start at 0)
	 * 
	 * @param i
	 *            the index of the attribute whose value is being requested
	 * @return the value of the ith attribute (indices start at 0)
	 * @throws IllegalArgumentException
	 *             if i is an invalid index
	 */
	public String getAttributeValue(int i) {
		indexCheck(i);

		return attributeValues.get(i);
	}

	/**
	 * Sets the value of the specified attribute on this element.
	 * 
	 * @param name
	 *            the name of the attribute that is being set
	 * @param value
	 *            the value of the attribute that is being set
	 * @throws IllegalArgumentException
	 *             if name is null
	 * @throws IllegalArgumentException
	 *             if value is null
	 */
	public void setAttribute(String name, String value) {
		nullCheck(name);
		nullCheck(value);

		attributeNames.add(name);
		attributeValues.add(value);
	}

	public String toString() {
		String output = "";

		output += "<" + tagName;
		for (int i = 0; i < getAttributeCount(); i++)
			output += " " + attributeNames.get(i) + "=\""
					+ attributeValues.get(i) + "\"";
		if (getFirstChild() == null) // empty elements look nice
			output += "/>";

		else {
			output += ">";
			Node n;
			for (n = getFirstChild(); n != null; n = n.getNextSibling()) 
				output += n;
			output += "</" + tagName + ">";
		}
		return output;
	}

	/**
	 * checks for out of range index
	 * 
	 * @param i
	 *            index to be checked
	 * @throws IllegalArgumentException
	 *             if index is invalid
	 */
	public void indexCheck(int i) {
		if (i < 0 || i >= attributeNames.size())
			throw new IllegalArgumentException("invalid index");
	}
}
