import java.util.*;
import java.io.*;
import java.nio.charset.Charset;;

/* ignorar materia se nao ativa */

public class ListaDisc{
	private static ListaDisc ui;
   private ArrayList <Disciplina> lista2011;
   private ArrayList <Disciplina> lista2019;
   private int cod;
   private int nome;
   private int per;
   private int hora;

   private void Carrega2011() throws IOException{
      this.lista2011 = new ArrayList<Disciplina>();
      cod = 3;
      nome = 5;
      per = 6;
      hora = 10;
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
			if(!(split[per].equals(""))){
				d = new Disciplina(split[nome], split[cod], Integer.parseInt(split[per]), Integer.parseInt(split[hora]), split[8]);
			}
         /* se periodo for vazio manda 0 no lugar */
			else{
				d = new Disciplina(split[nome], split[cod], 0, Integer.parseInt(split[hora]), split[8]);
			}
			/* se nao achar nome na lista */
			if(!repetido(lista2011, split[nome])){
				lista2011.add(d);
			}
		}

		System.out.println("Disciplinas de 2011 carregadas! " + lista2011.size());
      br.close();
   }

   private void Carrega2019() throws IOException{
      this.lista2019 = new ArrayList<Disciplina>();
      cod = 3;
      nome = 5;
      per = 6;
      hora = 9;
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
				if(!(split[per].equals(""))){
					d = new Disciplina(split[nome], split[cod], Integer.parseInt(split[per]), Integer.parseInt(split[hora]), split[8]);
				}
				else{
					d = new Disciplina(split[nome], split[cod], 0, Integer.parseInt(split[hora]), split[8]);
				}
				/* se nao achar nome na lista e disciplina esta ativa*/
				if(!repetido(lista2019, split[nome]) && split[10].equals("ATIVA")){
					lista2019.add(d);
				}
			}
		}

		System.out.println("Disciplinas de 2019 carregadas! " + lista2019.size());
      br.close();
   }

	private ListaDisc() throws IOException{
		Carrega2011();
      Carrega2019();
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

	public static synchronized ListaDisc getInstance() throws IOException{
		if(ui == null){
			ui = new ListaDisc();
		}
		return ui;
	}

	public void imprime(){
		lista2011.forEach((n) -> System.out.println("2011 " + n.getNome() + " - " + n.getCodigo()));
      lista2019.forEach((n) -> System.out.println("2019 " + n.getNome() + " - " + n.getCodigo()));
	}

   public ArrayList<Disciplina> getLista2011(){
      return this.lista2011;
   }

   public ArrayList<Disciplina> getLista2019(){
      return this.lista2019;
   }
}
