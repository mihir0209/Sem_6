<%@ taglib uri="/struts-tags" prefix="s" %>
<html>
<head>
    <title>Struts 2 Example</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 100px;
        }
        form {
            background: #f4f4f4;
            padding: 20px;
            display: inline-block;
            border-radius: 10px;
        }
        input[type="text"], input[type="submit"] {
            padding: 10px;
            margin: 10px;
        }
    </style>
</head>
<body>
    <h2>Enter your name</h2>
    <form action="hello.action" method="post">
        Name: <input type="text" name="name"/>
        <input type="submit" value="Submit"/>
    </form>
</body>
</html>
