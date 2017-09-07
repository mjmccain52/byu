package cs235.xml;

public class TextImpl extends NodeImpl implements Text{

	private String data;
	
	public TextImpl (String data){
		this.data = data;
	}
	/**
     * @return the type of this node (TEXT_NODE)
     */
	public int getType(){
		return TEXT_NODE;
	}
    /**
     * @return the text string stored in this node
     */
    public String getData(){
    	return data;
    }
    
    /**
     * @return the text string stored in this node
     */
    public String toString(){
    	return getData();
    }
    
    /**
     * Sets the text string stored in this node.
     * 
     * @param data the text string to be stored in this node
     * @throws IllegalArgumentException if data is null
     */
    public void setData(String data){
    	nullCheck(data);
    	
    	this.data = data;
    }
}
