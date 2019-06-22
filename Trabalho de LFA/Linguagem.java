//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

public class Linguagem {
	
	private String linguagem;
	private String estado;
	private boolean isSimplificado;
	
	public Linguagem(String linguagem, String estado) {
		this.linguagem = linguagem;
		this.estado = estado;
		verifica();
	}

	public boolean verifica() {
		if (linguagem.contains("L(" + estado + ")")) isSimplificado = false;
		else isSimplificado = true;
		return isSimplificado;
	}
	
	//Coloca em evidencia os L's
	public String simplifica(String ling) {
		String[] splitU = ling.split("U");
		int cont = 0;
		
		for (String s: splitU) {
			if (s.contains("L(" + estado + ")")) cont++;
		}
		
		if (cont <= 1) {
			isSimplificado = true;
		} else {
			String temp = "";
			String A = "";
			for (String s: splitU) {
				if (s.contains("L(" + estado + ")")) {
					if (A == "") A = s.replace("L(" + estado + ")", "");
					else A += "U" + s.replace("L(" + estado + ")", "");
				} 
			}
			
			A = parentesis(A);
			A += "L(" + estado + ")";
			
			for (int i = 0; i < splitU.length; i++) {
				if (!splitU[i].contains("L(" + estado + ")")) {
					if (temp.equals("")) temp = temp.concat(splitU[i]);
					else temp = temp.concat("U" + splitU[i]);
				}
			}
			
			if (temp.contains("U") || (temp.length() != 1 && !temp.equals("") && !temp.equals("{E}"))) temp = "(" + temp + ")";			
			if (temp.equals("")) {
				ling = A; 
			} else {
				ling = A + "U" + temp;
			}
			isSimplificado = true;
		}
		return ling;
	}
	
	//Aplica o lema de Arden à linguagem
	public void arden() {
		String A = "", B = "";
		String[] temp, splitL;
		String[] split = linguagem.split("\\(|\\)");

		for (int i = 0; i < split.length; i++) {
			if (split[i].contains("L")) {
				if (split[i].compareTo("L") == 0 && split[i+1].compareTo(estado) == 0) {
					A = split[i-1];
					break;
				}
				if (split[i+1].compareTo(estado) == 0) {
					temp = split[i].split("U");
					A = temp[temp.length-1].replace("L", "");
					break;
				}
			}
		}
		B = linguagem.replace(parentesis(A)+"L("+estado+")","");
		B = B.replace("UU", "U");
		
		splitL = B.split("U");
		B = "";
		for (String s: splitL) {
			if (!s.equals(")") && !s.equals("(")) {
				if (!B.equals("")) B += s;
				else B = s;
			}
		}
		
		A = parentesis(A);
		A += "*";
		
		B = parentesis(B);
		
		if (!B.equals("({E})")) linguagem = A + B;
		else linguagem = A;
	}
	
	//Substitui a linguagem de um estado est na linguagem, ou seja, L(est) é substituido por ling
	public void substitui(String est, String ling) {
		linguagem = linguagem.replace("L(" + est + ")", ling);
	}
	
	//Tira o excesso de parentesis
	private String parentesis(String s) {
		boolean temParentesis = false;
		if (!s.equals("")) temParentesis = s.charAt(0) == '(' && s.charAt(s.length()-1) == ')';
		if (!temParentesis) {
			if (s.length() > 1 && !s.contains("L(")) {
				s = "(" + s + ")";
			}
		} else {
			s = s.substring(1, s.length()-1);
		}
		return s;
	}
//funcoes auxiliares
	public String getLinguagem() {
		return linguagem;
	}
	
	public void setLinguagem(String l) {
		linguagem = l;
	}

	public boolean isSimplificado() {
		return isSimplificado;
	}
	
	public String getEstado() {
		return estado;
	}

	@Override
	public String toString() {
		return linguagem;
	}
}