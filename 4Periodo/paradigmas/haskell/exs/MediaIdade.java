import java.io.*;

public class MediaIdade {
   public static void main(String[] args) throws IOException{
      double idade[] = new double[10];
      double media = 0.0;
      BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
      for(int i = 0; i < 10; i++){
         System.out.print("Digite a idade: ");
         idade[i] = Double.parseDouble(teclado.readLine());
         media += idade[i];
      }
      media = media/10;
      System.out.println("A média de idades é: "+media);
      for(int i = 0; i < 10; i++){
         if(idade[i] < media){
            System.out.println(idade[i]+" está abaixo da média");
         }
         else{
            System.out.println(idade[i]%.0f+" está acima da média");
         }
      }
   }
}
