import org.jfree.data.xy.XYSeriesCollection;

/**
 * SmartBridgeController implementation.
 */
public class SmartBridgeControllerImpl implements SmartBridgeController {
    private final SmartBridgeView view;
    private final SmartBridgeModel model;
    
    public SmartBridgeControllerImpl(final SmartBridgeView view, final String port, final XYSeriesCollection dataSet) {
        this.view = view;
        model = new SmartBridgeModelArduino(this, port, dataSet);
    }
    
    @Override
    public void setValveOpening(final int opening) {
        model.setValveOpening(opening);
    }

    @Override
    public void setSmartLightOn() {
        view.updateSmartLightStatus(true);
    }

    @Override
    public void setSmartLightOff() {
        view.updateSmartLightStatus(false);
    }

    @Override
    public void setSituation(final String situation) {
        view.updateSituation(situation);
    }

    @Override
    public void setProgramState(final String state) {
        view.setProgramState(state);
    }

    @Override
    public void showValveController() {
        view.showValveController();
    }

    @Override
    public void hideValveController() {
        view.hideValveController();
    }

    @Override
    public void setRemoteControl(boolean state) {
        view.setRemoteControl(state);
    }
    
}
