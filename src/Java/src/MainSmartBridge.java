import java.util.stream.Stream;

import jssc.SerialPortList;

public class MainSmartBridge {
    public static void main(String[] args) throws Exception {
        SmartBridgeView gui = new SwingGui();
        gui.start();
        if (args.length == 0) {
            CommChannel channel = new SerialCommChannel(args[0],9600);
        } else {
            String[] portNames = SerialPortList.getPortNames();
            // try to open the serial port automatically
            CommChannel channel = new SerialCommChannel(Stream.of(portNames).filter(p -> p.contains("cu.usb") || p.contains("COM3"))
            .findFirst().get(), 9600);
            // CommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);	
            // CommChannel channel = new SerialCommChannel("/dev/cu.isi00-DevB",9600);	
            
            /* attesa necessaria per fare in modo che Arduino completi il reboot */
            System.out.println("Waiting Arduino for rebooting...");		
            Thread.sleep(4000);
            System.out.println("Ready.");		

            while (true){
                System.out.println("Sending ping");
                channel.sendMsg("ping");
                String msg = channel.receiveMsg();
                System.out.println("Received: "+msg);		
                Thread.sleep(500);
            }
        }
    }
}