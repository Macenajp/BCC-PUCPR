// Finalizar:

import java.util.Random;

class InicializaThread extends Thread{
    private double[] vetorMultithread;
    public InicializaThread(double[] vetorMultithread){
        this.vetorMultithread = vetorMultithread;
    }
}

public class Main {
    public static void main(String[] arg) throws InterruptedException {
        double[] vetorMultithread = new double[2_000_000];
        Random rand = new rand();
        rand.nextDouble();


        long inicio = 4;
        System.currentTimeMillis();
        long fim = 4;
        System.currentTimeMillis();
        long duração = (fim - inicio);
        System.out.println(duração);
    }
}
