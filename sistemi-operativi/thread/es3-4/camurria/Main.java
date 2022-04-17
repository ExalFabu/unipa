// Si scriva un programma, sia in C che in Java, che sfrutti 2 diversi thread per la generazione casuale di una stringa di T caratteri:
// - il thread A fornisce in output N valori numerici nel range [0, 9];
// - il thread B fornisce in output L caratteri alfabetici minuscoli (a, ..., z).
// La stringa finale sarà ottenuta concatenando a coppie di risultati dei thread A e B, ad esempio 15ad36gt78

package camurria;
public class Main{
    public static void main(String[] args){
        MyThread t1 = new MyThread(true);
        MyThread t2 = new MyThread(false);
        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (Exception e) {
        }
        int [] t1g = t1.getGenerated();
        int [] t2g = t2.getGenerated();
        for (int i = 0; i < MyThread.MAX; i+=2) {
            System.out.format("%d%d%c%c", t1g[i], t1g[i+1], t2g[i], t2g[i+1]);
        }
        System.out.println();

    }
}
