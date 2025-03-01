<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="/struts-tags" prefix="s" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Login Page</title>
</head>
<body bgcolor="lightBlue">
    <s:form action="Welcome">
        <s:textfield name="userName" label="User Name" />
        <s:password name="password" label="Password" />
        <s:submit value="Say Hello" />
    </s:form>
</body>
</html>