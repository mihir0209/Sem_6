<?php
$employee_name = array(
    "Amit Sharma", "Priya Verma", "Mihir Patil", "Sneha Patil", "Vikram Singh",
    "Neha Joshi", "Arun Nair", "Pooja Iyer", "Sandeep Reddy", "Kavita Das",
    "Rohan Mehta", "Anjali Gupta", "Manoj Choudhary", "Deepika Rao", "Harish Menon",
    "Swati Saxena", "Karan Malhotra", "Meena Pillai", "Suresh Babu", "Lavanya Gopal"
);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $searchName = isset($_POST["name"]) ? trim($_POST["name"]) : '';

    if ($searchName === '') {
        echo "<p style='color: orange; font-weight: bold;'>Please enter a name.</p>";
    } elseif (in_array($searchName, $employee_name)) {
        echo "<p style='color: green; font-weight: bold;'>$searchName exists in the database.</p>";
    } else {
        echo "<p style='color: red; font-weight: bold;'>$searchName not found.</p>";
    }
}
?>
