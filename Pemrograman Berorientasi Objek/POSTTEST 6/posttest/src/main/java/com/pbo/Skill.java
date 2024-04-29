package com.pbo;

public class Skill {
        private String name;
        private int power;
    
        public Skill(String name, int power) {
            this.name = name;
            this.power = power;
        }
    
        public String getName() {
            return name;
        }
    
        public int getPower() {
            return power;
        }
}
