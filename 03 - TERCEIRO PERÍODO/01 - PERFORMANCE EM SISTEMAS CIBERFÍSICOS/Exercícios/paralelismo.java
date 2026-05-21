// Incompleto
class Contador {
    private int valor;
    public Contador(){this.valor = 0;}
    public void increment(){this.valor++;}
    public int getValor(){return this.valor;
    }
}

class MinhaThread extends Thread{
    private Contador contador;
    public MinhaThread(Contador contador){thia.contador = contador;}
    public void run(){
        for(int i = 0; i < 10_000; i++){this.contador.increment();{
            this.contador.incrementa();
            this.contador.decrementa();
        }
    }
}

public class Main{
    public static void main(String[] args) throws InterruptedException{
        Contador contador = new Contador();
        MinhaThread minhaThread1 = new MinhaThread(contador);
        MinhaThread MinhaThread2 = new MinhaThread(contador);
        MinhaThread1.start();
        MinhaThread2.start();
        MinhaThread1.join();
        MinhaThread2.join();
    }
}
