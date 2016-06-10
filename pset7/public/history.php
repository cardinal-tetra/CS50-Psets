<?php

    require("../includes/config.php");
    
    //  get information
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    //  store information
    $positions = [];
    
    foreach ($rows as $row)
    {
        $positions[] = [
        "Transaction" => $row["Transaction"],
        "Time" => $row["Time"],
        "Symbol" => $row["Symbol"],
        "Quantity" => $row["Quantity"],
        "Price" => $row["Price"],
        ];    
    }
    
    //  render history  
    render("history.php",["title" => "History", "positions" => $positions]);

?>
