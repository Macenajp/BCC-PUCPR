interface IForma {
    int CalcularArea();
}



class Retangulo implements IForma {
    private int altura;
    private int largura;

    public Retangulo(int altura, int largura) {
        this.altura = altura;
        this.largura = largura;
    }

    public int CalcularArea() {
        return altura * largura;
    }
}



class Triangulo implements IForma {
    private int altura;
    private int largura;

    public Triangulo(int altura, int largura) {
        this.altura = altura;
        this.largura = largura;
    }

    public int CalcularArea() {
        return (altura * largura) / 2;
    }
}



public class exercícioAvançado03 {
    public static void main(String[] args) {
        IForma ret = new Retangulo(10, 5);
        IForma tri = new Triangulo(10, 5);

        System.out.println("Área Retângulo (Interface): " + ret.CalcularArea());
        System.out.println("Área Triângulo (Interface): " + tri.CalcularArea());
    }
}
