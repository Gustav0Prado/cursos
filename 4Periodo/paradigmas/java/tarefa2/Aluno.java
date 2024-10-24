public class Aluno{
   private String nome;
   private String email;
   private String grr;

   public Aluno(){}

   public Aluno(String nome, String email, String grr){
      this.nome = nome;
      this.email = email;
      this.grr = grr;
   }

   public void setNome(String nome){
      this.nome = nome;
   }
   public void setEmail(String email){
      this.email = email;
   }
   public void setGrr(String grr){
      this.grr = grr;
   }

   public String getNome(){
      return this.nome;
   }
   public String getEmail(){
      return this.email;
   }
   public String getGrr(){
      return this.grr;
   }
}