package wallbuilder;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * This is where the heat transfer happens. Data is gathered from the user and sent
 * here for calculation. Heat modes considered are conduction through a composite plane
 * wall with no generation and forced convection with laminar or turbulent flow.
 * @author mjmccain
 */
public class Calculator {
    public static final double HEIGHT = 3; //Height of the wall
    public static final double TI = 293; //Inside surface Temperature in Kelvins
    
	//enumerated values for readability when looking up properties.
	public static final int K = 0;
    public static final int KINE_VISC = 1;
    public static final int PR = 2;
	
	//the properties map has a list of properties associated with a given temperature.
    private HashMap<Double, ArrayList<Double>> properties;
    
	/**
	* The constructor initializes all thermal properties
	*/
    public Calculator(){
        properties = new HashMap<>();
        ArrayList<Double> t250 = new ArrayList<>();
        t250.add(new Double(.0223)); // Thermal conductivity k
        t250.add(new Double(11.44e-6)); //kinematic viscosity nu
        t250.add(new Double(.72)); // Prandtl number Pr
        properties.put(new Double(250), t250); //Associated temperature in Kelvins
        ArrayList<Double> t263 = new ArrayList<>();
        t263.add(new Double(.0241));
        t263.add(new Double(13.49e-6));
        t263.add(new Double(.714)); 
        properties.put(new Double(263), t263);
        ArrayList<Double> t273 = new ArrayList<>();
        t273.add(new Double(.0233));
        t273.add(new Double(12.6e-6));
        t273.add(new Double(.717)); 
        properties.put(new Double(273), t273);        
        ArrayList<Double> t283 = new ArrayList<>();
        t283.add(new Double(.0249));
        t283.add(new Double(14.38e-6));
        t283.add(new Double(.711)); 
        properties.put(new Double(283), t283);
        ArrayList<Double> t293 = new ArrayList<>();
        t293.add(new Double(.0257));
        t293.add(new Double(15.27e-6));
        t293.add(new Double(.709)); 
        properties.put(new Double(293), t293);


    }
	/**
	*	The final flux equation q = dT/Rtotal
	*/
    public double findQ(ArrayList<Layer> layers, double to, double windspeed){
        
        double r = findResistance(layers, findHo(windspeed,to));
        return (TI - to)/r;
    }

	/**
	* Finds the convection coefficient outside the wall, considering both
	* laminar and turbulent flow
	*/
    private double findHo(double v, double to){
        double pr = properties.get(new Double(to)).get(PR);
        double reynolds = re(v,to);
        double nu;
        if (reynolds < 5e5){ // Laminar flow over flat plate
            nu= .664 * Math.pow(reynolds,.5)*Math.pow(pr,1/3.0);
        } else { //turbulent flow over flat plate
            nu = (.037*Math.pow(reynolds, .8)-871)*Math.pow(pr, 1/3.0);
        }
        double ko = properties.get(new Double(to)).get(K);
        double ho = nu*ko/HEIGHT;
        return ho;
    }
	
	/**
	* Calculates the Reynolds Number
	*/
    private double re(double v, double to){
        double nu = properties.get(new Double(to)).get(KINE_VISC);
        return v*HEIGHT/nu;
    }
	
	/**
	* Calculates total resistance of the network.
	*/
    private double findResistance(ArrayList<Layer> layers, double ho){
        double r =0;
        for (int i = 0; i < layers.size(); i++){
            Layer l = layers.get(i);
            r += l.getThickness() / l.getMaterial().getK();
        }
        r+= 1/ho;
        return r;
    }
	
	public double totalCost(ArrayList<Layer> layers){
		double cost = 0;
		for (Layer layer: layers){ //layer layer!
			cost += layer.getMaterial().getCost()*HEIGHT*layer.getThickness();
		}
		return cost;
	}
}
