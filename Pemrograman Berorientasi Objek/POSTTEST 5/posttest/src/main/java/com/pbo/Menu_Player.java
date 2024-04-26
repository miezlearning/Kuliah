package com.pbo;

public class Menu_Player extends Character {
    // Constructor
    public Menu_Player(String username, String nickname, String job, int hp, int mp, int attack, int defense) {
        super(username, nickname, job, hp, mp, attack, defense);
    }

    // Fungsi overloading untuk menampilkan informasi karakter
    public void cek_info(User user) {
        Character character = user.getCharacter();
        if (character != null) {
            System.out.println("Informasi karakter:");
            System.out.println("Nickname: " + character.getNickname());
            System.out.println("Job: " + character.getJob());
            System.out.println("HP: " + character.getHp());
            System.out.println("MP: " + character.getMp());
            System.out.println("Attack: " + character.getAttack());
            System.out.println("Defense: " + character.getDefense());
        } else {
            System.out.println("Anda belum memiliki karakter.");
        }
    }

    // Fungsi overriding untuk menampilkan informasi karakter dari objek Character
    public void cek_info(Character character) {
        System.out.println("Informasi karakter:");
        System.out.println("Nickname: " + character.getNickname());
        System.out.println("Job: " + character.getJob());
        System.out.println("HP: " + character.getHp());
        System.out.println("MP: " + character.getMp());
        System.out.println("Attack: " + character.getAttack());
        System.out.println("Defense: " + character.getDefense());
    }

    // Fungsi overloading dengan tambahan parameter boolean detail untuk menampilkan
    // informasi karakter dari objek Character
    public void cek_info(Character character, boolean detail) {
        if (detail) {
            System.out.println("Detail informasi karakter:");
            cek_info(character);
        } else {
            System.out.println("Informasi karakter:");
            System.out.println("Nickname: " + character.getNickname());
            System.out.println("Job: " + character.getJob());
        }
    }

    // Fungsi overloading untuk menampilkan informasi karakter dari objek User
    // dengan tambahan detail
    public void cek_info(User user, boolean detail) {
        if (detail) {
            System.out.println("Detail informasi karakter:");
            cek_info(user);
        } else {
            System.out.println("Informasi karakter:");
            System.out.println("Nickname: " + user.getCharacter().getNickname());
            System.out.println("Job: " + user.getCharacter().getJob());
        }
    }
}