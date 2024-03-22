package com.pbo;

import java.util.HashMap;
import java.util.Map;

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
    private Map<String, Skill> skills; // Map to store skills based on job

    public Character(String username, String nickname, String job, int hp, int mp, int attack, int defense) {
        this.username = username;
        this.nickname = nickname;
        this.job = job;
        this.hp = hp;
        this.mp = mp;
        this.attack = attack;
        this.defense = defense;
        this.skills = new HashMap<>();
        initializeSkills(); 
    }

    private void initializeSkills() {
        switch (job) {
            case "Mage":
                skills.put("Fireball", new Skill("Fireball", 50));
                skills.put("Ice Shard", new Skill("Ice Shard", 40));
                break;
            case "Assassin":
                skills.put("Backstab", new Skill("Backstab", 60));
                skills.put("Poison Dagger", new Skill("Poison Dagger", 30));
                break;
            case "Fighter":
                skills.put("Berserk", new Skill("Berserk", 70));
                skills.put("Smash", new Skill("Smash", 40));
                break;
            case "Paladin":
                skills.put("Divine Strike", new Skill("Divine Strike", 80));
                skills.put("Holy Shield", new Skill("Holy Shield", 30));
                break;
            default:
                // Default skills for other jobs
                skills.put("Normal Attack", new Skill("Normal Attack", 20));
        }
    }

    // Method to use a skill
    public int useSkill(String skillName) {
        Skill skill = skills.get(skillName);
        if (skill != null) {
            return skill.getPower();
        } else {
            System.out.println("No such skill found.");
            return 0;
        }
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

    public void takeDamage(int damage) {
        // Reduce the character's health by the amount of damage taken
        hp -= damage;
        
        // Ensure health doesn't go below 0
        if (hp < 0) {
            hp = 0;
        }
    }

    
    

}
