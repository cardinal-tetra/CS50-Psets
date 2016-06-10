<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_form.php", ["title" => "Change"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check old password is correct
        $query = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $hash = $query[0]["hash"];
        
        if (crypt($_POST["old"], $hash) !== $hash)
        {
            apologize("Enter correct old password");
        }
        
        // check new password
        if (empty($_POST["new"]))
        {
            apologize("Please enter new password");
        }
        
        // check confirmation
        if (empty($_POST["confirmation"]))
        {
            apologize("Please verify new password");
        }
        
        // check match
        if ($_POST["new"] !== $_POST["confirmation"])
        {
            apologize("Passwords do not match");
        }
        
        // update password
        if (query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new"]), $_SESSION["id"]) === false)
        {
            apologize("Unable to change password");
        }
        
        //  redirect
        redirect("index.php");                      
     }
    
?>
