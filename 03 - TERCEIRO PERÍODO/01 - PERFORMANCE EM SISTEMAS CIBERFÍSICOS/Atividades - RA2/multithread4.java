import java.util.Random;

class AtvThread extends Thread {
    private final Random random = new Random();
    public double[] numeros;
    private final int inicio;
    private final int fim;

    public AtvThread(double[] numeros, int inicio, int fim) {
        this.numeros = numeros;
        this.inicio = inicio;
        this.fim = fim;
    }

    public void run() {
        for (int i = this.inicio; i < this.fim; i++) {
            this.numeros[i] = random.nextDouble();
        }
    }
}

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int tamanho = 200_000_000;
        double[] numeros = new double[tamanho];
        
        AtvThread t1 = new AtvThread(numeros, 0, 50_000_000);
        AtvThread t2 = new AtvThread(numeros, 50_000_000, 100_000_000);
        AtvThread t3 = new AtvThread(numeros, 100_000_000, 150_000_000);
        AtvThread t4 = new AtvThread(numeros, 150_000_000, 200_000_000);
        
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        System.out.println("Encerrou inicalizacao");

        int valores = 0;
        for (int i = 0; i < numeros.length; i++) {
            double numero = numeros[i];
            if (numero > 0.25 && numero < 0.75) {
                valores++;
            }
        }
        
        System.out.println(valores);
    }
}
