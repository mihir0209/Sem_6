<?php
// Database connection
$con = mysqli_connect('localhost', 'root', 'Mihir0209', 'Student');

// Check if the connection was successful
if (!$con) {
    die("Database connection failed: " . mysqli_connect_error());
}

// Get the POST records safely
$txtfname = mysqli_real_escape_string($con, $_POST['txtfname']);
$txtmname = mysqli_real_escape_string($con, $_POST['mname']);
$txtlname = mysqli_real_escape_string($con, $_POST['lname']);
$txtpwd   = mysqli_real_escape_string($con, $_POST['txtpwd']);

$sql = "INSERT INTO `registration` (`fname`, `mname`, `lname`, `pwd`) 
        VALUES ('$txtfname', '$txtmname', '$txtlname', '$txtpwd')";

// Execute the insert query
if (mysqli_query($con, $sql)) {
    echo "✅ Contact Record Inserted Successfully! <br><br>";
} else {
    echo "❌ Error: " . mysqli_error($con);
}

// Fetch records from the database
$sql = "SELECT * FROM `registration`";
$result = mysqli_query($con, $sql);

// Check if records exist
if (mysqli_num_rows($result) > 0) {
    while ($row = mysqli_fetch_assoc($result)) {
        echo "EMP ID : " . $row['Id'] . " <br> ";
        echo "EMP First NAME : " . $row['fname'] . " <br> ";
        echo "EMP Middle Name : " . $row['mname'] . " <br> ";
        echo "EMP Last Name : " . $row['lname'] . " <br> ";
        echo "--------------------------------<br>";
    }
} else {
    echo "⚠️ No records found!";
}

// Close the connection
mysqli_close($con);
?>
