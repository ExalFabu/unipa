import java.util.LinkedList;

public class Sala {
    private LinkedList<Cliente> divano;
    private final int maxDivano = 5;
    private LinkedList<Cliente> salaAttesa;
    private final int maxPersone = 10;
    private boolean cassaInUso = false;

    public Sala() {
        this.divano = new LinkedList<Cliente>();
        this.salaAttesa = new LinkedList<Cliente>();
    }

    public synchronized void siediCliente(Cliente c) {
        if (this.divano.contains(c))
            return;
        while (this.divano.size() >= this.maxDivano) {
            try {
                System.out.printf("%s ha trovato il divano pieno, aspetta\n", c.getName());
                wait();
            } catch (Exception e) {
            }
        }

        // if (this.salaAttesa.indexOf(c) == 0) {
        Cliente daFarSedere = this.salaAttesa.pop(); // che dovrebbe essere il primo
        System.out.printf("%s si è seduto sul divano\n", daFarSedere.getName());
        this.divano.addLast(daFarSedere);
        notifyAll();

    }

    public synchronized void accogliCliente(Cliente c) {
        if (salaAttesa.size() >= this.maxPersone) {
            System.out.printf("%s: Sala Piena\n", c.getName());
            return;
        }
        System.out.printf("%s ha trovato posto in sala, entra\n", c.getName());
        salaAttesa.addLast(c);
        this.siediCliente(c);
    }

    public synchronized Cliente accomodaCliente(Barbiere b) {
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

    public synchronized void serviCliente(Barbiere b) {
        while (this.divano.size() == 0) {
            try {
                System.out.printf("Divano vuoto, %s aspetta\n", b.getName());
                wait();
            } catch (Exception e) {
            }
        }
        Cliente daServire = divano.removeFirst();
        notifyAll(); // Notifico che il divano ha liberato un posto (?)
        System.out.printf("%s sta servendo %s\n", b.getName(), daServire.getName());
        try {
            Thread.sleep((int) (Math.random() * 0 + 2001));
        } catch (Exception e) {
        }
        this.pagaConto(b, daServire);
    }

    public synchronized void pagaConto(Barbiere b, Cliente c) {
        while (cassaInUso) {
            try {
                System.out.println("Volevano pagare ma era in uso, aspetta");
                wait();
            } catch (Exception e) {
            }
        }

        cassaInUso = true;
        System.out.printf("%s sta facendo pagare %s\n", b.getName(), c.getName());
        try {
            Thread.sleep((int) (Math.random() * 101));
        } catch (Exception e) {
        }
        System.out.println(b + " ha fatto pagare " + c);
        cassaInUso = false;
        notify();
    }
}
