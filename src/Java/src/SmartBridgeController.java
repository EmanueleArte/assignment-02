/**
 * Interface for a smart bridge controller.
 */
public interface SmartBridgeController {

    /**
     * Set the grade of opening of the valve
     * .
     * @param opening the grade of opening
     */
    void setValveOpening(int opening);

    /**
     * Set the smart light label to ON.
     */
    void setSmartLightOn();

    /**
     * Set the smart light label to OFF.
     */
    void setSmartLightOff();

    /**
     * Set the situation label to the chosen one.
     * 
     * @param situation the chosen situation
     */
    void setSituation(String situation);

    /**
     * Set a new point into the water trend.
     * 
     * @param trend the new point
     */
    void setWaterTrendPoint(String trend);

}
