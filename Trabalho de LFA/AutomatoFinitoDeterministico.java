//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

import java.util.TreeSet;
//CLASE DO AFD
public class AutomatoFinitoDeterministico {
//TREESET define a arvore do AFD
	private TreeSet<Simbolo> alfabeto;
	private TreeSet<Estado> estados;
	private TreeSet<Estado> estadosFinais;
	private Estado estadoInicial;
	private Estado estadoAtual;
	
	public AutomatoFinitoDeterministico() {
		alfabeto = new TreeSet<Simbolo>();
		estados = new TreeSet<Estado>();
		estadosFinais = new TreeSet<Estado>();	
	}
	
	public void setEstadoInicial(String estado) {
		for (Estado e: estados) {
			if (e.getEstado().compareTo(estado) == 0) estadoInicial = e;
		}
		estadoAtual = estadoInicial;
	}
	
	public void addEstado(String s) {
		Estado novo = new Estado(s);
		estados.add(novo);
	}
	
	public void addTransicao(String estado1, String simbolo, String estado2) {
		Estado ei = null;
		Estado ef = null;
		Simbolo s = null;
		for (Estado e: estados) {
			//Pega os estados
			if (e.getEstado().compareTo(estado1) == 0) ei = e;
			if (e.getEstado().compareTo(estado2) == 0) ef = e;
		}
		for (Simbolo sim: alfabeto) {
			//Pega o simbolo
			if (sim.getSimbolo().compareTo(simbolo) == 0) s = sim;
		}
		//Adiciona a transicao
		if (ei != null && ef != null && s != null) ei.addTransicao(s, ef);
	}
	
	public void setEstadoFinal(String s) {
		for (Estado e: estados) {
			if (e.getEstado().compareTo(s) == 0) {
				e.setFinal();
				estadosFinais.add(e);
			}
		}
	}
	
//Agrega simbolo novo ao alfabeto
	public void addSimbolo(String s) {
		Simbolo novo = new Simbolo(s);
		alfabeto.add(novo);
	}
	
	public TreeSet<Estado> getEstados() {
		return estados;
	}

	public TreeSet<Estado> getEstadosFinais() {
		return estadosFinais;
	}

	public Estado getEstadoInicial() {
		return estadoInicial;
	}
	
	public TreeSet<Simbolo> getAlfabeto() {
		return alfabeto;
	}
	
}
