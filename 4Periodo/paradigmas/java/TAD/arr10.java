import java.util.Arrays;

public class arr10{
    private int[] arr = new int[10];
    private int tam = 0;

    public void insereArr(int i){
        if(tam < 10){
            arr[tam] = i;
            this.tam++;
        }
        else{
            System.out.printf("nao foi possivel inserir %d, Vetor Cheio\n", i);
        }
    }

    public void imprimeArr(){
        for(int i = 0; i < this.tam; i++){
            System.out.printf("%d ", this.arr[i]);
        }
        System.out.println();
    }

    public void ordenaArr(){
        Arrays.sort(this.arr);
    }

    public int busca(int v){
        for(int i = 0; i < this.tam; i++){
            if(arr[i] == v){
                return i;
            }
        }
        return -1;
    }
}