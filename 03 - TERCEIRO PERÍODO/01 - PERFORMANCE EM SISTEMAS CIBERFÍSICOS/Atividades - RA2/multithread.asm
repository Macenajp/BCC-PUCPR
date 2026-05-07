class MinhaThread extends Thread{
    public void run(){
        System.out.println("Começo");
        try{
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("Fim");
    }
}

public class Main {
    public static void main(String[] args){
        System.out.println("Começo main");
        MinhaThread thread1 = new MinhaThread();
        thread1.start();
        System.out.println("Fim main");
    }
}
