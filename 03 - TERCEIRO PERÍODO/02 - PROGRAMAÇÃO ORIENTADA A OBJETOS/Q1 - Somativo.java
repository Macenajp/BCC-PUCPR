// Este código está completo, mas para seu uso, é necessário os outros arquivos complementares. O objetivo disso, era ler, entender o que estava faltando e implementar.
import java.util.ArrayList;

public class Agrupador {
    private static final int ano_minimo_geracao_X = 1965;
    private static final int ano_maximo_geracao_X = 1980;
    private static final int ano_minimo_geracao_Y = 1981;
    private static final int ano_maximo_geracao_Y = 1995;
    private static final int ano_minimo_geracao_Z = 1996;
    private static final int ano_maximo_geracao_Z = 2012;

// Para esses três tópicos, foi preciso adicionar tudo desde o "ArryList" de "pessoas_da_geracao_X" até o fechamento da chave, resumidamente, da linha 14 até a 24.
    public static ArrayList<Pessoa> agrupar_geracao_X(ArrayList<Pessoa> base_de_pessoas) {
        ArrayList<Pessoa> pessoas_da_geracao_X = new ArrayList<>();

        for (Pessoa p : base_de_pessoas) {
            if (p.nascida_entre(ano_minimo_geracao_X, ano_maximo_geracao_X)) {
                pessoas_da_geracao_X.add(p);
            }
        }

        System.out.println(pessoas_da_geracao_X);
		return pessoas_da_geracao_X;
    }

// Este e o próximo foram basicamentre a mesma coisa que o anterior, mas, corrigidos para seus usos, agrupar a geração Y e [...]
    public static ArrayList<Pessoa> agrupar_geracao_Y(ArrayList<Pessoa> base_de_pessoas) {
        ArrayList<Pessoa> pessoas_da_geracao_Y = new ArrayList<>();

        for (Pessoa p : base_de_pessoas) {
            if (p.nascida_entre(ano_minimo_geracao_Y, ano_maximo_geracao_Y)) {
                pessoas_da_geracao_Y.add(p);
            }
        }

        System.out.println(pessoas_da_geracao_Y);
		return pessoas_da_geracao_Y;
    }

// [...] Agrupar a geração Z:
    public static ArrayList<Pessoa> agrupar_geracao_Z(ArrayList<Pessoa> base_de_pessoas) {
        ArrayList<Pessoa> pessoas_da_geracao_Z = new ArrayList<>();
        
        for (Pessoa p : base_de_pessoas) {
            if (p.nascida_entre(ano_minimo_geracao_Z, ano_maximo_geracao_Z)) {
                pessoas_da_geracao_Z.add(p);
            }
        }

        System.out.println(pessoas_da_geracao_Z);
		return pessoas_da_geracao_Z;
    }
}
