import java.util.stream.Stream;
import jssc.SerialPortList;

/**
 * SmartBridgeModel implementation.
 */
public class SmartBridgeModelImpl implements SmartBridgeModel {
    private final static String NORMAL = "Normal";
    private final static String PRE_ALARM = "Pre-alarm";
    private final static String ALARM = "Alarm";
    private final SmartBridgeController controller;
    private boolean smartLight;
    private String situation;
    private int valve;
    private CommChannel channel;

    public SmartBridgeModelImpl(final SmartBridgeController controller, final String port) {
        this.controller = controller;
        smartLight = false;
        situation = NORMAL;
        valve = 0;

        if (port.isEmpty()) {
            serialConnect();
        } else {
            serialConnect(port);
        }
    }

    @Override
    public void setValveOpening(final int opening) {
        valve = opening;

    }

    private void serialConnect() {
        try {
            String[] portNames = SerialPortList.getPortNames();
            channel = new SerialCommChannel(Stream.of(portNames)
                .filter(p -> p.contains("cu.usb") || p.contains("COM3"))
                .findFirst().get(), 9600);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void serialConnect(final String port) {
        try {
            channel = new SerialCommChannel(port,9600);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void rebootWaiting() {
        /* attesa necessaria per fare in modo che Arduino completi il reboot */
        System.out.println("Waiting Arduino for rebooting...");		
        Thread.sleep(4000);
        System.out.println("Ready.");
    }
    

}
