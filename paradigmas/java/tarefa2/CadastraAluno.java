public class CadastraAluno {
   private Lista <Aluno> lista = new Lista<>();

   public void insereAluno(String nome, String email, String grr){
      Aluno aluno = new Aluno(nome, email, grr);
      this.lista.insere(aluno);
   }

   public void imprimeAlunos(){
      Nodo <Aluno> no = new Nodo<>();
      Aluno al = new Aluno();
      no = lista.getIni();
      while(no != null){
         al = no.getElem();
         System.out.println(al.getNome());
         no = no.getProx();
      }
   }
}
