<?php
session_start();
if (!isset($_SESSION["role"]) || $_SESSION["role"] !== "user") {
  header("Location: login.php");
  exit();
}
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <script src="JS/jquery.js"></script>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Toko Skin Minecraft</title>
    <link rel="stylesheet" href="CSS/utama.css">
    <link rel="stylesheet" href="CSS/modal.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.0/css/all.min.css">
    <link rel="stylesheet" href="CSS/form.css"> 
  </head>
  <body>

  <div id="popup" class="popup">
        <div class="popup-content">
          <h2>Selamat datang di Toko Skin Minecraft!</h2>
          <p>Nikmati berbagai skin Minecraft keren dengan harga terbaik.</p>
          <button id="close-popup">Tutup</button>
        </div>
    </div>
    
      <div id="myModal" class="modal">
        <div class="modal-content">
          <span class="close">&times;</span>
          <div id="modalOutput"></div>
        </div>
      </div>


      <div id="confirmationModal" class="modal">
    <div class="modal-content">
      <div id="confirmationMessage">Apakah Anda yakin ingin mengirim pesan ini?</div>
      <button id="confirmSubmit" class="beli">Ya</button>
      <button id="cancelSubmit" class="beli">Batal</button>
    </div>
    </div>

    <?php include 'header.php' ?>
    
    <div class="container">
    



    <div id="produks" class="landing-page">
      <h1 class="menkrep">Selamat Datang di Toko Skin Minecraft!</h1>
      <div class="produk">
        <div id="skin1" class="skin">
          <div class="card">
            <img src="Gambar/skin1.png" alt="Skin 1">
            <div class="card-content">
              <h2>Skin 1</h2>
              <p>Harga: $10</p>
              <button class="beli">Beli</button>
            </div>
          </div>
        </div>
        
        <div id="skin2" class="skin">
          <div class="card">
            <img src="Gambar/skin2.png" alt="Skin 2">
            <div class="card-content">
              <h2>Skin 2</h2>
              <p>Harga: $15</p>
              <button class="beli">Beli</button>
            </div>
          </div>
        </div>
      </div>
      
      
      
      <div class="contact-form">
        <h2>Hubungi Kami</h2>
        <form id='kontak' method="POST">
          <label for="name">Nama:</label>
          <input type="text" id="name" name="name" required>
          
          <label for="email">Email:</label>
          <input type="email" id="email" name="email" required>
          
          <label for="message">Pesan:</label>
          <textarea id="message" name="message" rows="5" required></textarea>
          
          <button type="submit" class="beli" id="submitForm">Kirim</button>
        </form>
    </div>
    </div>
    
    <?php include 'footer.php' ?>
  </div> <!-- Tutup container di sini -->
  
  <script src="JS/popup.js"></script>
  <script src="JS/modal.js"></script>
  <script src="JS/script.js"></script>
</body>
</html>
