import java.util.*;
import java.io.*;
import java.nio.charset.Charset;;

/* ignorar materia se nao ativa */


public class ListaDisc2011{
	private static ListaDisc2011 ui;
	private ArrayList <Disciplina> lista;

	private static final int COD  = 3;
	private static final int NOME = 5;
	private static final int PER  = 6;
	private static final int TIPO = 8;
	private static final int HORA = 10;

	private ListaDisc2011() throws IOException{
		this.lista = new ArrayList<Disciplina>();
		/*Carrega disciplinas do arquivo*/
		BufferedReader br = new BufferedReader(new FileReader("Disciplinas_2011.csv", Charset.forName("Windows-1258")));
		String linha;
		/* le primeiras linhas vazias */
      br.readLine();
      br.readLine();

		Disciplina d;
		/* le linhas com as infos, pegando as horas totais sem repetir */
      while((linha = br.readLine()) != null){
      	String[] split = linha.split(";");
			if(!(split[PER].equals(""))){
				d = new Disciplina(split[NOME], split[COD], Integer.parseInt(split[PER]), Integer.parseInt(split[HORA]), split[TIPO]);
			}
			else{
				d = new Disciplina(split[NOME], split[COD], 0, Integer.parseInt(split[HORA]), split[TIPO]);
			}
			/* se nao achar nome na lista */
			if(!repetido(lista, split[NOME])){
				lista.add(d);
			}
		}

		System.out.println("Disciplinas de 2011 carregadas! " + lista.size());
	}

	private Boolean repetido(ArrayList <Disciplina> l, String nome){
		Iterator it = l.iterator();
		Disciplina d;

		while(it.hasNext()){
			d = (Disciplina) it.next();
			if(d.getNome().equals(nome)){
				return true;
			}
		}
		return false;
	}

	public static synchronized ListaDisc2011 getInstance() throws IOException{
		if(ui == null){
			ui = new ListaDisc2011();
		}
		return ui;
	}

	public void imprime(){
		lista.forEach((n) -> System.out.println(n.getNome() + " - " + n.getCodigo()));
	}
}