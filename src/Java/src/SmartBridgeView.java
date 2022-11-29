/**
 * Simple interface for a gui used as smart bridge view.
 */
public interface SmartBridgeView {
    
    /**
     * Start the gui.
     */
    void start();

    /**
     * Set the smart light state text.
     * 
     * @param state the state
     */
    void updateSmartLightStatus(boolean state);

    /**
     * Show the valve controller.
     */
    void showValveController();

    /**
     * Hide the valve controller.
     */
    void hideValveController();

    /**
     * Set the situation text.
     * 
     * @param situation the situation
     */
    void updateSituation(String situation);

    /**
     * Set the smart bridge controller.
     * 
     * @param controller the smart bridge controller
     */
    void setController(SmartBridgeController controller);

    /**
     * Set the program state label text.
     * 
     * @param state the program state
     */
    void setProgramState(String state);

    /**
     * Set on or off the remote control.
     * @param state if on the remote control is activated else it is deactivated
     */
    void setRemoteControl(boolean state);
}
