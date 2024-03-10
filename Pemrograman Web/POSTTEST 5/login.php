<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Halaman Login</title>
    <link rel="stylesheet" href="CSS/login.css">
</head>
<body>
    <div class="container">
        <h2>Login</h2>
        <form action="FUNCTION/proseslogin.php" method="post">
            <div class="input-group">
                <label for="username">Username:</label>
                <input type="text" name="username" id="username" required>
            </div>
            <div class="input-group">
                <label for="password">Password:</label>
                <input type="password" name="password" id="password" required>
            </div>
            <button type="submit" class="btn">Login</button>
        </form>
        <div class="daftar">
    <p>Apakah kamu ingin <a href="daftar.php">mendaftar?</a></p>
    </div>
    </div>
</body>
</html>