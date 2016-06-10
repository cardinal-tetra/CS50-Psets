<?php

    //  configuration
    require("../includes/config.php");
    
    //  if user has reached page via get
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }

    //  if user has reached page via post
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check shares exist
        if (lookup($_POST["symbol"]) == false)
        {
            apologize("Please specify a valid symbol");
        }
        // check for valid quantity
        if (preg_match("/^\d+$/", $_POST["quantity"]) == false)
        {
            apologize("Please specify a correct quantity");
        }
        
        // check there is enough cash
        $user = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $balance = $user[0]["cash"];
        
        $quantity = $_POST["quantity"];
        $lookup = lookup($_POST["symbol"]);
        $price = $lookup["price"];
        $total_cost = $price * $quantity;
        
        if ($total_cost > $balance)
        {
            apologize("You do not have enough money");
        }
        
        // update portfolio
        if (query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["quantity"]) === false)
        {
            apologize("Purchase has been unsuccessful");
        }
        
        // update cash balance
        if (query("UPDATE users SET cash = cash - ? WHERE id = ?", $total_cost, $_SESSION["id"]) === false)
        {
            apologize("You haven't paid for the purchase yet");
        }
        
        // update history
        if (query("INSERT INTO history (ID, Transaction, Symbol, Quantity, Price) VALUES(?, 'Purchase', ?, ?, ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $quantity, $price) === false)
        {
            apologize("Transaction history not recorded");
        }
        
        // redirect
        redirect("index.php");
    }
    
?>
