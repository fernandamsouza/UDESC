//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

//Classe encarregada de fazer as comparacoes dos simbolos do alfabeto cada vez que eh chamada.

public class Simbolo implements Comparable<Simbolo> {
	
	private String simbolo;

	public Simbolo(String simbolo) {
		this.simbolo = simbolo;
	}

	public String getSimbolo() {
		return simbolo;
	}

	public void setSimbolo(String simbolo) {
		this.simbolo = simbolo;
	}

	@Override
	public int compareTo(Simbolo o) {
		return simbolo.compareTo(o.getSimbolo());
	}

	@Override
	public String toString() {
		return simbolo;
	}
}
