/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

/**
 *
 * @author a19khan
 */

public class lab9 {
    
    public static int tally = 0;
    public static final int numOfPhilosophers = 5;
    public static Philosopher[] philosophers;
    public enum phil_state {THINKING, HUNGRY, EATING};
    public static Semaphore forks;
    
    public static void main(String args[]){
        
        int i=0;
        forks = new Semaphore(numOfPhilosophers);
        philosophers = new Philosopher[numOfPhilosophers];
        
        while (i < numOfPhilosophers){
            philosophers[i] = new Philosopher();
            i++;
        }
        
        for (int x=0; x < numOfPhilosophers; x++){
            philosophers[x].start();
        }
        
        while(tally >= numOfPhilosophers){
            try{
                while (i < numOfPhilosophers){
                    philosophers[i].join();
                    i++;
                }
            }catch(Exception ex){
                System.out.println("Exception!");
            }
            System.out.println("Every Philospher has eaten!");
        }
        
    }

    public static class Philosopher extends Thread{
        
        private int identifier = 0;
        private phil_state state;
        private int leftNeighbor;
        private int rightNeighbor;
        private static int M_ID = 0;
        
        public Philosopher(){
            
            this.identifier = M_ID; M_ID++;
            state = phil_state.HUNGRY;
           
            if (this.identifier == (numOfPhilosophers-1)){
                leftNeighbor = numOfPhilosophers-2;
                rightNeighbor = 0;
            }
            else if (this.identifier != 0){
                leftNeighbor = this.identifier - 1;
                rightNeighbor = this.identifier + 1;
            }
            else {
                leftNeighbor = numOfPhilosophers-1;
                rightNeighbor = 1;
            }
    }
        
    @Override
    public String toString(){
        
        return "Philosopher: " + this.identifier + " State: " + this.state.toString();
        
    }
        public synchronized void eating(){
        
        this.state = phil_state.EATING;
        System.out.println(this.toString());
        
        try{
            Thread.sleep(7);
        }catch(Exception ex){
            System.out.println("Exception related to eating!");
        }
    }
        
    public synchronized void thinking(){
        
        this.state = phil_state.THINKING;
        System.out.println(this.toString());
        
        try{
            wait(7);
        }catch(Exception ex){
            System.out.println("Exception related to thinking!");
        }
    }
     
    public synchronized void putForks(){
        
        this.state = phil_state.THINKING;
        
        try{
            forks.up();
        }catch(InterruptedException ie){
            System.out.println("Putting Fork related exception!");
        }
        
        tally++;
        }
    
    public synchronized void takeForks(){
        
        System.out.println(this.toString());
        System.out.println("Fork retrieval in process.....\n");
        
        while(philosophers[leftNeighbor].getPhilState() == phil_state.EATING || philosophers[rightNeighbor].getPhilState() == phil_state.EATING){
            System.out.println(this.identifier + "'s fork is being utilized!\n");
            thinking();
        }
        
        if(philosophers[leftNeighbor].getPhilState() != phil_state.EATING || philosophers[rightNeighbor].getPhilState() != phil_state.EATING){
            
            try{
                forks.down();
            }catch(InterruptedException ie){
                System.out.println("Taking fork related exception!\n");
            }
            
            this.state = phil_state.EATING;
            System.out.println(this.identifier + "'s Fork has been succesfully retrieved!\n");
        }
    }
    
    public phil_state getPhilState(){
        return this.state;
    }
    
    @Override
    public void run(){
        thinking();
        takeForks();
        eating();
        putForks();
        System.out.println(this.toString());
    }
   
    }

}