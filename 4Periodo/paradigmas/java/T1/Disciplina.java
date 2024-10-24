public class Disciplina{
	private String nome;
	private String codigo;
	private int periodo;
	private int horas;
	private String tipo;

	/*setters*/

	public void setNome(String nome){
		this.nome = nome;
	}

	public void setCodigo(String codigo){
		this.codigo = codigo;
	}

	public void setPeriodo(int periodo){
		this.periodo = periodo;
	}

	public void setHoras(int horas){
		this.horas = horas;
	}

	public void setTipo(String tipo){
		this.tipo = tipo;
	}

	/*getters*/

	public String getNome(){
		return this.nome;
	}

	public String getCodigo(){
		return this.codigo;
	}

	public int getPeriodo(){
		return this.periodo;
	}

	public int getHoras(){
		return this.horas;
	}

	public String getTipo(){
		return this.tipo;
	}


	public Disciplina(){}
	public Disciplina(String nome, String codigo, int periodo, int horas, String tipo){
		this.nome = nome;
		this.codigo = codigo;
		this.periodo = periodo;
		this.horas = horas;
		this.tipo = tipo;
	}
}