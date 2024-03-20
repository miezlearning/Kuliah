package com.pbo;

import java.util.Random;
import java.util.Scanner;

public class Dungeon {
    public static void startDungeon(Character player) {
        // Assuming there's an NPC instance representing the NPC in the dungeon
        NPC npc = new NPC("Evil Wizard", 200, 30, 2); // Example NPC

        // Display introduction
        System.out.println("You entered the dungeon.");
        System.out.println("You encountered " + npc.getName() + ". Prepare for battle!");

        // Start battle
        boolean playerWon = battle(player, npc);

        // Handle battle outcome
        if (playerWon) {
            System.out.println("You defeated " + npc.getName() + ". Congratulations!");
            // Handle rewards or progression
        } else {
            System.out.println("You were defeated by " + npc.getName() + ". Game Over!");
            // Handle game over condition
        }
    }

    private static boolean battle(Character player, NPC npc) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();
        
        while (player.getHp() > 0 && npc.getHealth() > 0) {
            // Player's turn
            System.out.println("Your turn!");
            System.out.println("Choose a skill:");
            System.out.println("1. Normal Attack");
            
            // Display skills based on player's job
            switch (player.getJob()) {
                case "Mage":
                    System.out.println("2. Fireball");
                    System.out.println("3. Ice Shard");
                    break;
                case "Assassin":
                    System.out.println("2. Backstab");
                    System.out.println("3. Poison Dagger");
                    break;
                case "Fighter":
                    System.out.println("2. Berserk");
                    System.out.println("3. Smash");
                    break;
                case "Paladin":
                    System.out.println("2. Divine Strike");
                    System.out.println("3. Holy Shield");
                    break;
                default:
                    System.out.println("Invalid job. You can only perform a normal attack.");
                    break;
            }
            
            System.out.print("Choice: ");
            int choice = scanner.nextInt();
    
            int playerDamage = 0;
            switch (choice) {
                case 1:
                    playerDamage = calculateDamage(player.getAttack());
                    break;
                case 2:
                    // Check player's job and use corresponding skill
                    if (player.getJob().equals("Mage")) {
                        playerDamage = player.useSkill("Fireball");
                    } else if (player.getJob().equals("Assassin")) {
                        playerDamage = player.useSkill("Backstab");
                    } else if (player.getJob().equals("Fighter")) {
                        playerDamage = player.useSkill("Berserk");
                    } else if (player.getJob().equals("Paladin")) {
                        playerDamage = player.useSkill("Divine Strike");
                    }
                    break;
                case 3:
                    // Check player's job and use corresponding skill
                    if (player.getJob().equals("Mage")) {
                        playerDamage = player.useSkill("Ice Shard");
                    } else if (player.getJob().equals("Assassin")) {
                        playerDamage = player.useSkill("Poison Dagger");
                    } else if (player.getJob().equals("Fighter")) {
                        playerDamage = player.useSkill("Smash");
                    } else if (player.getJob().equals("Paladin")) {
                        playerDamage = player.useSkill("Holy Shield");
                    }
                    break;
                default:
                    System.out.println("Invalid choice. You lost your turn.");
                    break;
            }
    
            npc.takeDamage(playerDamage); // Reduce NPC's health
            System.out.println("You dealt " + playerDamage + " damage to " + npc.getName() + ".");
    
            if (npc.getHealth() <= 0) {
                return true; // Player won
            }
    
            // NPC's turn
            int npcDamage = calculateDamage(npc.getAttackPower());
            player.takeDamage(npcDamage); // Reduce player's health
            System.out.println(npc.getName() + " dealt " + npcDamage + " damage to you.");
    
            if (player.getHp() <= 0) {
                return false; // Player lost
            }
    
            // Display updated health of both player and NPC
            System.out.println("Your Health: " + player.getHp());
            System.out.println(npc.getName() + "'s Health: " + npc.getHealth());
        }
        return false; // Should not reach here if battle logic is correct
    }
    
    
    private static int calculateDamage(int attackPower) {
        Random random = new Random();
        // Generate random damage between 1 and attackPower
        return random.nextInt(attackPower) + 1;
    }
    
    
}
