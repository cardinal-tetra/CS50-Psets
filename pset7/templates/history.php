<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Time</th>
            <th>Symbol</th>
            <th>Quantity</th>
            <th>Price</th>
        </tr>
    </thead>
    
    <tbody>
           
<?php foreach ($positions as $position): ?>
    <tr>
        <td><?= $position["Transaction"] ?></td>
        <td><?= $position["Time"] ?></td>
        <td><?= $position["Symbol"] ?></td>
        <td><?= $position["Quantity"] ?></td>
        <td><?= "$" . number_format($position["Price"], 2, '.', ',') ?></td>
    </tr>
<?php endforeach ?>

    </tbody>
    
</table>
