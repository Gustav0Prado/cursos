public class ListaPessoas {
   private static ListaPessoas ui;
   private Lista <Pessoa> li;

   private ListaPessoas(){
      this.li = new Lista<Pessoa>();
   }

   public static synchronized ListaPessoas getInstance(){
      if(ui == null){
         ui = new ListaPessoas();
      }
      return ui;
   }

   public void inserePessoa(String nome, String endereco, String cpf){
      Pessoa p = new Pessoa(nome, cpf, endereco);
      this.li.insere(p);
   }

   public void imprimeLista(){
      Iterator <Pessoa> it = this.li.iterator();

      while(it.hasNext()){
         System.out.println(it.next().getElem().getNome());
      }
   }
}
