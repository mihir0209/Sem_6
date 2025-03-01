package com.example;

import com.opensymphony.xwork2.ActionSupport;

public class WelcomeAction extends ActionSupport {
    private String userName;

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String execute() {
        return SUCCESS;
    }
}