package com.pbo;

class User {
    private String username;
    private String password;
    private Character character;
    private String role;

    public User(String username, String password, String role) {
        this.username = username;
        this.password = password;
        this.role = role;
        this.character = null;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public Character getCharacter() {
        return character;
    }

    public void setCharacter(Character character) {
        this.character = character;
    }

    public void setRole() {
        this.role = role;
    }

    public Object getRole() {
        return role;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}

class Character {
    private String username;
    private String nickname;
    private String job;
    private int hp;
    private int mp;
    private int attack;
    private int defense;

    public Character(String username, String nickname, String job, int hp, int mp, int attack, int defense) {
        this.username = username;
        this.nickname = nickname;
        this.job = job;
        this.hp = hp;
        this.mp = mp;
        this.attack = attack;
        this.defense = defense;
    }

    public String getUsername() {
        return username;
    }

    public String getNickname() {
        return nickname;
    }

    public String getJob() {
        return job;
    }

    public int getHp() {
        return hp;
    }

    public int getMp() {
        return mp;
    }

    public int getAttack() {
        return attack;
    }

    public int getDefense() {
        return defense;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public void setJob(String job) {
        this.job = job;
    }

    public void setAttack(int attack) {
        this.attack = attack;
    }

    public void setJob(int mp) {
        this.mp = mp;
    }

    public void setHP(int hp) {
        this.hp = hp;
    }

    public void setDefense(int defense) {
        this.defense = defense;
    }

}
