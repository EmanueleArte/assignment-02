/**
 * Interface for a smart bridge model.
 */
public interface SmartBridgeModel {

    /**
     * Set the grade of opening of the valve.
     * 
     * @param opening the grade of opening
     */
    void setValveOpening(int opening);

    /**
     * Set the remote control state.
     * 
     * @param state if on the remote control is activated else it is deactivated
     */
    void setRemoteControl(boolean state);

}
