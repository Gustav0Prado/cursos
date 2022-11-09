public class Lista <E> implements Iterator <E>{
   private No <E> ini;
   private int tam;
   private No <E> pos;

   public Lista(){
      this.ini = null;
      this.tam = 0;
   }

   public int tamanho(){
      return this.tam;
   }

   public void insere(E elem){
      No <E> no = new No<>(this.ini, elem);
      this.pos = no;
      this.ini = no;
      this.tam++;
   }

   public No <E> top(){
      return this.ini;
   }

   public Iterator <E> iterator(){
      return this;
   }

   public boolean hasNext(){
      return(pos != null);
   }

   public No <E> next(){
      No <E> n = pos;
      pos = pos.getProx();
      return n;
   }
}