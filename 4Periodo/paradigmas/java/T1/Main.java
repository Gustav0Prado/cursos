import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.Charset;

public class Main {
   public static void main(String[] args) throws IOException {
      Disciplina calc = new Disciplina("Calculo 1", "CM201", 2, 80, "Obrigatoria");
      ListaDisc lista = ListaDisc.getInstance();
      lista.imprime();
   }
}
