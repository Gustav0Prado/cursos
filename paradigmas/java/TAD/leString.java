import java.util.*;

public class leString {
    private Vector <String> vet;
    private ArrayList <String> vetA;

    public void ler(){
        vet = new Vector<>();
        Scanner le = new Scanner(System.in);
        String atual = le.next();
        while(atual != null && !(atual.equals("fim"))){
            vet.add(atual);
            atual = le.next();
        }
        Collections.sort(vet);
        le.close();
    }

    public void imprimirVet(){
        for(String s : vet){
            System.out.println(s);
        }
    }

    public void lerA(){
        vetA = new ArrayList<>();
        Scanner le = new Scanner(System.in);
        String atual = le.next();
        while(atual != null && !(atual.equals("fim"))){
            vetA.add(atual);
            atual = le.next();
        }
        Collections.sort(vetA);
        le.close();
    }

    public void imprimirVetA(){
        Iterator <String> it;

        it = vetA.iterator();
        while(it.hasNext()){
            System.out.print(it.next()+" ");
        }
        System.out.println();
    }
}
