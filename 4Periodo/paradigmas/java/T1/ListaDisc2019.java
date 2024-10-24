import java.util.*;
import java.io.*;
import java.nio.charset.Charset;;

/* ignorar materia se nao ativa */

public class ListaDisc2019{
	private static ListaDisc2019 ui;
	private ArrayList <Disciplina> lista;

	private static final int COD  = 3;
	private static final int NOME = 5;
	private static final int PER  = 6;
	private static final int TIPO = 9;
	private static final int HORA = 9;
   private static final int SIT  = 10;

	private ListaDisc2019() throws IOException{
		this.lista = new ArrayList<Disciplina>();
		/*Carrega disciplinas do arquivo*/
		BufferedReader br = new BufferedReader(new FileReader("Disciplinas_2019.csv", Charset.forName("Windows-1258")));
		String linha;
		/* le primeiras linhas vazias */
      br.readLine();
      br.readLine();

		Disciplina d;
		/* le linhas com as infos, pegando as horas totais sem repetir */
      while((linha = br.readLine()) != null){
      	String[] split = linha.split(";");
			/* pega apenas materias com todos os campos */
			if(split.length == 11){
				/* Optativas sem periodo sugerido ficam com periodo = 0 */
				if(!(split[PER].equals(""))){
					d = new Disciplina(split[NOME], split[COD], Integer.parseInt(split[PER]), Integer.parseInt(split[HORA]), split[TIPO]);
				}
				else{
					d = new Disciplina(split[NOME], split[COD], 0, Integer.parseInt(split[HORA]), split[TIPO]);
				}
				/* se nao achar nome na lista e disciplina esta ativa*/
				if(!repetido(lista, split[NOME]) && split[SIT].equals("ATIVA")){
					lista.add(d);
				}
			}
		}

		System.out.println("Disciplinas de 2019 carregadas! " + lista.size());
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

	public static synchronized ListaDisc2019 getInstance() throws IOException{
		if(ui == null){
			ui = new ListaDisc2019();
		}
		return ui;
	}

	public void imprime(){
		lista.forEach((n) -> System.out.println(n.getNome() + " - " + n.getCodigo()));
	}
}