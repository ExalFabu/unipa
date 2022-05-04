public class Main {
    public static void main(String[] args) {
        String pali = "itopinonavevanonipoti";
        MyThread t1 = new MyThread(pali, false);
        MyThread t2 = new MyThread(pali, true);
        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (Exception e) {
            // : handle exception
        }
        System.out.println(t1.getRet());
        System.out.println(t2.getRet());
        System.out.println("La stringa " + pali + " è palindroma -> " + t1.getRet().equals(t2.getRet()));

    }

}