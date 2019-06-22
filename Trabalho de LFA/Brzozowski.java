//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

import java.util.TreeMap;

public class Brzozowski {
	private AutomatoFinitoDeterministico afd;
	private TreeMap<Integer, Linguagem> linguagens; // árvore que contém um inteiro e a linguagem de cada autômato inicializado pelo método.
	private int qtd;

	public Brzozowski(AutomatoFinitoDeterministico afd) {
		this.afd = afd;
		linguagens = new TreeMap<Integer, Linguagem>();
		int i = 1;
		//inicializa o mapa colocando nele os estados com suas respectivas linguagens
		for (Estado e: this.afd.getEstados()) {
			if (e.compareTo(afd.getEstadoInicial()) == 0) { // caso a comparação seja verdadeira e seja o estado inicial.
				linguagens.put(1,new Linguagem(e.getLinguagem(), e.getEstado())); // para o estado inicial.
			} else { // demais estados.
				++i;
				linguagens.put(i, new Linguagem(e.getLinguagem(), e.getEstado()));
			}
		}
		qtd = i;
	}

	public String brzozowski() {
		//método de brzozowski
		for (int i = qtd; i > 0; i--) {

			if (i == qtd) {
				if (!linguagens.get(i).verifica()) {
					linguagens.get(i).setLinguagem(linguagens.get(i).simplifica(linguagens.get(i).getLinguagem()));
					linguagens.get(i).arden(); // chamada do lema de arden.
				}
			} else {
				for (int j = qtd; j > i; j--) {
					linguagens.get(i).substitui(linguagens.get(j).getEstado(),linguagens.get(j).getLinguagem());
				}
				if (!linguagens.get(i).verifica()) {
					linguagens.get(i).setLinguagem(linguagens.get(i).simplifica(linguagens.get(i).getLinguagem()));
					linguagens.get(i).arden(); // chamada do lema de arden
				}
			}
		}

		return linguagens.get(1).getLinguagem();
	}
}
