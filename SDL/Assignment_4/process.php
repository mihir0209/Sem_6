<?php
session_start(); // Start session to store result temporarily

$employee_name = array("Amit Sharma", "Priya Verma", "Mihir Patil", "Sneha Patil", "Vikram Singh",
    "Neha Joshi", "Arun Nair", "Pooja Iyer", "Sandeep Reddy", "Kavita Das",
    "Rohan Mehta", "Anjali Gupta", "Manoj Choudhary", "Deepika Rao", "Harish Menon",
    "Swati Saxena", "Karan Malhotra", "Meena Pillai", "Suresh Babu", "Lavanya Gopal");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $searchName = isset($_POST["name"]) ? trim($_POST["name"]) : '';

    if ($searchName === '') {
        $_SESSION["searchResult"] = "<p style='color: orange; font-weight: bold;'>Please enter a name.</p>";
    } elseif (in_array($searchName, $employee_name)) {
        $_SESSION["searchResult"] = "<p style='color: green; font-weight: bold;'>$searchName exists in the array.</p>";
    } else {
        $_SESSION["searchResult"] = "<p style='color: red; font-weight: bold;'>$searchName does not exist in the array.</p>";
    }

    header("Location: process.php"); // Redirect back to main page
    exit();
}
?>
<?php session_start(); ?>
<!DOCTYPE html>
<html>
<head>
    <title>Search Employee</title>
    <style>
        body { font-family: Arial, sans-serif; }
        .result { margin-top: 10px; font-size: 18px; font-weight: bold; }
    </style>
</head>
<body>

<h2>Search Employee</h2>
<form method="post" action="process.php">
    <label for="name">Enter Employee Name:</label>
    <input type="text" id="name" name="name" required>
    <button type="submit">Search</button>
</form>

<!-- Display search result -->
<div id="result" class="result">
    <?php
    if (isset($_SESSION["searchResult"])) {
        echo $_SESSION["searchResult"];
        unset($_SESSION["searchResult"]); // Clear session after displaying result
    }
    ?>
</div>

</body>
</html>
