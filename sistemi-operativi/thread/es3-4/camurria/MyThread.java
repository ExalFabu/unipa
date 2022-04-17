package camurria;
import java.util.Random;
public class MyThread extends Thread{
    public static final int MAX = 10;

    private int[] generated;
    private int offset, range;
    public MyThread(boolean generateNumber){
        if (generateNumber){
            this.offset = 0;
            this.range = 9;
        }
        else{
            this.offset = (int) 'a';
            this.range = (int) 'z' - (int) 'a';
        }
        this.generated = new int[MAX];
    }

    @Override
    public void run(){
        Random randr = new Random();
        for (int i = 0; i < generated.length; i++) {
            generated[i] = randr.nextInt(range) + offset;
        }
        
    }
    public int[] getGenerated() {
        return generated;
    }
}
