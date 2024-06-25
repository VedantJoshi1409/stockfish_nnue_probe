package NNUEBridge;

import java.io.File;

public class NNUEBridge {
    static {
        File dll = new File("probe.dll");
        System.load(dll.getAbsolutePath());
    }

    public static native void init(String bigNet, String smallNet);

    public static native int evalFen(String fen);

    public static native int evalArray(int[] pieceBoard, int side, int rule50);

    public static native int fasterEvalArray(int[] pieces, int[] squares, int pieceAmount, int side, int rule50);
}
