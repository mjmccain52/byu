package wallbuilder;

/**
 * Layer contains geometric and material properties of one layer of the conductive wall
 * @author mjmccain
 */
public class Layer {
    private double thickness;
    private Material m;
    
    public Layer (double thickness, Material m){
        this.thickness = thickness;
        this.m = m;
    }
    public double getThickness(){
        return thickness;
    }
    public Material getMaterial(){
        return m;
    }

}

