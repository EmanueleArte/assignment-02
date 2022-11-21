/**
 * SmartBridgeModel implementation.
 */
public class SmartBridgeModelImpl implements SmartBridgeModel {
    private final static String NORMAL = "Normal";
    private final static String PRE_ALARM = "Pre-alarm";
    private final static String ALARM = "Alarm";
    private final SmartBridgeController controller;
    private final boolean smartLight;
    private final String situation;
    private final int valve;

    public SmartBridgeModelImpl(SmartBridgeController controller) {
        this.controller = controller;
        smartLight = false;
        situation = NORMAL;
        valve = 0;
    }

    @Override
    public void setValveOpening(final int opening) {
        valve = opening;
        
    }
    

}
