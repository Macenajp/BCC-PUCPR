import java.util.ArrayList;
import java.util.List;

class Pais {
    private String codigoIso;
    private String nome;
    private long populacao;
    private double dimensao;
    private List<Pais> vizinhos;



    // Construtor que inicializa:
    public Pais(String codigoIso, String nome, double dimensao) {
        this.codigoIso = codigoIso;             // O código ISO,
        this.nome = nome;                       // o nome,
        this.dimensao = dimensao;               // e também a dimensão
        this.vizinhos = new ArrayList<>();
    }



    // Métodos de acesso (Getters e Setters)
    public String getCodigoIso() { return codigoIso; }
    public void setCodigoIso(String codigoIso) { this.codigoIso = codigoIso; }

    public String getNome() { return nome; }
    public void setNome(String nome) { this.nome = nome; }

    public long getPopulacao() { return populacao; }
    public void setPopulacao(long populacao) { this.populacao = populacao; }

    public double getDimensao() { return dimensao; }
    public void setDimensao(double dimensao) { this.dimensao = dimensao; }

    public List<Pais> getVizinhos() { return vizinhos; }
    public void setVizinhos(List<Pais> vizinhos) { this.vizinhos = vizinhos; }

    // Verifica se dois objetos representam o mesmo país pelo código ISO
    public boolean isMesmoPais(Pais outroPais) {
        if (outroPais == null) return false;
        return this.codigoIso.equals(outroPais.getCodigoIso());
    }

    // Informa se outro país é vizinho
    public boolean isVizinho(Pais outroPais) {
        return this.vizinhos.contains(outroPais);
    }

    public void adicionarVizinho(Pais vizinho) {
        if (!this.vizinhos.contains(vizinho) && !this.isMesmoPais(vizinho)) {
            this.vizinhos.add(vizinho);
        }
    }

    // Aqui retorna a densidade populacional
    public double densidadePopulacional() {
        if (this.dimensao == 0) return 0;
        return this.populacao / this.dimensao;
    }

    // Vai retornar uma lista de vizinhos comuns aos dois países
    public List<Pais> vizinhosComuns(Pais outroPais) {
        List<Pais> comuns = new ArrayList<>();
        for (Pais vizinho : this.vizinhos) {
            if (outroPais.isVizinho(vizinho)) {
                comuns.add(vizinho);
            }
        }
        return comuns;
    }
}



public class exercicioSimples02 {
    public static void main(String[] args) {
        Pais brasil = new Pais("BRA", "Brasil", 8515767.049);
        brasil.setPopulacao(202768562);

        Pais argentina = new Pais("ARG", "Argentina", 2780400.0);
        Pais uruguai = new Pais("URY", "Uruguai", 176215.0);

        brasil.adicionarVizinho(argentina);
        brasil.adicionarVizinho(uruguai);
        argentina.adicionarVizinho(brasil);
        argentina.adicionarVizinho(uruguai);

        System.out.println("Densidade BR: " + brasil.densidadePopulacional());
        System.out.println("São vizinhos comuns (BR e ARG): " + brasil.vizinhosComuns(argentina).get(0).getNome());
    }
}
