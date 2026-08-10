interface IForma {
    int CalcularArea();
}



class Retangulo implements IForma {
    protected int altura;
    protected int largura;

    public Retangulo(int altura, int largura) {
        this.altura = altura;
        this.largura = largura;
    }

    public int CalcularArea() {
        return altura * largura;
    }
}



class Triangulo extends Retangulo {
    public Triangulo(int altura, int largura) {
        super(altura, largura);
    }

    public int CalcularArea() {
        return super.CalcularArea() / 2;
    }
}



public class exercícioAvançado04 {
    public static void main(String[] args) {
        Retangulo ret = new Retangulo(10, 5);
        Triangulo tri = new Triangulo(10, 5);

        System.out.println("Área Retângulo (Herança): " + ret.CalcularArea());
        System.out.println("Área Triângulo (Chamando Super/2): " + tri.CalcularArea());
    }
}
