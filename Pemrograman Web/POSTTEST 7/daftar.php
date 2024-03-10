<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Halaman Pendaftaran</title>
    <link rel="stylesheet" href="CSS/daftar.css">
</head>
<body>
    <div class="container">
        <h2>Daftar</h2>
        <form action="FUNCTION/prosesdaftar.php" method="post">
            <div class="input-group">
                <label for="username">Username:</label>
                <input type="text" name="username" id="username" required>
            </div>
            <div class="input-group">
                <label for="password">Password:</label>
                <input type="password" name="password" id="password" required>
            </div>
            <div class="input-group">
                <label for="confirm_password">Konfirmasi Password:</label>
                <input type="password" name="confirm_password" id="confirm_password" required>
            </div>
            <!-- Juga tambahkan input untuk data pendaftaran lainnya jika diperlukan -->
            <button type="submit" class="btn">Daftar</button>
        </form>
        <div class="login">
            <p>Sudah punya akun? <a href="login.php">Login di sini</a></p>
        </div>
    </div>
</body>
</html>
