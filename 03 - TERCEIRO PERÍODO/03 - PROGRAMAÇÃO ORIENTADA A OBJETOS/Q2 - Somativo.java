// Este código está completo, mas para seu uso, é necessário os outros arquivos complementares. O objetivo disso, era ler, entender o que estava faltando e implementar.
import java.util.ArrayList;

class Tradutor {
    private ArrayList<Equivalencia> dicionario;

    public Tradutor() { dicionario = new ArrayList<Equivalencia>(); }
    
    public void aprender(String termo_portugues, String termo_ingles) {
        dicionario.add(new Equivalencia(termo_portugues, termo_ingles));
    }

  
// Alterado e corrigido:
    public String traduzir_para_portugues(String termo) {
        try {
            int k = localizar_ingles(termo);
            assert k >= 0 && k < dicionario.size();
            return dicionario.get(k).para_portugues();
        } catch (Throwable e) {
            return "--TERMO INGLÊS DESCONHECIDO--";
        }
    }

// Alterado e corrigido:
    public String traduzir_para_ingles(String termo) {
        try {
            int k = localizar_portugues(termo);
            assert k >= 0 && k < dicionario.size();
            return dicionario.get(k).para_ingles();
        } catch (Throwable e) {
            return "--TERMO PORTUGUÊS DESCONHECIDO--";
        }
    }


  
    private int localizar_portugues(String termo) {
        int local = 0;
        while (local < dicionario.size() && !dicionario.get(local).entrada_portugues(termo))
            local++;
        return local;
    }
  
    private int localizar_ingles(String termo) {
        int local = 0;
        while (local < dicionario.size() && !dicionario.get(local).entrada_ingles(termo))
            local++;
        return local;
    }
}
