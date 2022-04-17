/**
 * Main
 */
public class Main {
    public static final int DIM = 3;

    public static void printMatrix(int[][] m) {
        for (int i = 0; i < Main.DIM; i++) {
            for (int j = 0; j < Main.DIM; j++) {
                System.out.printf("%d\t", m[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int matrice[][] = {
                { 6, 5, 1 },
                { 4, 1, 2 },
                { 0, 7, 11 }
        };
        MyThread t1 = new MyThread(matrice, true);
        MyThread t2 = new MyThread(matrice, false);
        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (Exception e) {
        }
        int det = t1.getRis() - t2.getRis();
        printMatrix(matrice);
        System.out.println("Determinante: " + det);

    }
}