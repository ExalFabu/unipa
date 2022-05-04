public class MyThread extends Thread {
    private String toCheck;
    private boolean reverse;
    private String ret;

    public MyThread(String toCheck, boolean reverse) {
        this.toCheck = toCheck;
        this.reverse = reverse;
        this.ret = "";
    }

    @Override
    public void run() {
        int middle = this.toCheck.length() % 2 == 0 ? this.toCheck.length() / 2 : (this.toCheck.length() / 2) + 1;
        for (int i = 0; i < middle; i++) {
            int ind = i;
            if (this.reverse)
                ind = this.toCheck.length() - i - 1;
            this.ret += this.toCheck.charAt(ind);
        }
    }

    public String getRet() {
        return this.ret;
    }
}
