<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check they have properly registered
        if (empty($_POST["username"]))
        {
            apologize("Please enter username");
        }
        if (empty($_POST["password"]))
        {
            apologize("Please enter a password");
        }
        if (empty($_POST["confirmation"]))
        {
            apologize("Please verify your password");
        }
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match");
        }
        if (query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"])) === false)
        {
            apologize("Please try another username");
        }
        
        //  remember user id and redirect
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        $_SESSION["user_id"] = $id;
        redirect("index.php");                      
     }
    
?>
