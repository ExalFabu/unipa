public class Main {

    public static void main(String[] args) {
        Sala sala = new Sala();
        int nBarbieri = 3;
        int nClienti = 22;
        Barbiere[] barbieri = new Barbiere[nBarbieri];
        Cliente[] clienti = new Cliente[nClienti];
        for (int i = 0; i < nBarbieri; i++) {
            barbieri[i] = new Barbiere(i + 1, sala);
            barbieri[i].start();
        }
        for (int i = 0; i < nClienti; i++) {
            clienti[i] = new Cliente(sala);
            clienti[i].start();
            try {
                Thread.sleep((int) (Math.random() * 101));
            } catch (Exception e) {

            }
        }
    }
}
