<ul class="nav nav-pills">
    <li><a href="quote.php"><strong>Quote</strong></a></li>
    <li><a href="buy.php"><strong>Buy</strong></a></li>
    <li><a href="sell.php"><strong>Sell</strong></a></li>
    <li><a href="history.php"><strong>History</strong></a></li>
    <li><a href="logout.php">Log Out</a></li>
    <li><a href="change.php">Change Password</a></li>
</ul>

<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
    </thead>
    
    <tbody>
           
<?php foreach ($positions as $position): ?>
    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= "$" . number_format($position["price"], 2, '.', ',') ?></td>
        <td><?= "$" . number_format($position["price"] * $position["shares"], 2, '.', ',') ?></td>
    </tr>
<?php endforeach ?>

    <tr>
        <td>CASH</td>
        <td></td>
        <td></td>
        <td></td>
        <td><?= "$" . number_format($balance, 2, '.', ',') ?></td>
    </tr>
    
    </tbody>
    
</table>
