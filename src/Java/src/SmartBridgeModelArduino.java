import java.util.stream.Stream;

import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import jssc.SerialPortList;

/**
 * SmartBridgeModel implementation.
 */
public class SmartBridgeModelArduino implements SmartBridgeModel {
    private final static String NORMAL = "Normal";
    private final static String PRE_ALARM = "Pre-alarm";
    private final static String ALARM = "Alarm";
    private final static double MAX_WATER_LEVEL = 357.0;
    private final SmartBridgeController controller;
    private boolean smartLight;
    private String situation;
    private int valve;
    private CommChannel channel;
    private final XYSeriesCollection waterDataSet;
    private final XYSeries waterLevelData;
    private int dataIndex;

    private class ListenerThread extends Thread {

        @Override
        public void run() {
            while (true) {
                String msg = null;
                try {
                    msg = channel.receiveMsg();
                    msgCheck(msg);
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    public SmartBridgeModelArduino(final SmartBridgeController controller, final String port, final XYSeriesCollection dataSet) {
        this.controller = controller;
        smartLight = false;
        situation = NORMAL;
        valve = 0;
        dataIndex = 0;
        waterDataSet = dataSet;
        waterLevelData = new XYSeries("Water");
        waterDataSet.addSeries(waterLevelData);
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
        if (valve != opening) {
            valve = opening;
            channel.sendMsg(String.valueOf(valve));
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private void serialConnect() {
        try {
            String[] portNames = SerialPortList.getPortNames();
            //System.out.println("Available ports:");
            //Stream.of(portNames).forEach(System.out::println);
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
        // Smart light state update
        if (smartLight) {
            controller.setSmartLightOn();
        } else {
            controller.setSmartLightOff();
        }
        // Valve controller showing
        if (situation != ALARM) {
            controller.hideValveController();
        } else {
            controller.showValveController();
        }
        controller.setSituation(situation);
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
            case "RemoteControl-off":
                controller.setRemoteControl(false);
                break;
            default:
                addWaterData(msg);
                break;
        }
        updateInfo();
    }

    /**
     * Adds a new water level data point to the dataset.
     * 
     * @param msg the water data received from the Arduino
     */
    private void addWaterData(final String msg) {
        if (msg.matches("[0-9]+")) {
            waterLevelData.add(dataIndex++, MAX_WATER_LEVEL - Double.parseDouble(msg));
        }
    }

    @Override
    public void setRemoteControl(boolean state) {
        if (state) {
            // Remote control on
            channel.sendMsg("-1");
        } else {
            // Remote control off
            channel.sendMsg("-2");
        }
    }
    
}
