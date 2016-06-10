<?php
    
    require("../includes/config.php");

    // where user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => "Get Quote"]); 
    }
    
    // where user reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol");  
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            if ($stock == false)
            {
                apologize("Please provide valid symbol");
            }
        }
               
        render("quote.php", ["title" => "Quote", "name" => $stock["name"], "symbol" => strtoupper($stock["symbol"]), "price" => number_format($stock["price"], 2, '.', '')]);       
    }    

?>
