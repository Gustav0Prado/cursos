public class No <E> {
   private No <E> prox;
   private E elem;

   public No(No <E> prox, E elem){
      this.prox = prox;
      this.elem = elem;
   }

   public void setProx(No <E> prox){
      this.prox = prox;
   }

   public void setElem(E elem){
      this.elem = elem;
   }

   public No <E> getProx(){
      return this.prox;
   }

   public E getElem(){
      return this.elem;
   }
}