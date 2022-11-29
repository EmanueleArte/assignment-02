import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.JTextField;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeriesCollection;

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
    private final JButton remoteControlButton;
    private final JLabel valveLabel;
    private final JLabel programState;
    private SmartBridgeController controller;
    private final XYSeriesCollection waterDataSet;

    public SwingGui(final XYSeriesCollection dataSet) {
        frame = new JFrame("SmartBridge");
        frame.setMinimumSize(new Dimension(500, 400));
        frame.setLocation(200, 200);

        Container pane = frame.getContentPane();
        pane.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        programState = new JLabel("Offline.");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 0;
        pane.add(programState, c);

        // Smart light state
        JLabel smartLightLabel = new JLabel("Smart light: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 1;
        pane.add(smartLightLabel, c);
        smartLightTextField = new JTextField(3);
        smartLightTextField.setEditable(false);
        c.gridx = 1;
        pane.add(smartLightTextField, c);

        // Situation state
        JLabel situationLabel = new JLabel("Situation: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 2;
        pane.add(situationLabel, c);
        situationTextField = new JTextField(6);
        situationTextField.setEditable(false);
        c.gridx = 1;
        pane.add(situationTextField, c);

        // Valve controller
        valveLabel = new JLabel("Valve opening: ");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 3;
        pane.add(valveLabel, c);
        valveOpeningSlider = new JSlider(0, 180, 0);
        c.gridx = 1;
        pane.add(valveOpeningSlider, c);
        // Button to set remote control
        remoteControlButton = new JButton("Activate Remote control");
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 4;
        pane.add(remoteControlButton, c);

        // Temporal trend of water level
        waterDataSet = dataSet;
        JFreeChart chart = ChartFactory.createXYLineChart(
                "Water trend",
                "time(s)",
                "water level",
                waterDataSet,
                PlotOrientation.VERTICAL,
                false,
                true,
                false
                );

        ChartPanel waterLevel = new ChartPanel(chart);
        waterLevel.setPreferredSize(new Dimension(400, 200));
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 3;
        
        c.gridx = 0;
        c.gridy = 5;
        pane.add(waterLevel, c);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
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
        if (!remoteControlButton.isVisible()) {
            setRemoteControl(false);
        }
        valveLabel.setVisible(true);
        valveOpeningSlider.setVisible(true);
        remoteControlButton.setVisible(true);
    }

    @Override
    public void hideValveController() {
        valveLabel.setVisible(false);
        valveOpeningSlider.setVisible(false);
        remoteControlButton.setVisible(false);
    }

    @Override
    public void updateSituation(final String situation) {
        situationTextField.setText(situation);
    }

    @Override
    public void setController(SmartBridgeController controller) {
        this.controller = controller;
        // Add listener to the slider
        valveOpeningSlider.addChangeListener(e -> {
            if (valveOpeningSlider.isVisible()) {
                JSlider slider = (JSlider) e.getSource();
                this.controller.setValveOpening(slider.getValue());
            }
        });
        // Add listener to the button
        remoteControlButton.addActionListener(e -> {
            setRemoteControl(remoteControlButton.getText() == "Activate Remote control");
        });
    }

    @Override
    public void setProgramState(final String state) {
        programState.setText(state);
    }

    @Override
    public void setRemoteControl(boolean state) {
        if (state) {
            this.controller.setValveOpening(-1);
            remoteControlButton.setText("Deactivate Remote control");
            valveOpeningSlider.setEnabled(true);
        } else {
            this.controller.setValveOpening(-2);
            remoteControlButton.setText("Activate Remote control");
            valveOpeningSlider.setValue(0);
            valveOpeningSlider.setEnabled(false);
        }
    }

}
