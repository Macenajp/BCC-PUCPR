/*
class Conta{
    print double saldo;
    public Conta(){this.saldo = 0.0f;}
    public void deposita(double valor){this.saldo += valor;}
    public void saque(double valor){this.saldo -= valor;}
    public double getSaldo(){return this.saldo;}

}

class Deposita extends Thread{
    private Conta conta;
    public Deposita(Conta conta){this.conta = conta;}
    public void run(){
        Random random = new Random();

        while(true){
            double valor = random.nextDouble();
            this.conta.deposita(valor);
            System.out.println("DEPOSITA VALOR: " + valor + "SALDO: "+ this.conta.getSaldo());
            try{Thread.sleep(101);} catch (InterruptedException e) {throw new RuntimeException(e);}
        }

}

class Main{
    public static void main(String[] args) throws InterruptedException{

    }
}
*/


import java.util.Random;

class Conta{
    private double saldo;
    public Conta(){
        this.saldo = 0.0f;
    }
    public void deposita(double valor){
        this.saldo += valor;
    }
    public void saque(double valor){
        this.saldo -= valor;
    }
    public double getSaldo(){
        return this.saldo;
    }
}

class Deposita extends Thread{
    private final Conta conta;
    public Deposita(Conta conta){
        this.conta = conta;
    }
    public void run(){
        Random random = new Random();
        while(true){
            double valor = random.nextDouble();
            this.conta.deposita(valor);
            System.out.println(" DEPOSITA VALOR: " + valor + " SALDO: " + this.conta.getSaldo());
            try {
                Thread.sleep(10l);
            }
            catch (InterruptedException e){
                throw new RuntimeException(e);
            }
        }
    }
}

class Saque extends Thread{
    private Conta conta;
    public Saque(Conta conta){
        this.conta = conta;
    }
    
    public void run(){
        Random random = new Random();
        while(true){
            double valor = random.nextDouble();
            if (this.conta.getSaldo() >= valor) {
                this.conta.saque(valor);
                System.out.println(" SACA VALOR: " + valor + " SALDO: " + this.conta.getSaldo());
                try {
                    Thread.sleep(10l);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }
}

public class Main{
    public static void main (String[] args) throws InterruptedException{
        Conta conta = new Conta();
        Deposita deposita = new Deposita(conta);
        Deposita deposita1 = new Deposita(conta);
        Saque saque = new Saque(conta);
        Saque saque1 = new Saque(conta);
        Saque saque2 = new Saque(conta);
        deposita.start();
        deposita1.start();
        saque.start();
        saque1.start();
        saque2.start();
    }
}
