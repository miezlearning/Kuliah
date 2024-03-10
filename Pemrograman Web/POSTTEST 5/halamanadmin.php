
<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: login.php'); // Jika tidak ada sesi, kembali ke halaman login
    exit();
}
?>

<!-- KEKURANGNA PROGRAM INI, TIDAK MENGGUNAKAN ROLE -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard</title>
    <link rel="stylesheet" href="CSS/admin.css">
</head>
<body>
    <h1>Admin Dashboard <a href="FUNCTION/logout.php">Logout</a></h1>
    
    <!-- Tambah Pengguna Form -->
    <h2>Tambah Pengguna</h2>
    <form method="post" action="FUNCTION/admin.php">
        <label for="new_username">Username:</label>
        <input type="text" name="new_username" id="new_username" required>
        <label for="new_password">Password:</label>
        <input type="password" name="new_password" id="new_password" required>
        <button type="submit" name="submit">Tambah</button>
    </form>

    <!-- Tampilkan Data Pengguna -->
    <h2>Data Pengguna</h2>
    <table>
        <tr>
            <th>ID</th>
            <th>Username</th>
            <th>Password</th>
            <th>Action</th>
        </tr>
        <!-- Tampilkan data pengguna dari database (menggunakan PHP) -->
        <?php
        include 'FUNCTION/koneksi.php';
        $query = "SELECT * FROM posttest";
        $result = $conn->query($query);
        while ($row = $result->fetch_assoc()) {
            if ($row['username'] === 'admin' && $row['password'] === 'admin') {
                continue;
            } else {
            echo "<tr>";
            echo "<td>" . $row['id'] . "</td>";
            echo "<td>" . $row['username'] . "</td>";
            echo "<td>" . $row['password'] . "</td>";
            echo '<td>
                    <form method="post" action="FUNCTION/admin.php">
                        <input type="hidden" name="user_id" value="' . $row['id'] . '">
                        <input type="text" name="new_username" placeholder="Edit Username" required>
                        <input type="password" name="new_password" placeholder="Edit Password"required>
                        <button type="submit" name="update">Edit</button>
                        <button type="submit" name="delete">Hapus</button>
                    </form>
                </td>';
            echo "</tr>";
        }
    }
        ?>
    </table>
</body>
</html>
