package com.pbo;

abstract class Job {
    protected final String name;
    protected final int hp;
    protected final int mp;
    protected final int attack;
    protected final int defense;

    public Job(String name, int hp, int mp, int attack, int defense) {
        this.name = name;
        this.hp = hp;
        this.mp = mp;
        this.attack = attack;
        this.defense = defense;
    }

    public abstract void performSpecialAttack();

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

final class Warrior extends Job {
    public Warrior(String name, int hp, int mp, int attack, int defense) {
        super(name, hp, mp, attack, defense);
    }

    @Override
    public void performSpecialAttack() {
        // Implementasi spesifik untuk serangan khusus Warrior
    }
}

final class Assassin extends Job {
    public Assassin(String name, int hp, int mp, int attack, int defense) {
        super(name, hp, mp, attack, defense);
    }

    @Override
    public void performSpecialAttack() {
        // Implementasi spesifik untuk serangan khusus Assassin
    }
}

final class Fighter extends Job {
    public Fighter(String name, int hp, int mp, int attack, int defense) {
        super(name, hp, mp, attack, defense);
    }

    @Override
    public void performSpecialAttack() {
        // Implementasi spesifik untuk serangan khusus Fighter
    }
}

final class Paladin extends Job {
    public Paladin(String name, int hp, int mp, int attack, int defense) {
        super(name, hp, mp, attack, defense);
    }

    @Override
    public void performSpecialAttack() {
        // Implementasi spesifik untuk serangan khusus Paladin
    }
}
