package com.pbo;

class Job {
    private String name;
    private int hp;
    private int mp;
    private int attack;
    private int defense;

    public Job(String name, int hp, int mp, int attack, int defense) {
        this.name = name;
        this.hp = hp;
        this.mp = mp;
        this.attack = attack;
        this.defense = defense;
    }
    public String getName() {
        return name;
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
}