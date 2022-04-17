public class MyThread extends Thread {
    private int[][] matrice;
    private boolean principale; // true if diagonali principali
    private int ris;

    public MyThread(int[][] matrice, boolean principale) {
        this.matrice = matrice;
        this.principale = principale;
        this.ris = 0;
    }

    @Override
    public void run() {
        for (int offset = 0; offset < Main.DIM; offset++) {
            int local_mul = 1;
            for (int i = 0; i < Main.DIM; i++) {
                int row = this.principale ? i : Main.DIM - 1 - i;
                int col = (i + offset) % Main.DIM;
                local_mul *= this.matrice[row][col];
            }
            this.ris += local_mul;
        }
    }

    public int getRis() {
        return this.ris;
    }

}