// Arrumar:
class MinhaThread extends Thread {
    private String none;
    public MinhaThread(String none) {
        this.none = none;
    }
    public void run() {
        System.out.printl(this.none);
    }
}


public class Main {
    public static void main(String[] args) throws InterruptedException{
    MinhaThread thread1 = new MinhaThread("thread1");
    MinhaThread thread2 = new MinhaThread("thread2");
    thread1.start();
    thread1.join();
    thread2.start();
    thread2.start();
    System.out.println("Fim do Main");
    }
}
