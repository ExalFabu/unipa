public class Cliente extends Thread {
    private static int cliente_counter = 0;
    private int clientId;
    private Sala s;

    public Cliente(int id, Sala s) {
        super("Cliente " + id);
        this.clientId = id;
        this.s = s;
        Cliente.cliente_counter++;
    }

    public Cliente(Sala s) {
        super("Cliente " + Cliente.cliente_counter);
        this.clientId = Cliente.cliente_counter;
        this.s = s;
        Cliente.cliente_counter++;
    }

    @Override
    public void run() {
        try {
            this.s.accogliCliente(this);
        } catch (Exception e) {
        }
    }

    public int getClientId() {
        return clientId;
    }

    public String toString() {
        return "Cliente " + this.clientId;
    }
}
