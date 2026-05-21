import java.util.Random;

class InicializaThread extends Thread {
    private double[] vetorMultithread;

    public InicializaThread(double[] vetorMultithread) {
        this.vetorMultithread = vetorMultithread;
    }

    public void run() {
        Random rand = new Random();
        for (int i = 0; i < vetorMultithread.length; i++) {
            vetorMultithread[i] = rand.nextDouble();
        }
    }
}

class ComputaThread extends Thread {
    private double[] vetorMultithread;
    private int quantidade;

    public ComputaThread(double[] vetorMultithread) {
        this.vetorMultithread = vetorMultithread;
        this.quantidade = 0;
    }

    public void run() {
        for (int i = 0; i < vetorMultithread.length; i++) {
            if (vetorMultithread[i] > 0.25 && vetorMultithread[i] < 0.75) {
                quantidade++;
            }
        }
    }

    public int getQuantidade() {
        return quantidade;
    }
}

public class Main {
    public static void main(String[] arg) throws InterruptedException {
        double[] vetorMultithread = new double[200000000];

        long inicio = System.currentTimeMillis();

        InicializaThread threadInicializacao = new InicializaThread(vetorMultithread);
        threadInicializacao.start();
        threadInicializacao.join();

        System.out.println("Encerrou inicalizacao");

        ComputaThread threadComputacao = new ComputaThread(vetorMultithread);
        threadComputacao.start();
        threadComputacao.join();

        System.out.println(threadComputacao.getQuantidade());

        long fim = System.currentTimeMillis();
        long duração = (fim - inicio);
        System.out.println(duração);
    }
}
