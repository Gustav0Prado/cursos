public class Sorteio {
   public static void main(String[] args){
      String pessoas[] = {"Matheus", "Ana", "Cláudio", "Joana", "Paulo"};
      int sorteio = (int)(Math.random()*5);
      System.out.println("O vencedor foi: "+pessoas[sorteio]);
   }
}
