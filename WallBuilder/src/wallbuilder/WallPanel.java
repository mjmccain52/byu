package wallbuilder;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Random;
import javax.swing.*;
/**
 * This large scary looking class is mostly GUI fluff. Its only important computational
 * tasks are to initialize all the material properties, randomize the ambient conditions, 
 * and retrieve user input.
 * @author mjmccain
 */
public final class WallPanel extends JPanel implements ActionListener{
    
    private double target = 10;
    private double costTarget = 10.00;
    private double windspeed;
    private double to;
    private ArrayList<Material> materials;
    private String[] matsArr;
    private ArrayList<Layer> layers;
    
    private JComboBox dropList;
    private JButton add;
    private JButton solve;
    
    private JRadioButton one;
    private JRadioButton twoAndHalf;
    private JRadioButton five;
    private JRadioButton ten;
    
    private JPanel console;
    
    public WallPanel(){
        dataInit();
        visualsInit();
       
    }
    public void dataInit(){
        double[] speeds = {1,2,5,10,20};
        double[] tos = {250,263,273,283};
        Random r = new Random();
        add = new JButton("Add to list");
        solve = new JButton("Solve");
        materials = new ArrayList<>();
        layers = new ArrayList<>();
        one = new JRadioButton("1 cm", true);
        twoAndHalf= new JRadioButton("2.5 cm", false);
        five= new JRadioButton("5 cm", false);
        ten= new JRadioButton("10 cm", false);
        
		//Materials have a name, thermal conductivity, and cost per square meter.
        materials.add (new Material("Hardboard Siding", .094,5.92));
        materials.add (new Material("Particle Board", .17,13.41));
        materials.add (new Material("Plywood", .12,1.43));
        materials.add (new Material("Cement", .72,6.45));
        materials.add (new Material("Brick", .72,5.38));
        materials.add (new Material("Fiberglass", .038,9.2));
        materials.add (new Material("Cork", .039,7.53));
        matsArr = new String[materials.size()];
        for (int i = 0; i < materials.size(); i++){
                matsArr[i] = materials.get(i).getName();
        }
        dropList = new JComboBox(matsArr);
        
        windspeed = speeds[r.nextInt(speeds.length)];
        to = tos[r.nextInt(tos.length)];
              
        add.addActionListener(this);
        solve.addActionListener(this);
     

    }
    public void visualsInit(){
        this.setPreferredSize(new Dimension(500,350));
        console = new JPanel();
        console.setLayout(new BoxLayout (console, BoxLayout.Y_AXIS));
        console.setBorder(BorderFactory.createTitledBorder("Wall Panel"));
        console.setOpaque(false);
        
        
        add(new JLabel("IN THE COLD, SUNLESS, WINDY POST-APOCALYPTIC WORLD,"));
        add(new JLabel("YOU ARE BUILDING THE ONE WALL THAT WILL KEEP YOU WARM"));
        add(new JLabel("AND PROTECT YOU FROM ZOMBIES! (All other sides of the "
                + "cave are perfectly insulated)"));
        add(new JLabel("Design a wall (3 m tall) that loses less than " + 
                target + " Watts per square meter"));
         add(new JLabel("and costs less than $" + costTarget + " per square meter."));
        add(new JLabel("Outside conditions are " + to + "K and " + windspeed + 
                " m/s wind"));
        add(new JLabel("The inside surface of your wall is constant at 293K"));
        JPanel menuPanel = new JPanel();
        dropList.setBackground(Color.WHITE);
        
        ButtonGroup thickButtons = new ButtonGroup();
        thickButtons.add(one);
        thickButtons.add(twoAndHalf);
        thickButtons.add(five);
        thickButtons.add(ten);
        menuPanel.add (dropList);
        menuPanel.add(one);
        menuPanel.add(twoAndHalf);
        menuPanel.add(five);
        menuPanel.add(ten);
        menuPanel.setOpaque(false);
        console.add(menuPanel);
        console.add(add);
        
        JPanel listPanel = new JPanel();
        console.add(listPanel);
        add(console);
        add(solve);
    }
    @Override
    public void actionPerformed(ActionEvent event){
    
        if (event.getSource()==add){
            double thick;
            if (one.isSelected()){
                thick = .01;
            } else if (twoAndHalf.isSelected()){
                thick = .025;
            } else if (five.isSelected()){
                thick = .05;
            } else {
                thick = .1;
            }
            Material m = materials.get(dropList.getSelectedIndex());
            Layer temp = new Layer(thick,m);
            layers.add(temp);   
            console.add(new JLabel(temp.getMaterial().getName() + " " 
                    + temp.getThickness() + " m thick"));
            console.getRootPane().revalidate();
        }
        if (event.getSource()==solve){
            if (layers.isEmpty()){
                JOptionPane.showMessageDialog(null, "You must have at least one"
                        + " layer!", "Moron.", JOptionPane.INFORMATION_MESSAGE);
                return;
            }
            Calculator calc = new Calculator();
            double q = calc.findQ(layers,to,windspeed);
			double c = calc.totalCost(layers);
            if (q < target && c < costTarget){
                add(new JLabel("Congratulations! Your wall loses " + 
                        (double)Math.round(q * 1000) / 1000 
                        + " Watts per meter squared and costs $" + 
                        (double)Math.round(c * 100) / 100 + " per meter!"));
            } else{
                add(new JLabel("Failure! Your wall loses " 
                        + (double)Math.round(q * 1000) / 1000 
                        + " Watts per meter squared and costs $" + 
                        (double)Math.round(c * 100) / 100 + " per meter!"));
            } 
            this.getRootPane().revalidate();
        }
    }
}
