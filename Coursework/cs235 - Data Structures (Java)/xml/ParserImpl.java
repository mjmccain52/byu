
package cs235.xml;

import java.io.InputStream;
import java.io.IOException;
import java.util.Stack;

/**
 * The Parser interface represents an XML parser.
 */
public class ParserImpl implements Parser {

    /**
     * Parses the XML document contained in the specified input stream
     * and returns a document tree that represents the document.
     * 
     * @param input an input stream containing an XML document
     * @return the root node of document tree
     * @throws IllegalArgumentException if input is null
     * @throws IOException if an input error occurs while parsing the XML document
     * @throws XMLException if the XML document being parsed is not in valid XML format
     */
    public Document parser(InputStream input) throws IOException, XMLException{
    	if (input == null)
    		throw new IllegalArgumentException ("null argument");
    
    	Tokenizer scan = new TokenizerImpl(input);  //this error is ok.  have class file
    	Document doc = ParserFactory.createDocument();
    	Node n = doc;
    	while (scan.nextToken() != Tokenizer.EOF){
    		if (scan.getTokenType() == Tokenizer.START_TAG){
    			Node temp = ParserFactory.createElement(scan.getTagName());
    			n.appendChild(temp);
    			n = temp;
    			for (int i = 0; i < scan.getAttributeCount(); i++)
    				((Element)n).setAttribute(scan.getAttributeName(i), 
    						scan.getAttributeValue(i));
    		}
    		if (scan.getTokenType() == Tokenizer.TEXT)
    			n.appendChild(ParserFactory.createText(scan.getText()));
    		if (scan.getTokenType() == Tokenizer.END_TAG){
    			try{
	    			if (!scan.getTagName().equals(((Element)n).getTagName()))
	    				throw new XMLException();
	    			n = n.getParent();
    			}
    			catch (ClassCastException e){ // if missing start tag
    				throw new XMLException();
    			}
    		}
    	}
    	if (n.getType() != 1)  //if missing end tag
    		throw new XMLException();
    	
    	return doc;
    }
    public Document parse(InputStream input) throws IOException, XMLException{
    	if (input == null)
    		throw new IllegalArgumentException ("null argument");
    
    	Tokenizer scan = new TokenizerImpl(input);  //this error is ok.  have class file
    	Document doc = ParserFactory.createDocument();
    	Stack<String> layers = new Stack<String>();
    	Node n = doc;
    	while (scan.nextToken() != Tokenizer.EOF){
    		//System.out.println(layers.peek());
    		switch (scan.getTokenType()){
    		case Tokenizer.START_TAG:
    			layers.push(scan.getTagName());
    			Element temp = ParserFactory.createElement(scan.getTagName());
    			for (int i = 0; i < scan.getAttributeCount(); i++)
    				temp.setAttribute(scan.getAttributeName(i), 
    						scan.getAttributeValue(i));
    			n.appendChild(temp);
    			n = temp;
    			break;
    		case Tokenizer.END_TAG:
    			if (layers.isEmpty() || !layers.peek().equals(scan.getTagName()))
    				throw new XMLException();
    			n = n.getParent();
    			layers.pop();
    			break;
    		case Tokenizer.TEXT:
    			n.appendChild(ParserFactory.createText(scan.getText()));
    		default:
    			break;
    		}
    	}
    	if (!layers.isEmpty())
    		throw new XMLException();
    	return doc;
    }
}
