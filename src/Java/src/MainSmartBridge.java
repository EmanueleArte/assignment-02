/**
 * The class to run the SmartBridge application.
 */
public class MainSmartBridge {
    public static void main(String[] args) throws Exception {
        System.out.println(">>> If the program doesn't work or you want to connect to a specific port, pass it as argument.");
        final SmartBridgeView gui = new SwingGui();
        gui.start();
        if (args.length == 1) {
            new SmartBridgeControllerImpl(gui, args[0]);
        } else {
            new SmartBridgeControllerImpl(gui, "");
        }
    }
}