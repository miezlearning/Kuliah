package com.pbo;

public class Menu_Player extends Character {
    // Constructor
    public Menu_Player(String username, String nickname, String job, int hp, int mp, int attack, int defense) {
        super(username, nickname, job, hp, mp, attack, defense);
    }

    // Metode tambahan untuk cek informasi karakter
    public void cek_info(User user) {
        Character character = user.getCharacter();
        App halo = new App();
        if (character != null) {
            System.out.println("Username: " + user.getUsername());
            System.out.println("Nickname: " + character.getNickname());
            System.out.println("Job: " + character.getJob());
            System.out.println("HP: " + character.getHp());
            System.out.println("MP: " + character.getMp());
            System.out.println("Attack: " + character.getAttack());
            System.out.println("Defense: " + character.getDefense());
            halo.menuUtama(user);
        } else {
            System.out.println("Anda belum memiliki karakter.");
        }
    }
}