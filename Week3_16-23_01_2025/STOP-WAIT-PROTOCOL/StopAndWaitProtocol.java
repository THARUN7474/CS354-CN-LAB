import java.util.Random;

class Sender {
    private final Random random = new Random();
    private final double lossProbability;

    Sender(double lossProbability) {
        this.lossProbability = lossProbability;
    }

    public boolean sendFrame(int seqNo) {
        System.out.println("Sender: Sending frame with sequence number " + seqNo);
        boolean isLost = random.nextDouble() < lossProbability;
        if (isLost) {
            System.out.println("Frame with sequence number " + seqNo + " lost during transmission.");
            return false;
        } else {
            System.out.println("Frame with sequence number " + seqNo + " delivered successfully.");
            return true;
        }
    }
}

class Receiver {
    private final Random random = new Random();
    private final double lossProbability;

    Receiver(double lossProbability) {
        this.lossProbability = lossProbability;
    }

    public boolean sendAcknowledgment(int expectedSeqNo) {
        System.out.println("Receiver: Sending acknowledgment for next expected sequence number " + expectedSeqNo);
        boolean isLost = random.nextDouble() < lossProbability;
        if (isLost) {
            System.out.println("Acknowledgment for next expected sequence number " + expectedSeqNo + " lost during transmission.");
            return false;
        } else {
            System.out.println("Acknowledgment for next expected sequence number " + expectedSeqNo + " delivered successfully.");
            return true;
        }
    }
}

public class StopAndWaitProtocol {
    public static void main(String[] args) {
        final double lossProbability = 0.5;
        Sender sender = new Sender(lossProbability);
        Receiver receiver = new Receiver(lossProbability);
        int seqNo = 0;

        while (true) {
            boolean isSent = sender.sendFrame(seqNo);
            if (isSent) {
                boolean ackReceived = receiver.sendAcknowledgment((seqNo + 1) % 2);
                if (ackReceived) {
                    seqNo = (seqNo + 1) % 2; // Toggle sequence number between 0 and 1
                }
            }
            try {
                Thread.sleep(1000); // Wait for 1 second before sending the next frame
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}