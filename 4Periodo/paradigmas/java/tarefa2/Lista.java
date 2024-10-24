public class Lista <E> {
   private Nodo <E> ini;
   private Nodo <E> fim;
   private int tam;

   public Lista(){
      this.ini = null;
      this.fim = null;
      this.tam = 0;
   }

   public boolean vazia(){
      return (this.tam == 0);
   }

   public int tamanho(){
      return this.tam;
   }

   public void insere(E elem){
      Nodo <E> aux = new Nodo<>(elem);
      aux.setProx(this.ini);
      this.ini = aux;
      if(this.vazia()){
         this.fim = this.ini;
      }
      this.tam++;
   }

   public Nodo <E> getIni(){
      return this.ini;
   }
}
