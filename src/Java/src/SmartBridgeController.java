/**
 * Interface for a smart bridge controller.
 */
public interface SmartBridgeController {

    /**
     * Set the grade of opening of the valve.
     * 
     * @param opening the grade of opening
     */
    void setValveOpening(int opening);

    /**
     * Set the smart light label text to ON.
     */
    void setSmartLightOn();

    /**
     * Set the smart light label text to OFF.
     */
    void setSmartLightOff();

    /**
     * Show the valve controller.
     */
    void showValveController();

    /**
     * Hide the valve controller.
     */
    void hideValveController();

    /**
     * Set the situation label to the chosen one.
     * 
     * @param situation the chosen situation
     */
    void setSituation(String situation);

    /**
     * Set the program state label text.
     * 
     * @param state the program state
     */
    void setProgramState(String state);

    /**
     * Set on or off the remote control.
     * 
     * @param state if on the remote control is activated else it is deactivated
     */
    void setRemoteControl(boolean state);
    
}
