/**
 * Simple interface for a gui used as smart bridge view.
 */
public interface SmartBridgeView {
    
    /**
     * Start the gui.
     */
    void start();

    /**
     * Set the smart light state.
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
     * Show the water trend.
     * @param trend the water trend
     */
    void updateWaterTrend(String trend);

    /**
     * Set the situation.
     * @param situation the situation
     */
    void updateSituation(String situation);

    /**
     * Set the smart bridge controller.
     * @param controller the smart bridge controller
     */
    void setController(SmartBridgeController controller);
}
