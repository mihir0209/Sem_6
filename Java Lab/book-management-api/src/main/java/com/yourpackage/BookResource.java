package com.yourpackage;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.List;

@Path("/books")
public class BookResource {

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public List<Book> getBooks() {
        return BookService.getBooks(); // Assuming you have a BookService to manage data
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response createBook(Book book) {
        BookService.createBook(book); // Save the book
        return Response.status(Response.Status.CREATED).entity(book).build();
    }

    @PUT
    @Path("/{isbn}")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response updateBook(@PathParam("isbn") String isbn, Book book) {
        book.setIsbn(isbn);
        BookService.updateBook(book);
        return Response.ok(book).build();
    }

    @DELETE
    @Path("/{isbn}")
    public Response deleteBook(@PathParam("isbn") String isbn) {
        BookService.deleteBook(isbn);
        return Response.noContent().build();
    }
}
