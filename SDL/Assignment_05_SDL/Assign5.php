<?php
define('PI', 3.14);

interface Shape
{
    function calc_area($r, $h);
    function calc_vol($r, $h);
}

class Sphere implements Shape
{
    function calc_area($r, $h)
    {
        return 4 * PI * $r * $r;
    }

    function calc_vol($r, $h)
    {
        return (4 / 3) * PI * $r * $r * $r;
    }
}

class Cylinder implements Shape
{
    function calc_area($r, $h)
    {
        return 2 * PI * $r * ($r + $h);
    }

    function calc_vol($r, $h)
    {
        return PI * $r * $r * $h;
    }
}

class Cone implements Shape
{
    function calc_area($r, $h)
    {
        return 0.5 * $r * $r * $h;
    }

    function calc_vol($r, $h)
    {
        return (1 / 3) * PI * $r * $r * $h;
    }
}

$op = isset($_GET['op']) ? $_GET['op'] : null;
$r = isset($_GET['r']) ? (float)$_GET['r'] : 0;
$h = isset($_GET['h']) ? (float)$_GET['h'] : 0;
$r1 = isset($_GET['r1']) ? (float)$_GET['r1'] : 0;

$result = "";

switch ($op) {
    case 1:
        $ob = new Cone();
        $area = $ob->calc_area($r, $h);
        $volume = $ob->calc_vol($r, $h);
        $shape = "Cone";
        break;

    case 2:
        $ob = new Cylinder();
        $area = $ob->calc_area($r, $h);
        $volume = $ob->calc_vol($r, $h);
        $shape = "Cylinder";
        break;

    case 3:
        $ob = new Sphere();
        $area = $ob->calc_area($r1, 0); // Height is not used in sphere calculations
        $volume = $ob->calc_vol($r1, 0);
        $shape = "Sphere";
        break;

    default:
        $result = "<p style='color: red; font-weight: bold;'>Invalid operation.</p>";
        $shape = "";
        $area = $volume = null;
}

if ($shape) {
    $result = "<p><strong>Shape:</strong> $shape</p>";
    $result .= "<p><strong>Area:</strong> " . number_format($area, 2) . " sq. units</p>";
    $result .= "<p><strong>Volume:</strong> " . number_format($volume, 2) . " cubic units</p>";
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Calculation Result</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 350px;
        }

        h2 {
            color: #333;
            border-bottom: 2px solid #007bff;
            padding-bottom: 5px;
            margin-bottom: 15px;
        }

        p {
            font-size: 18px;
            color: #333;
            margin: 5px 0;
        }

        .result-box {
            background: #e9f5ff;
            padding: 15px;
            border-radius: 5px;
            margin-top: 10px;
            box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.1);
        }

        .back-btn {
            background-color: #007bff;
            color: white;
            padding: 10px;
            font-size: 16px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: 0.3s;
            margin-top: 15px;
            width: 100%;
            text-decoration: none;
            display: inline-block;
            text-align: center;
        }

        .back-btn:hover {
            background-color: #0056b3;
        }
    </style>
</head>
<body>

<div class="container">
    <h2>Calculation Result</h2>
    <div class="result-box">
        <?= $result ?>
    </div>
    <a href="Assign5.html" class="back-btn">Go Back</a>
</div>

</body>
</html>
