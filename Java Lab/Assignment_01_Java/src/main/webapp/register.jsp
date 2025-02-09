<%@ page import="java.sql.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600&display=swap" rel="stylesheet">
    <style>
        body {
            margin: 0;
            font-family: 'Poppins', sans-serif;
            background: linear-gradient(135deg, #ff7eb3, #ff758c);
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            color: #fff;
        }
        .container {
            background-color: rgba(255, 255, 255, 0.95);
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
            text-align: center;
            position: absolute;
            top: 50px;
            right: 50px;
            width: 90px;
            height: 80px;
        }
        h2 {
            margin-bottom: 20px;
            font-size: 30px;
            font-weight: 600;
            color: #ff758c;
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
            box-shadow: inset 0 1px 10px rgba(255,117,140,0.5);
        }
        input[type="submit"] {
            background-color: #ff758c;
            color: white;
            border-radius: 10px;
            border: none;
            cursor: pointer;
            padding: 15px;
            font-size: 18px;
            font-weight: bold;
            transition: background-color 0.3s ease, transform 0.3s ease;
        }
        input[type="submit"]:hover {
            background-color: #ff4a68;
            transform: translateY(-3px);
        }
        .message {
            margin-top: 20px;
        }
        .error {
            color: #dc3545; /* Red for errors */
        }
        .success {
            color: #28a745; /* Green for success */
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
        
        <h2>Create Your Account</h2>
        
        <form action="register.jsp" method="post">
            
           <label for="username">Username:</label>
           <input type="text" id="username" name="username" required 
                  value="<%= request.getParameter("username") != null ? request.getParameter("username") : "" %>">
           
           <label for="password">Password:</label>
           <input type="password" id="password" name="password" required>
           
           <input type="submit" value="Register">

       </form>
       <p class="form-footer">Already have an account? <a href="login.jsp">Log in now</a></p>
       <div class="message">
           <%
           String username = request.getParameter("username");
           String password = request.getParameter("password");

           if (username != null && password != null) {
               try {
                   Class.forName("com.mysql.cj.jdbc.Driver");
                   Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/user_db", "root", "Mihir0209");

                   String checkQuery = "SELECT COUNT(*) FROM users WHERE username = ?";
                   PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
                   checkStmt.setString(1, username);
                   ResultSet checkRs = checkStmt.executeQuery();
                   checkRs.next();

                   if (checkRs.getInt(1) > 0) {
                       out.println("<p class='error'>Username already exists. Please choose another.</p>");
                   } else {
                       String insertQuery = "INSERT INTO users (username, password) VALUES (?, ?)";
                       PreparedStatement insertStmt = conn.prepareStatement(insertQuery);
                       insertStmt.setString(1, username);
                       insertStmt.setString(2, password); 

                       int result = insertStmt.executeUpdate();
                       
                       if (result > 0) {
                           session.setAttribute("username", username);
                           session.setAttribute("successMessage", "Registration successful!");
                           response.sendRedirect("welcome.jsp");
                       } else {
                           out.println("<p class='error'>Registration failed. Try again.</p>");
                       }

                       insertStmt.close();
                   }

                   checkRs.close();
                   checkStmt.close();
                   conn.close();
               } catch (Exception e) {
                   e.printStackTrace();
                   out.println("<p class='error'>Error occurred! " + e.getMessage() + "</p>");
               }
           }
           %>
       </div>
   </div>
</body>
</html>
