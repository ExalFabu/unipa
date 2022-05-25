import java.util.LinkedList;

public class Sala {
    private LinkedList<Cliente> divano;
    private final int maxDivano = 5;
    private LinkedList<Cliente> salaAttesa;
    private final int maxPersone = 10;

    public Sala() {
        this.divano = new LinkedList<Cliente>();
        this.salaAttesa = new LinkedList<Cliente>();
    }

    public synchronized void siediCliente(Cliente c) {
        if (this.divano.contains(c))
            return;
        while (this.divano.size() >= this.maxDivano) {
            try {
                System.out.println(c + " ha trovato il divano pieno, aspetta");
                wait();
            } catch (Exception e) {
            }
        }

        // if (this.salaAttesa.indexOf(c) == 0) {
        Cliente daFarSedere = this.salaAttesa.pop(); // che dovrebbe essere il primo
        System.out.println(daFarSedere + " si è seduto sul divano");
        this.divano.addLast(daFarSedere);
        notifyAll();

    }

    public synchronized void accogliCliente(Cliente c) {
        if (salaAttesa.size() >= this.maxPersone) {
            System.out.println(c + ": Sala Piena");
            return;
        }
        System.out.println(c + " ha trovato posto in sala, entra");
        salaAttesa.addLast(c);
        this.siediCliente(c);
    }

    public synchronized Cliente accomodaCliente(Barbiere b) { // accomoda nella poltrona (?)
        while (this.divano.size() == 0) {
            try {
                // System.out.println(b + " sta aspettando perché il divano è vuoto");
                wait();
            } catch (Exception e) {
            }
        }
        Cliente c = this.divano.pop();
        notify();
        return c;
    }

    // Non serve più, spostato su Barbiere
    //
    // public synchronized void serviCliente(Barbiere b) {
    // while (this.divano.size() == 0) {
    // try {
    // System.out.println("Divano vuoto, " + b + " aspetta");
    // wait();
    // } catch (Exception e) {
    // }
    // }
    // Cliente daServire = divano.removeFirst();
    // notifyAll(); // Notifico che il divano ha liberato un posto (?)
    // System.out.printf("%s sta servendo %s\n", b.getName(), daServire.getName());
    // try {
    // Thread.sleep((int) (Math.random() * 0 + 2001));
    // } catch (Exception e) {
    // }
    // this.pagaConto(b, daServire);
    // }

    public synchronized void pagaConto(Barbiere b, Cliente c) {
        System.out.println(b + " sta facendo pagare " + c);
        try {
            Thread.sleep((int) (Math.random() * 101));
        } catch (Exception e) {
        }
        System.out.println(b + " ha fatto pagare " + c);
    }
}
