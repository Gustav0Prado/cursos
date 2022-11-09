import java.io.*;

public class SomaMatriz {
   public static void main(String[] args) throws IOException{
      int matrizA[][] = new int[3][3];
      int matrizB[][] = new int[3][3];
      int matrizC[][] = new int[3][3];
      BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
      System.out.print("Digite a matriz A: ");
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            matrizA[i][j] = Integer.parseInt(teclado.readLine());
         }
      }
      System.out.print("Digite a matriz B: ");
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            matrizB[i][j] = Integer.parseInt(teclado.readLine());
         }
      }
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            matrizC[i][j] = matrizA[i][j] + matrizB[i][j];
         }
      }
      System.out.println("Matriz A: ");
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
           System.out.print(matrizA[i][j]+" ");
         }
         System.out.println();
      }
      System.out.println("Matriz B: ");
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
           System.out.print(matrizB[i][j]+" ");
         }
         System.out.println();
      }
      System.out.println("A soma das matrizes A e B é: ");
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
           System.out.print(matrizC[i][j]+" ");
         }
         System.out.println();
      }
   }
}
