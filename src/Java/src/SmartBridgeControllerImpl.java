/**
 * SmartBridgeController implementation.
 */
public class SmartBridgeControllerImpl implements SmartBridgeController {
    private final SmartBridgeView view;
    private final SmartBridgeModel model;
    
    public SmartBridgeControllerImpl(SmartBridgeView view) {
        this.view = view;
        model = new SmartBridgeModelImpl();
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
    
}
