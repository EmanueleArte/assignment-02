import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import java.awt.*;

/**
 * SmartBridgeView implementation based on Swing.
 */
public class SwingGui extends JFrame implements SmartBridgeView {
    private static final long serialVersionUID = 1L;
    private final JFrame frame;
    private final JTextField smartLightTextField;
    private final JTextField situationTextField;
    private final JSlider valveOpeningSlider;
    private final JLabel valveLabel;
    private final JLabel programState;
    private SmartBridgeController controller;

    public SwingGui() {
        frame = new JFrame("SmartBridge");
        frame.setSize(350, 300);
        frame.setLocation(200, 200);

        Container pane = frame.getContentPane();
        pane.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        programState = new JLabel("Program state: ");

        // Smart light state
        JLabel smartLightLabel = new JLabel("Smart light: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 0;
        pane.add(smartLightLabel, c);
        smartLightTextField = new JTextField(3);
        smartLightTextField.setEditable(false);
        smartLightTextField.setText("OFF");
        c.gridx = 1;
        pane.add(smartLightTextField, c);

        // Situation state
        JLabel situationLabel = new JLabel("Situation: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 1;
        pane.add(situationLabel, c);
        situationTextField = new JTextField(6);
        situationTextField.setEditable(false);
        situationTextField.setText("Pre-alarm");
        c.gridx = 1;
        pane.add(situationTextField, c);

        // Valve controller
        valveLabel = new JLabel("Valve opening: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 2;
        pane.add(valveLabel, c);
        valveOpeningSlider = new JSlider(0, 180, 0);
        c.gridx = 1;
        pane.add(valveOpeningSlider, c);

        // Temporal trend of water level
        JTextArea trendTextArea = new JTextArea(10, 20);
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 3;
        c.gridx = 0;
        c.gridy = 3;
        pane.add(trendTextArea, c);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.pack();
    }

    @Override
    public void start() {
        frame.setVisible(true);
    }

    @Override
    public void updateSmartLightStatus(final boolean state) {
        smartLightTextField.setText(state ? "ON" : "OFF");
    }

    @Override
    public void showValveController() {
        valveLabel.setVisible(true);
        valveOpeningSlider.setVisible(true);
    }

    @Override
    public void hideValveController() {
        valveLabel.setVisible(false);
        valveOpeningSlider.setVisible(false);
    }

    @Override
    public void updateWaterTrend(String trend) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void updateSituation(final String situation) {
        situationTextField.setText(situation);
    }

    @Override
    public void setController(SmartBridgeController controller) {
        this.controller = controller;
    }

    @Override
    public void setProgramState(final String state) {
        programState.setText(state);
    }

}
