import java.io.*;

public class ProcuraNome {
   static int tam = 10;
   public static void main(String[] args) throws IOException {
      String nome[] = new String[tam];
      String busca;
      int i;
      BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
      for(i = 0; i < tam; i++){
         System.out.print((i+1)+": ");
         nome[i] = teclado.readLine();
      }
      System.out.println("Digite um nome para ser buscado: ");
      busca = teclado.readLine();
      i = 0;
      while(i < tam && !busca.equals(nome[i])){
         i++;
      }
      if(i == tam){
         System.out.println("Não Achou "+busca);
      }
      else{
         System.out.println("Achou "+busca+" na posição "+(i+1));
      }
   }
}
