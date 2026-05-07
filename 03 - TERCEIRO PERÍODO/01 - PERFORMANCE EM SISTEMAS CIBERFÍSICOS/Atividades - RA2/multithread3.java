import javax.sql.rowset.serial.SQLOutputImpl;
import java.sql.SQLOutput;

class MinhaThread extends Thread{
    public MinhaThread(String exemplo) {
    }

    public void run(){
        System.out.println("Bem vindo");
        try{
            Thread.sleep(5000);

        } catch (InterruptedException a){
            throw new RuntimeException();
        }
        System.out.println("Adeus");
    }
}

public class Main{
    public static void main(String[] args) throws InterruptedException {

        MinhaThread exemplo = new MinhaThread("exemplo");
        exemplo.start();
        exemplo.join();
        System.out.println("Fim do programa");
    }
}
