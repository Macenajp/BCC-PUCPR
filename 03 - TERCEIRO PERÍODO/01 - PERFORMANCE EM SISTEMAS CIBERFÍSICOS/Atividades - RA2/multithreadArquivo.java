import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class ContarCaracterePasta {
    private static final String caminho = "C:/Users/macena.joao/Downloads/amostra/amostra"; // <-- altere para o seu caminho
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in, StandardCharsets.UTF_8);

        System.out.print("Digite o caractere que deseja contar: ");
        String caractereStr = entrada.nextLine();

        if (caractereStr.codePointCount(0, caractereStr.length()) != 1) {
            System.out.println("Por favor, digite apenas UM caractere.");
            entrada.close();
            return;
        }

        int caractereAlvo = caractereStr.codePointAt(0); // suporta Unicode
        int contadorTotal = 0;

        File pasta = new File(caminho);

        if (!pasta.exists() || !pasta.isDirectory()) {
            System.out.println("O caminho informado não é uma pasta válida.");
            entrada.close();
            return;
        }

        File[] arquivosTxt = pasta.listFiles((dir, nome) -> nome.toLowerCase().endsWith(".txt"));

        if (arquivosTxt == null || arquivosTxt.length == 0) {
            System.out.println("Nenhum arquivo .txt encontrado.");
            entrada.close();
            return;
        }

        for (File arquivo : arquivosTxt) {
            int contadorArquivo = 0;
            try (BufferedReader br = new BufferedReader(
                    new InputStreamReader(new FileInputStream(arquivo), StandardCharsets.UTF_8))) {

                int codePoint;
                while ((codePoint = br.read()) != -1) {
                    if (codePoint == caractereAlvo) {
                        contadorArquivo++;
                        contadorTotal++;
                    }
                }

                System.out.printf("Arquivo '%s': %d ocorrências%n", arquivo.getName(), contadorArquivo);

            } catch (IOException e) {
                System.out.println("Erro ao ler arquivo: " + arquivo.getName());
            }
        }

        System.out.printf("TOTAL de ocorrências do caractere '%s': %d%n", caractereStr, contadorTotal);
        entrada.close();
    }
}
