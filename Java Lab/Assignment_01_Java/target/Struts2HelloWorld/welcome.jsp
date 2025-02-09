<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
String successMessage = (String) session.getAttribute("success");
session.removeAttribute("success"); // Remove message after displaying
%>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome</title>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@600&display=swap" rel="stylesheet">
    <style>
        body {
            margin: 0;
            font-family: 'Poppins', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background: linear-gradient(135deg, #6a11cb, #2575fc);
            color: #fff;
        }
        .container {
            background-color: rgba(255, 255, 255, 0.9);
            padding: 40px;
            border-radius: 20px;
            box-shadow: 0 15px 30px rgba(0, 0, 0, 0.2);
            text-align: center;
            position: relative;
        }
        h1 {
            color: #6a11cb;
            margin-bottom: 20px;
        }
        p {
            color: #333;
            font-size: 18px;
        }
        .logo {
            position: absolute;
            top: 20px;
            right: 20px;
            width: 120px;
        }
        .message-container {
            display: none;
            background-color: #28a745;
            color: white;
            padding: 15px;
            border-radius: 5px;
            width: 300px;
            margin: 10px auto;
            font-weight: bold;
        }
        .fade-out {
            animation: fadeOut 2s forwards;
        }
        @keyframes fadeOut {
            0% { opacity: 1; }
            100% { opacity: 0; display: none; }
        }
        .logout-btn {
            display: inline-block;
            margin-top: 20px;
            padding: 10px 20px;
            background-color: #ff4757;
            color: white;
            text-decoration: none;
            font-weight: bold;
            border-radius: 5px;
            transition: 0.3s;
        }
        .logout-btn:hover {
            background-color: #e84118;
        }
    </style>
    <script>
        window.onload = function() {
            let messageContainer = document.getElementById("successMessage");
            if (messageContainer) {
                messageContainer.style.display = "block";
                setTimeout(() => {
                    messageContainer.classList.add("fade-out");
                }, 2000);
            }
        };
    </script>
</head>
<body>
    <img src="<%= request.getContextPath() %>/images/logo.png" alt="Logo" class="logo">

    <div class="container">
        <% if (successMessage != null) { %>
            <div id="successMessage" class="message-container"><%= successMessage %></div>
        <% } %>

        <h1>Welcome, <%= session.getAttribute("username") %>!</h1>
        <p>You have successfully entered this portal.</p>
        <a href="logout.jsp" class="logout-btn">Logout</a>
    </div>
</body>
</html>
