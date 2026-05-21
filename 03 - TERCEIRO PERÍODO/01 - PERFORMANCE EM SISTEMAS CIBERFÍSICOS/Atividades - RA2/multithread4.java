// Vetor Multithreading:
import java.util.Random;

class AtvThread extends Thread {
    private final Random random = new Random();
    public double[] numeros;
    private final int inicio;
    private final int fim;

    public AtvThread(double[] numeros, int i, int i1) {
        this.numeros = numeros;
        this.inicio = i;
        this.fim = i1;
    }

    public void run() {
        try {
            Thread.sleep(10);
            for (int i = this.inicio; i < this.fim; i ++) {
                this.numeros[i] = random.nextDouble();
            }
        } catch (InterruptedException exception) {
            throw new RuntimeException("Erro");
        }
    }
}

public class Main {
    public static void main(String[] args) throws InterruptedException {
        double[] numeros = new double[2000000];
        int valores = 0;
        AtvThread AtvThread1 = new AtvThread(numeros, 0, 500000);
        AtvThread AtvThread2 = new AtvThread(numeros, 500000, 1000000);
        AtvThread AtvThread3 = new AtvThread(numeros, 1000000, 1500000);
        AtvThread AtvThread4 = new AtvThread(numeros, 1500000, 2000000);
        AtvThread1.start();
        AtvThread2.start();
        AtvThread3.start();
        AtvThread4.start();
        AtvThread1.join();
        AtvThread2.join();
        AtvThread3.join();
        AtvThread4.join();

        for (int i = 0; i < numeros.length; i++){
            Double numero = numeros[i];
            if (numero > 0.25 && numero < 0.75) {
                valores += 1;
            }
        }
        System.out.println(valores);
        System.out.println("Encerrou a inicialização");
    }
}
