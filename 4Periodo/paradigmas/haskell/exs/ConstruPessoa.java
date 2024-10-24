import java.io.*;

public class ConstruPessoa{
   public static void main(String[] args) throws IOException {
      Pessoa A = new Pessoa("Ana", "Rua X", "1234", "Ana@email.com");
      FileWriter Arquivo = new FileWriter("Saida.txt");
      Arquivo.write(A.getNome()+"\n");
      Arquivo.write(A.getTelefone()+"\n");
      Arquivo.write(A.getEndereco()+"\n");
      Arquivo.write(A.getEmail()+"\n");
      Arquivo.close();
   }
}

class Pessoa{
   private String nome;
   private String endereco;
   private String telefone;
   private String email;

   public Pessoa(String nome, String endereco, String telefone, String email){
      this.nome = nome;
      this.endereco = endereco;
      this.telefone = telefone;
      this.email = email;
   }

   public String getNome(){
      return this.nome;
   }
   public String getTelefone(){
      return this.telefone;
   }
   public String getEndereco(){
      return this.endereco;
   }
   public String getEmail(){
      return this.email;
   }
}