package edu.msu.cse476.cloudhatter.Cloud.Models;

import org.simpleframework.xml.Attribute;

public class DeleteResult {
    @Attribute
    private String status;

    @Attribute(name = "msg", required = false)
    private String message;

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public DeleteResult() {}

    public DeleteResult(String status, String msg) {
        this.status = status;
        this.message = msg;
    }
}
