class Data {
    private int dia;
    private int mes;
    private int ano;
    private String formato;

    public Data(int dia, int mes, int ano) {
        setAno(ano);
        setMes(mes);
        setDia(dia);
        this.formato = "dd/mm/aaaa";
    }

    public void setDia(int dia) {
        if (dia >= 1 && dia <= 31) {
            this.dia = dia;
        } else {
            this.dia = 1;
        }
    }

    public void setMes(int mes) {
        if (mes >= 1 && mes <= 12) {
            this.mes = mes;
        } else {
            this.mes = 1;
        }
    }

    public void setAno(int ano) {
        if (ano > 0) {
            this.ano = ano;
        } else {
            this.ano = 1;
        }
    }

    public void DefinirFormato(String formato) {
        this.formato = formato;
    }

    public void Imprimir() {
        String fDia = "", fMes = "", fAno = "";

        // Aqui serve para descobrir quantos d, m, e a existem no formato
        for (char c : formato.toCharArray()) {
            if (c == 'd') fDia += "d";
            else if (c == 'm') fMes += "m";
            else if (c == 'a') fAno += "a";
        }

        String resultado = formato;

        // Substitui os caracteres pelas strings já formatadas com a quantidade certa de zeros
        if (!fDia.isEmpty()) resultado = resultado.replace(fDia, formatarComZeros(dia, fDia.length()));
        if (!fMes.isEmpty()) resultado = resultado.replace(fMes, formatarComZeros(mes, fMes.length()));
        if (!fAno.isEmpty()) resultado = resultado.replace(fAno, formatarComZeros(ano, fAno.length()));

        System.out.println(resultado);
    }

    // Já aqui, auxilia o preenchimento de zeros à esquerda, se necessário
    private String formatarComZeros(int valor, int qtdCaracteres) {
        String texto = String.valueOf(valor);
        while (texto.length() < qtdCaracteres) {
            texto = "0" + texto;
        }
        return texto;
    }
}

public class exercícioAvançado01 {
    public static void main(String[] args) {
        Data d = new Data(1, 8, 2017);

        d.DefinirFormato("dd/mm/aaaa");
        d.Imprimir();

        d.DefinirFormato("dddd/m/aaaa");
        d.Imprimir();

        d.DefinirFormato("d:m:aa");
        d.Imprimir();

        d.DefinirFormato("aaa/m/d");
        d.Imprimir();
    }
}
