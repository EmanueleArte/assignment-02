import java.util.stream.Stream;
import jssc.SerialPortList;

/**
 * SmartBridgeModel implementation.
 */
public class SmartBridgeModelArduino implements SmartBridgeModel {
    private final static String NORMAL = "Normal";
    private final static String PRE_ALARM = "Pre-alarm";
    private final static String ALARM = "Alarm";
    private final SmartBridgeController controller;
    private boolean smartLight;
    private String situation;
    private int valve;
    private CommChannel channel;

    private class ListenerThread extends Thread {

        @Override
        public void run() {
            while (true) {
                String msg = null;
                try {
                    msg = channel.receiveMsg();
                    msgCheck(msg);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("Received: " + msg);
            }
        }

    }

    public SmartBridgeModelArduino(final SmartBridgeController controller, final String port) {
        this.controller = controller;
        smartLight = false;
        situation = NORMAL;
        valve = 0;
        updateInfo();

        if (port.isEmpty()) {
            serialConnect();
        } else {
            serialConnect(port);
        }
        Thread listener = new ListenerThread();
        listener.start();
    }

    @Override
    public void setValveOpening(final int opening) {
        valve = opening;

    }

    private void serialConnect() {
        try {
            String[] portNames = SerialPortList.getPortNames();
            System.out.println("Available ports:");
            Stream.of(portNames).forEach(System.out::println);
            channel = new SerialCommChannel(Stream.of(portNames)
                .filter(p -> p.contains("cu.usb") || p.contains("COM3"))
                .findFirst().get(), 9600);
        } catch (Exception e) {
            controller.setProgramState("Connection failed.");
            e.printStackTrace();
            return;
        }
        rebootWaiting();
    }

    private void serialConnect(final String port) {
        try {
            channel = new SerialCommChannel(port,9600);
        } catch (Exception e) {
            controller.setProgramState("Connection failed.");
            e.printStackTrace();
            return;
        }
        rebootWaiting();
    }

    private void rebootWaiting() {
        // Necessary wait to make sure that Arduino completes the reboot
        controller.setProgramState("Waiting Arduino for rebooting...");	
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        controller.setProgramState("Online.");
    }

    private void updateInfo() {
        if (smartLight) {
            controller.setSmartLightOn();
        } else {
            controller.setSmartLightOff();
        }
        if (situation != ALARM) {
            controller.hideValveController();
        } else {
            controller.showValveController();
        }
        controller.setSituation(situation);
        controller.setValveOpening(valve);
        //controller.setWaterTrendPoint("boh");
    }

    private void msgCheck(final String msg) {
        switch (msg) {
            case "SmartLight-on":
                smartLight = true;
                break;
            case "SmartLight-off":
                smartLight = false;
                break;
            case "Normal":
                situation = NORMAL;
                break;
            case "Pre-alarm":
                situation = PRE_ALARM;
                break;
            case "Alarm":
                situation = ALARM;
                break;
            default:
                // da completare con il water level
                break;
        }
        updateInfo();
    }
    
}
