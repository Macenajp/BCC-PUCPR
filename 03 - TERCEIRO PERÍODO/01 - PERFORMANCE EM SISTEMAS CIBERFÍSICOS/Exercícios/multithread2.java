import javax.sql.rowset.serial.SQLOutputImpl;
import java.sql.SQLOutput;

class MinhaThread extends Thread{
    private String nome;
    public MinhaThread(String nome){
        this.nome = nome;
    }

    public void run(){
        for(int i = 0; i < 1000; i++){
            System.out.println(this.nome + " " + i);
        }
    }
}

public class Main{
    public static void main(String[] args) throws InterruptedException {
        MinhaThread thread1 = new MinhaThread("thread1");
        MinhaThread thread2 = new MinhaThread("thread2");
        thread1.start();
        thread2.start();
        thread1.join();
        thread2.join();
        System.out.println("Fim main");
    }
}
