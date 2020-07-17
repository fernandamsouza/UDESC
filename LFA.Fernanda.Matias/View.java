//Feito por: Fernanda Maria de Souza e Matias Gutierrez

package main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;




public class View {

	private static Controle control = new Controle();
//--------------------------------------------MAIN--------------------------------------------
	public static void main(String[] args) {
		
		System.out.println("Digite sua AFD.\n");
		lerConsole();
		System.out.println("Determinando uma expressao Regular atraves do Brzozowski");
		System.out.println("\nExpressao Regular: "+control.brzozowski()+"\n");
	}
//LE O CONSOLE
	private static void lerConsole() {
		control.inicializaAutomato();
		
		int i,total;
		String s;
		StringTokenizer st;
		
		System.out.print("Digite os simbolos do alfabeto: ");
		st = new StringTokenizer(readString());
		total = st.countTokens();
		for (i=0; i<total; i++) control.addSimbolo(st.nextToken());
	
		System.out.print("Digite os estados do automato: ");
		st = new StringTokenizer(readString());
		total = st.countTokens();
		for (i=0; i<total; i++)
			control.addEstado(st.nextToken());
		
		System.out.print("Digite o/s estado/s final/ais: ");
		st = new StringTokenizer(readString());
		total = st.countTokens();
		for (i=0; i<total; i++)
			control.setEstadoFinal(st.nextToken());
		
		System.out.print("Digite o estado inicial: ");
		control.setEstadoInicial(readString());
		
		System.out.println("Para terminar, entre com cada transicao do AFD (ex: estadoA w estadoB):");
		for (i = 0; i < control.numeroTransicoes(); i++) {
			s = readString();
			st = new StringTokenizer(s);
			control.addTransicao(st.nextToken(),st.nextToken(),st.nextToken());
		}
		System.out.println("");
	}
//FUNCAO DE LER STRINGS
	public static String readString() {
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			return br.readLine();
		} catch (IOException e) {
			return "NULL";
		}
	}
}