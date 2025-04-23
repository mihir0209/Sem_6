package com.hibernate.demo;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import java.util.Scanner;

public class UserApp {
    public static void main(String[] args) {
        // Create session factory
        SessionFactory factory = new Configuration()
                                .configure("hibernate.cfg.xml")
                                .addAnnotatedClass(User.class)
                                .buildSessionFactory();
        
        // Create scanner for user input
        Scanner scanner = new Scanner(System.in);
        
        try {
            // Create a session
            Session session = factory.getCurrentSession();
            
            System.out.println("=== User Registration System ===");
            
            // Get user input
            System.out.print("Enter first name: ");
            String firstName = scanner.nextLine();
            
            System.out.print("Enter last name: ");
            String lastName = scanner.nextLine();
            
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            
            // Create a new user object
            User user = new User(firstName, lastName, email);
            
            // Begin transaction
            Transaction tx = session.beginTransaction();
            
            // Save the user
            System.out.println("Saving the user...");
            session.save(user);
            
            // Commit the transaction
            tx.commit();
            
            System.out.println("User saved successfully! Generated ID: " + user.getId());
            
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            scanner.close();
            factory.close();
        }
    }
}