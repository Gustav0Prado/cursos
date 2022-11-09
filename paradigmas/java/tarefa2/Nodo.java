public class Nodo <E> {
   private Nodo <E> prox;
   private  E elem;

   public Nodo(){}

   public Nodo(E elem){
      this.prox = null;
      this.elem = elem;
   }

   public void setProx(Nodo <E> prox){
      this.prox = prox;
   }
   public void setElem(E elem){
      this.elem = elem;
   }

   public Nodo <E> getProx(){
      return this.prox;
   }

   public E getElem(){
      return this.elem;
   }
}
