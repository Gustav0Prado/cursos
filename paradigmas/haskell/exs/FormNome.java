import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class FormNome {
   public static void main(String[] args) throws IOException {
      BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
      String nomeCompleto = teclado.readLine();
      int espaco = nomeCompleto.indexOf(' ') + 1;
      System.out.println(nomeCompleto.substring(espaco, nomeCompleto.length()) + ", " + nomeCompleto.charAt(0) + ".");
   }
}
