package com.pbo;

public class Menu_Player {
    // public void menu_start() {
    //     System.out.println("Selamat Datang Player Baru!");
    //     System.out.println("Mari ikuti aku untuk membuat karakter kamu!");

    //     System.out.println("1. Buat Karakter");
    //     System.out.println("2. Kembali");
    // }

    public static void cek_info(User user) {
        App halo = new App();
        Character pengguna = user.getCharacter();
        System.out.println("Job / Class : " + pengguna.getJob());
        System.out.println("HP : " + pengguna.getHp());
        System.out.println("MP : " + pengguna.getMp());
        System.out.println("Attack : " + pengguna.getAttack());
        System.out.println("Defense : " + pengguna.getDefense());
        halo.menuUtama(user);
    }
}
