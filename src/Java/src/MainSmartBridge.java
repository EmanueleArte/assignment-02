import java.util.stream.Stream;

import jssc.SerialPortList;

public class MainSmartBridge {
    public static void main(String[] args) {
        String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}
        CommChannel channel = null;
        try {
            channel = new SerialCommChannel(Stream.of(portNames).filter(p -> p.contains("cu.usb")).findFirst().get(), 9600);
        } catch (Exception e1) {
            e1.printStackTrace();
        }	
		// CommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);	
		// CommChannel channel = new SerialCommChannel("/dev/cu.isi00-DevB",9600);	
		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		try {
            Thread.sleep(4000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
		System.out.println("Ready.");		

		
		while (true){
			System.out.println("Sending ping");
			channel.sendMsg("ping");
			String msg = null;
            try {
                msg = channel.receiveMsg();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
			System.out.println("Received: "+msg);		
			try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
		}
    }
}