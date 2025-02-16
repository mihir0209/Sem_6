package com.example.action;

import com.opensymphony.xwork2.ActionSupport;

public class HelloAction extends ActionSupport {
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String execute() {
        if (name == null || name.trim().isEmpty()) {
            return ERROR;
        }
        return SUCCESS;
    }
}
