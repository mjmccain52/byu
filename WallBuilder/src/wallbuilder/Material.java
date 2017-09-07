package wallbuilder;

/**
 * Material holds the name, k, and cost values for a particular building
 * material.
 * @author mjmccain
 */
public class Material {
    private String name;
    private double k;
    private double cost;
    
    public Material(String name, double k, double cost){
        this.name = name;
        this.k = k;
        this.cost = cost;
    }
    
    public String getName(){
        return name;
    }
    public double getK(){
        return k;
    }
    public double getCost(){
        return cost;
    }
    
}
