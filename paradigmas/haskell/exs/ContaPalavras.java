import java.io.*;

public class ContaPalavras{

   public static void main(String[] args) throws IOException {
      BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
      String frase;
      int cont = 1;
      System.out.print("Digite uma frase: ");
      frase = teclado.readLine();
      for(int i = 0; i < frase.length(); i++){
         if(frase.charAt(i) == ' '){
            cont++;
         }
      }
      System.out.println("A frase '"+frase+"' contem "+cont+" palavras");
   }
}