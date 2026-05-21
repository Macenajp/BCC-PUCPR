// Falta finalizar:

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
