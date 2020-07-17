//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeMap;

public class Estado implements Comparable<Estado>{
	private String estado;
	private TreeMap<Simbolo, Estado> transicoes;
	private boolean isFinal = false;

	public Estado(String estado) {
		super();
		this.estado = estado;
		transicoes = new TreeMap<Simbolo, Estado>();
	}
	
	//Retorna a Linguagem que leva o estado "estado" para um estado final
	public String getLinguagem () {
		String L = "";
		int i = 0;
		Set<Simbolo> keyset = transicoes.keySet();
		Iterator<Simbolo> it = keyset.iterator();
		while (it.hasNext()) {
			Simbolo s = it.next();
			if (it.hasNext()) {
				L = L.concat(s.toString() + "L(" + transicoes.get(s) + ")U");
				i += transicoes.get(s).toString().length() + 2;
			} else {
				L = L.concat(s.toString() + "L(" + transicoes.get(s) + ")");
				i += transicoes.get(s).toString().length() + 1;
			}
		}
		if (isFinal) L = L.concat("U{E}");	
		return L;
	}
	
	//Retorna os simbolos que fazem a transicao de "estado" para "e"
	public String simboloTransicaoPara(Estado e) {
		String st = "";
		if (transicoes.containsValue(e)) {
			for (Simbolo s: transicoes.keySet()) {
				if (transicoes.get(s).getEstado().equals(e.getEstado())) {
					if (st.equals("")) {
						st = s.getSimbolo();					
					} else {
						st += "U" + s.getSimbolo();
					}
				}
			}
		} 
		if (st.equals("")) return "{}";
		return st;
	}
//funcoes auxiliares
	public String getEstado() {
		return estado;
	}

	public void setEstado(String estado) {
		this.estado = estado;
	}

	@Override
	public int compareTo(Estado o) {
		return estado.compareTo(o.getEstado());
	}
	
	public void addTransicao(Simbolo s, Estado e) {
		transicoes.put(s, e);
	}
	
	public Estado transiciona(Simbolo s) {
		return transicoes.get(s);
	}
	
	public boolean isFinal() {
		return isFinal;
	}
	
	public void setFinal() {
		isFinal = true;
	}

	@Override
	public String toString() {
		return estado;
	}
}