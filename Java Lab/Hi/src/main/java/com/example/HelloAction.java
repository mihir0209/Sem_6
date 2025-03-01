package com.example;

public class HelloAction {
    private String message;

    public String execute() {
        message = "Hello, World!";
        return "success";
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}