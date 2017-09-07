package cs235.xml;

public class ParserFactory {

    /**
     * Creates and returns an object that implements the Parser interface.
     * This is useful for parsing an existing XML document.
     * 
     * @return a new object that implements the Parser interface
     */
    public static Parser createParser() {
    	return new ParserImpl();
    }

    /**
     * Creates and returns an object that implements the Document interface.
     * This is useful for creating new XML documents.
     *
     * @return a new object that implements the Document interface
     */
    public static Document createDocument() {
    	return new DocumentImpl();
    	
    }
	
    /**
     * Creates a new element node.
     *
     * @param tagName the name of the element
     * @return the new element node
     * @throws IllegalArgumentException if tagName is null
     */
    public static Element createElement(String tagName) {
    	nullCheck(tagName);
    	return new ElementImpl(tagName);
    }

    /**
     * Creates a new text node.
     *
     * @param data the text string to be stored in the new node
     * @return the new text node
     * @throws IllegalArgumentException if data is null
     */
    public static Text createText(String data) {
    	nullCheck(data);
    	return new TextImpl (data);
    }
    
    /**
     * checks for null parameters
     * @param o Object to be checked
     * @throws IllegalArgumentException if o is null
     */
    public static void nullCheck (Object o){
    	if (o == null)
    		throw new IllegalArgumentException("null argument");
    }
}





