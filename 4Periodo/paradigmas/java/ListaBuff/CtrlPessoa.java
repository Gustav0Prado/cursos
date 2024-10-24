public class CtrlPessoa{
   public static void main(String[] args) {
      ListaPessoas lp = ListaPessoas.getInstance();
      lp.inserePessoa("Alberto", "1234", "Rua dos Bobos, nº0");
      lp.inserePessoa("Jose", "5678", "Rua dos Bobos, nº1");
      lp.inserePessoa("Joaozinho", "7894", "Rua dos Bobos, nº2");
      lp.imprimeLista();
   }
}