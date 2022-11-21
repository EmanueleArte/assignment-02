/**
 * SmartBridgeController implementation.
 */
public class SmartBridgeControllerImpl implements SmartBridgeController {
    private final SmartBridgeView view;
    private final SmartBridgeModel model;
    
    public SmartBridgeControllerImpl(final SmartBridgeView view, final String port) {
        this.view = view;
        model = new SmartBridgeModelArduino(this, port);
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
    public void setWaterTrendPoint(String trend) {
        // TODO Auto-generated method stub
        
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
    
}
