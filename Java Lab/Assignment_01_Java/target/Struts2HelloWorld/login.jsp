<%@ page import="java.sql.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: 'Roboto', sans-serif;
            background: linear-gradient(135deg, #6a11cb, #2575fc);
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            color: #fff;
        }
        .container {
            background-color: rgba(255, 255, 255, 0.9);
            border-radius: 20px;
            box-shadow: 0 15px 30px rgba(0, 0, 0, 0.2);
            padding: 40px;
            width: 100%;
            max-width: 400px;
            text-align: center;
            position: relative;
        }
        .container1 {
            background-color: rgba(0, 0, 0, 0.9);
            border-radius: 20px;
            box-shadow: 0 15px 30px rgba(0, 0, 0, 0.2);
            padding: 40px;
            width: 100%;
            max-width: 400px;
            text-align: center;
            position: absolute;
            top: 50px;
            right: 50px;
            width: 90px;
            height: 80px;
        }
        h2 {
            margin-bottom: 30px;
            font-size: 32px;
            color: #6a11cb;
        }
        label {
            display: block;
            margin-bottom: 10px;
            font-weight: 500;
            color: #333;
        }
        input[type="text"], input[type="password"] {
            width: calc(100% - 20px);
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 10px;
            border: none;
            box-shadow: inset 0 1px 5px rgba(0,0,0,0.1);
        }
        input[type="text"]:focus, input[type="password"]:focus {
            outline: none;
            box-shadow: inset 0 1px 10px rgba(106,17,203,0.5);
        }
        input[type="submit"] {
            background-color: #6a11cb;
            color: white;
            border-radius: 10px;
            border: none;
            cursor: pointer;
            padding: 15px;
            font-size: 18px;
            transition: background-color 0.3s ease, transform 0.3s ease;
        }
        input[type="submit"]:hover {
            background-color: #2575fc;
            transform: translateY(-3px);
        }
        .message {
            margin-top: 20px;
        }
        .error {
            color: #dc3545;
        }
        .success {
            color: #28a745;
        }
        .logo {
            position: absolute;
            top: 20px;
            right: 20px;
            width: 120px;
        }
        .form-footer {
            color: black;
            margin-top: 15px;
            font-size: 14px;
        }
        .form-footer a {
            color: #c60be7e2;
            text-decoration: none;
            font-weight: 500;
        }
        .form-footer a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>

    <div class="container1">
        <img src="<%= request.getContextPath() %>/images/logo.png" alt="Logo" class="logo">
    </div>
    <div class="container">
        
        <h2>Welcome Back!</h2>
        
        <form action="login.jsp" method="post" autocomplete="off">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username" required 
                   value="<%= request.getParameter("username") != null ? request.getParameter("username") : "" %>">
            
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" required>
            
            <input type="submit" value="Login">
        </form>
        
       <p class="form-footer">Don't have an account? <a href="register.jsp">Register now</a></p>
        <div class="message">
           <%
           String username = request.getParameter("username");
           String password = request.getParameter("password");

           if (username != null && password != null) {
               try {
                   Class.forName("com.mysql.cj.jdbc.Driver");
                   Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/user_db", "root", "Mihir0209");

                   String query = "SELECT * FROM users WHERE username = ? AND password = ?";
                   PreparedStatement stmt = conn.prepareStatement(query);
                   stmt.setString(1, username);
                   stmt.setString(2, password);
                   
                   ResultSet rs = stmt.executeQuery();
                   
                   if (rs.next()) {
                       session.setAttribute("username", username); 
                       session.setAttribute("successMessage", "Login successful.");
                       response.sendRedirect("welcome.jsp");
                   } else {
                       out.println("<p class='error'>Invalid username or password.</p>");
                   }

                   rs.close();
                   stmt.close();
                   conn.close();
               } catch (Exception e) {
                   e.printStackTrace();
                   out.println("<p class='error'>Error: " + e.getMessage() + "</p>");
               }
           }
           %>
       </div>
    </div>
</body>
</html>
