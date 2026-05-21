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

    @Override
    public void run() {
        // Removido o Thread.sleep() para não prejudicar a performance
        for (int i = this.inicio; i < this.fim; i++) {
            this.numeros[i] = random.nextDouble();
        }
    }
}

public class Main {
    public static void main(String[] args) throws InterruptedException {
        // 1. Aloca um vetor double com 200 milhões de entradas
        // Dica: Usar underscores (_) facilita a leitura de números grandes no Java
        int tamanho = 200_000_000;
        double[] numeros = new double[tamanho];
        
        // Dividindo 200 milhões entre 4 threads (50 milhões cada)
        AtvThread t1 = new AtvThread(numeros, 0, 50_000_000);
        AtvThread t2 = new AtvThread(numeros, 50_000_000, 100_000_000);
        AtvThread t3 = new AtvThread(numeros, 100_000_000, 150_000_000);
        AtvThread t4 = new AtvThread(numeros, 150_000_000, 200_000_000);
        
        // 2. Inicializa o vetor
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // 3. Após inicialização exibe a mensagem (Exatamente como o enunciado pede)
        System.out.println("Encerrou inicalizacao");

        // 4. Computa os valores (Mantido na thread principal para simplificar, como no seu código)
        int valores = 0;
        for (int i = 0; i < numeros.length; i++) {
            // Usando tipo primitivo "double" ao invés do objeto "Double" para melhor performance
            double numero = numeros[i];
            if (numero > 0.25 && numero < 0.75) {
                valores++;
            }
        }
        
        // Exibe a quantidade computada
        System.out.println("Quantidade de valores encontrados: " + valores);
    }
}
