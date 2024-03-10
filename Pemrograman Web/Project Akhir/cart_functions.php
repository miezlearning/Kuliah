<?php

include('FUNCTION/koneksi.php');

// Ensure $_SESSION['user_id'] is set before using it
$user_id = isset($_SESSION['user_id']) ? $_SESSION['user_id'] : null;

function addToCart($user_id, $product_id, $quantity) {
    global $conn;

    // Use prepared statements to prevent SQL injection
    $query = "SELECT * FROM shopping_cart WHERE user_id = ? AND product_id = ?";
    $stmt = mysqli_prepare($conn, $query);
    mysqli_stmt_bind_param($stmt, "ii", $user_id, $product_id);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);

    if (mysqli_num_rows($result) > 0) {
        $update_query = "UPDATE shopping_cart SET quantity = quantity + ? WHERE user_id = ? AND product_id = ?";
        $update_stmt = mysqli_prepare($conn, $update_query);
        mysqli_stmt_bind_param($update_stmt, "iii", $quantity, $user_id, $product_id);
        mysqli_stmt_execute($update_stmt);
    } else {
        $insert_query = "INSERT INTO shopping_cart (user_id, product_id, quantity) VALUES (?, ?, ?)";
        $insert_stmt = mysqli_prepare($conn, $insert_query);
        mysqli_stmt_bind_param($insert_stmt, "iii", $user_id, $product_id, $quantity);
        mysqli_stmt_execute($insert_stmt);
    }
}

function getCart($user_id) {
    global $conn;

    // Use prepared statements to prevent SQL injection
    $query = "SELECT * FROM shopping_cart WHERE user_id = ?";
    $stmt = mysqli_prepare($conn, $query);
    mysqli_stmt_bind_param($stmt, "i", $user_id);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);

    $cart = array();
    while ($row = mysqli_fetch_assoc($result)) {
        $cart[] = $row;
    }

    return $cart;
}
function saveCartToDatabase($user_id, $cart) {
    global $conn;

    // Update or insert cart data into the database based on your logic
    // Use prepared statements to prevent SQL injection

    foreach ($cart as $item) {
        if ($item['quantity'] > 0) {
            // Update the quantity
            $update_query = "UPDATE shopping_cart SET quantity = ? WHERE user_id = ? AND product_id = ?";
            $update_stmt = mysqli_prepare($conn, $update_query);
            mysqli_stmt_bind_param($update_stmt, "iii", $item['quantity'], $user_id, $item['product_id']);
            mysqli_stmt_execute($update_stmt);
    
            if (mysqli_affected_rows($conn) == 0) {
                // If no rows were affected, insert a new record
                $insert_query = "INSERT INTO shopping_cart (user_id, product_id, quantity) VALUES (?, ?, ?)";
                $insert_stmt = mysqli_prepare($conn, $insert_query);
                mysqli_stmt_bind_param($insert_stmt, "iii", $user_id, $item['product_id'], $item['quantity']);
                mysqli_stmt_execute($insert_stmt);
            }
        } else {
            // Quantity is zero, delete the record
            $delete_query = "DELETE FROM shopping_cart WHERE user_id = ? AND product_id = ?";
            $delete_stmt = mysqli_prepare($conn, $delete_query);
            mysqli_stmt_bind_param($delete_stmt, "ii", $user_id, $item['product_id']);
            mysqli_stmt_execute($delete_stmt);
        }
    }
    
}
?>