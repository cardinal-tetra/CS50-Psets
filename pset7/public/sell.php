<?php

    //  configuration
    require("../includes/config.php");
    
    //  if user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]); 
        render("sell_form.php", ["title" => "Sell", "rows" => $rows]);
    }
    
    //  if user reached page via POST
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //  check that user specified shares
        if (empty($_POST["symbol"]))
        {
            apologize("Please specify a company");
        }
        
        //  find quantity of shares owned
        $find_quantity = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $quantity = $find_quantity[0]["shares"];
        
        //  Update portfolio
        if (query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]) === false)
        {
            apologize("Sale has been unsuccesful, please try again");
        }
        
        //  Calculate proceeds
        $find_price = lookup($_POST["symbol"]);        
        $price = $find_price["price"];
        $proceeds = $quantity * $price;

        //  Update cash balance
        if (query("UPDATE users SET cash = cash + ? WHERE id = ?", $proceeds, $_SESSION["id"]) === false)
        {
            apologize("You have not received proceeds, please contact us");
        }
        
        //  Update history
        if (query("INSERT INTO history (ID, Transaction, Symbol, Quantity, Price) VALUES (?, 'Sale', ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $quantity, $price) === false)
        {
            apologize("Transaction history not recorded");
        }
        
        //  Redirect
        redirect("index.php");
    }
?>
