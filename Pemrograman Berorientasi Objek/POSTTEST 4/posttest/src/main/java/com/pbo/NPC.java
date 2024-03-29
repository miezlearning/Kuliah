package com.pbo;

import java.util.Random;

public class NPC {
    private String name;
    private int health;
    private int attackPower;
    private int defensePower;

    // Constructor
    public NPC(String name, int health, int attackPower, int defensePower) {
        this.name = name;
        this.health = health;
        this.attackPower = attackPower;
        this.defensePower = defensePower;
    }

    // Getter methods
    public String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    // Method to calculate damage taken by NPC
    public void takeDamage(int damage) {
        int actualDamage = Math.max(damage - defensePower, 0); // Ensure damage doesn't go below 0
        health -= actualDamage;
    }

    // Method to calculate NPC's attack damage
    public int calculateDamage() {
        Random random = new Random();
        int damage = random.nextInt(attackPower) + 1; // Random damage between 1 and attackPower
        return damage;
    }

    // Getter method for attackPower
    public int getAttackPower() {
        return attackPower;
    }
}
