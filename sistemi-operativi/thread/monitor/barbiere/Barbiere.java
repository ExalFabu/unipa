public class Barbiere extends Thread {
    private int barbId;
    private Sala s;

    public Barbiere(int id, Sala s) {
        super("Barbiere " + id);
        this.barbId = id;
        this.s = s;
    }

    @Override
    public void run() {
        System.out.println(this + " pronto a servire!");
        while (true) {
            Cliente daServire = this.s.accomodaCliente(this);
            this.serviCliente(daServire);
            try {
                System.out.println(this + " sta pulendo la sua postazione"); // aspetto dopo aver servito un cliente
                Thread.sleep((long) Math.random() * 2000);
            } catch (InterruptedException e) {
            }
        }
    }

    public void serviCliente(Cliente c) {
        try {
            System.out.println(this + " sta servendo " + c);
            Thread.sleep((long) Math.random() * 3000);
        } catch (InterruptedException e) {
        }
        System.out.println(this + " ha servito " + c);
        this.s.pagaConto(this, c);
    }

    public int getBarbId() {
        return this.barbId;
    }

    public String toString() {
        return "Barbiere " + this.barbId;
    }
}