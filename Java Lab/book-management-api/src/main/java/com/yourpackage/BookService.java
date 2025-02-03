package com.yourpackage;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import java.util.List;

public class BookService {
    private static EntityManagerFactory emf = Persistence.createEntityManagerFactory("bookdb");
    private static EntityManager em = emf.createEntityManager();

    public static List<Book> getBooks() {
        return em.createQuery("SELECT b FROM Book b", Book.class).getResultList();
    }

    public static void createBook(Book book) {
        em.getTransaction().begin();
        em.persist(book);
        em.getTransaction().commit();
    }

    public static void updateBook(Book book) {
        em.getTransaction().begin();
        em.merge(book);
        em.getTransaction().commit();
    }

    public static void deleteBook(String isbn) {
        Book book = em.find(Book.class, isbn);
        if (book != null) {
            em.getTransaction().begin();
            em.remove(book);
            em.getTransaction().commit();
        }
    }
}
