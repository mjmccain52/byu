package wallbuilder;

import java.util.ArrayList;
import javax.swing.JFrame;

/**
 * WallBuilder computes the heat flux given certain ambient outside conditions
 * and users' choice of conductive material. The outside conditions are randomized.
 * @author mjmccain
 */
public class WallBuilder {
    /**
     * The main driver launches the main GUI window.
     */
    public static void main(String[] args) {
        Calculator test = new Calculator();
        
        JFrame frame = new JFrame ("WallBuilder");
        frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);

        frame.getContentPane().add(new WallPanel());
        frame.pack();
        frame.setVisible(true);
    
    }
}
