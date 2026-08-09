import java.util.ArrayList;
import java.util.List;



class Pais {
    private String codigoIso;
    private String nome;
    private long populacao;
    private double dimensao;
    private List<Pais> vizinhos;

    public Pais(String codigoIso, String nome, double dimensao) {
        this.codigoIso = codigoIso;
        this.nome = nome;
        this.dimensao = dimensao;
        this.vizinhos = new ArrayList<>();
    }

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

    public boolean isMesmoPais(Pais outroPais) {
        if (outroPais == null) return false;
        return this.codigoIso.equals(outroPais.getCodigoIso());
    }

    public boolean isVizinho(Pais outroPais) {
        return this.vizinhos.contains(outroPais);
    }

    public void adicionarVizinho(Pais vizinho) {
        if (!this.vizinhos.contains(vizinho) && !this.isMesmoPais(vizinho)) {
            this.vizinhos.add(vizinho);
        }
    }

    public double densidadePopulacional() {
        if (this.dimensao == 0) return 0;
        return this.populacao / this.dimensao;
    }

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



class Continente {
    private String nome;
    private List<Pais> paises;

    // Construtor que inicializa o nome do continente
    public Continente(String nome) {
        this.nome = nome;
        this.paises = new ArrayList<>();
    }

    // Aqui permite o acréscimo de países no continente
    public void adicionarPais(Pais pais) {
        if (!this.paises.contains(pais)) {
            this.paises.add(pais);
        }
    }

    // Aqui retorna a dimensão total do continente
    public double dimensaoTotal() {
        double total = 0;
        for (Pais p : paises) {
            total += p.getDimensao();
        }
        return total;
    }

    // Retorna a população total do continente
    public long populacaoTotal() {
        long total = 0;
        for (Pais p : paises) {
            total += p.getPopulacao();
        }
        return total;
    }

    // Retorna a densidade populacional do continente
    public double densidadePopulacional() {
        double dim = dimensaoTotal();
        if (dim == 0) return 0;
        return populacaoTotal() / dim;
    }

    // Retorna o país com maior população no continente
    public Pais paisMaiorPopulacao() {
        if (paises.isEmpty()) return null;
        Pais maior = paises.get(0);
        for (Pais p : paises) {
            if (p.getPopulacao() > maior.getPopulacao()) {
                maior = p;
            }
        }
        return maior;
    }

    // Retorna o país com menor população no continente
    public Pais paisMenorPopulacao() {
        if (paises.isEmpty()) return null;
        Pais menor = paises.get(0);
        for (Pais p : paises) {
            if (p.getPopulacao() < menor.getPopulacao()) {
                menor = p;
            }
        }
        return menor;
    }

    // Retorna o país de maior dimensão territorial no continente
    public Pais paisMaiorDimensao() {
        if (paises.isEmpty()) return null;
        Pais maior = paises.get(0);
        for (Pais p : paises) {
            if (p.getDimensao() > maior.getDimensao()) {
                maior = p;
            }
        }
        return maior;
    }

    // Retorna o país de menor dimensão territorial no continente
    public Pais paisMenorDimensao() {
        if (paises.isEmpty()) return null;
        Pais menor = paises.get(0);
        for (Pais p : paises) {
            if (p.getDimensao() < menor.getDimensao()) {
                menor = p;
            }
        }
        return menor;
    }

    // Retorna a razão territorial do maior país em relação ao menor país
    public double razaoTerritorial() {
        Pais maior = paisMaiorDimensao();
        Pais menor = paisMenorDimensao();
        if (maior != null && menor != null && menor.getDimensao() > 0) {
            return maior.getDimensao() / menor.getDimensao();
        }
        return 0;
    }
}



public class exercícioSimples03 {
    public static void main(String[] args) {
        Continente americaDoSul = new Continente("América do Sul");

        Pais brasil = new Pais("BRA", "Brasil", 8515767.049);
        brasil.setPopulacao(202768562);

        Pais uruguai = new Pais("URY", "Uruguai", 176215.0);
        uruguai.setPopulacao(3400000);

        americaDoSul.adicionarPais(brasil);
        americaDoSul.adicionarPais(uruguai);

        System.out.println("População total: " + americaDoSul.populacaoTotal());
        System.out.println("País de maior dimensão: " + americaDoSul.paisMaiorDimensao().getNome());
        System.out.println("Razão territorial (Maior/Menor): " + americaDoSul.razaoTerritorial());
    }
}
