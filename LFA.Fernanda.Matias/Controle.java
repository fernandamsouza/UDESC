//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

//Este arquivo esta encarregado de levar as informacoes de View.java para os outros arquivos.

public class Controle {
// como diz no nome de cada funcao
	private AutomatoFinitoDeterministico afd;
	
	public Controle() {}
	
	public void inicializaAutomato() {
		afd = new AutomatoFinitoDeterministico();
	}
	
	public void addSimbolo(String s) {
		afd.addSimbolo(s);
	}
	
	public void addEstado(String e) {
		afd.addEstado(e);
	}
	
	public void setEstadoFinal(String e) {
		afd.setEstadoFinal(e);
	}
	
	public void setEstadoInicial(String e) {
		afd.setEstadoInicial(e);
	}
		
	public void addTransicao(String ea, String s, String ep) {
		afd.addTransicao(ea,s,ep);
	}
	
	
	public int numeroTransicoes() {
		return afd.getEstados().size()*afd.getAlfabeto().size();
	}

	public String brzozowski() {
		Brzozowski br = new Brzozowski(afd);
		return br.brzozowski();
	}
}