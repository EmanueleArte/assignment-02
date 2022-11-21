import javax.swing.JFrame;

/**
 * Gui implementation based on Swing.
 */
public class SwingGui extends JFrame implements Gui {

    public SwingGui() {
        JFrame frame = new JFrame("SmartBridge");
        frame.setSize(400, 300);
        frame.setLocation(200, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }

    public void start() {
        // metodo start della classe SwingGui
    }

}
