abstract class Forma {
    protected int altura;
    protected int largura;

    public Forma(int altura, int largura) {
        this.altura = altura;
        this.largura = largura;
    }

    abstract public int CalcularArea();
}



class Retangulo extends Forma {
    public Retangulo(int altura, int largura) {
        super(altura, largura);
    }

    public int CalcularArea() {
        return altura * largura;
    }
}



class Triangulo extends Forma {
    public Triangulo(int altura, int largura) {
        super(altura, largura);
    }

    public int CalcularArea() {
        return (altura * largura) / 2;
    }
}



public class exercícioAvançado02 {
    public static void main(String[] args) {
        Forma ret = new Retangulo(10, 5);
        Forma tri = new Triangulo(10, 5);

        System.out.println("Área Retângulo: " + ret.CalcularArea());
        System.out.println("Área Triângulo: " + tri.CalcularArea());
    }
}
