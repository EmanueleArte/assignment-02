import java.util.stream.Stream;

import jssc.SerialPortList;

public class MainSmartBridge {
    public static void main(String[] args) throws Exception {
        System.out.println(">>> If the program doesn't work or you want to connect to a specific port, pass it as argument.");
        final SmartBridgeView gui = new SwingGui();
        if (args.length == 1) {
            final SmartBridgeController controller = new SmartBridgeControllerImpl(gui, args[0]);
        } else {
            
            	

            while (true){
                System.out.println("Sending ping");
                channel.sendMsg("ping");
                String msg = channel.receiveMsg();
                System.out.println("Received: "+msg);		
                Thread.sleep(500);
            }*/
            final SmartBridgeController controller = new SmartBridgeControllerImpl(gui, "");
        }
        gui.start();
    }
}