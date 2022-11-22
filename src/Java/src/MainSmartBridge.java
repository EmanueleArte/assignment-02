import org.jfree.data.xy.XYSeriesCollection;

/**
 * The class to run the SmartBridge application.
 */
public class MainSmartBridge {
    public static void main(String[] args) throws Exception {
        System.out.println(">>> If the program doesn't work or you want to connect to a specific port, pass it as argument.");
        final XYSeriesCollection dataSet = new XYSeriesCollection();
        final SmartBridgeView gui = new SwingGui(dataSet);
        gui.start();
        if (args.length == 1) {
            gui.setController(new SmartBridgeControllerImpl(gui, args[0], dataSet));
        } else {
            gui.setController(new SmartBridgeControllerImpl(gui, "", dataSet));
        }
    }
}