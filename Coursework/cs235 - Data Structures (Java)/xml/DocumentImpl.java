
package cs235.xml;

import java.io.OutputStream;
import java.io.IOException;
import java.io.PrintWriter;


/**
 * The Document interface represents the root of an XML document tree.
 */
public class DocumentImpl extends NodeImpl implements Document {

	/**
     * @return the type of this node (DOCUMENT_NODE)
     */
	public int getType(){
		return DOCUMENT_NODE;
	}
     /**
     * Writes the document in XML format to the specified output stream.
     * 
     * @param output the output stream to which the document should be written
     * @throws IllegalArgumentException if output is null
     * @throws IOException if an output error occurs while writing to the stream
     */
    public void write(OutputStream output) throws IOException {
    	nullCheck(output);
    	
    	PrintWriter pw = new PrintWriter(output);
    	pw.print(getFirstChild());
    	pw.close();
    }
}
