<?php
session_start();
include 'FUNCTION/koneksi.php';
include('cart_functions.php');

// Proses login dan verifikasi pengguna

if (!isset($_SESSION['username'])) {
    header('Location: login.php');
    exit();
}

if (!isset($_SESSION['id_user'])) {
    header('Location: login.php');
    exit();
}

$user_id = isset($_SESSION['id_user']) ? $_SESSION['id_user'] : null;


if (isset($_POST['product_id']) && isset($_POST['quantity'])) {
  $product_id = $_POST['product_id'];
  $quantity = $_POST['quantity'];
  addToCart($user_id, $product_id, $quantity);
  $_SESSION['cart'] = getCart($user_id);
}

// Initialize $cart variable
$cart = isset($_SESSION['cart']) ? $_SESSION['cart'] : [];



saveCartToDatabase($user_id, $cart);


// Rest of your code...
?>


<style>
/* Sembunyikan ikon hamburger pada tampilan desktop */
#hamburger-menu {
  display: none;
  cursor: pointer;
  font-size: 20px;
  margin-right: 25px;
}

/* Media query untuk layar kurang dari 768px (tablet dan di bawah) */
@media only screen and (max-width: 768px) {
  /* Sesuaikan margin untuk kontainer about */
  .about-container {
    margin: 20px auto;
  }

  /* Gaya untuk menu mobile */
  .menu.show {
    display: flex;
    flex-direction: column;
    position: absolute;
    top: 60px;
    left: 0;
    right: 0;
    background-color: #fff;
    z-index: 1;
  }

  /* Tampilkan ikon hamburger pada tampilan mobile */
  #hamburger-menu {
    display: block;
    cursor: pointer;
    font-size: 20px;
  }

  /* Gaya untuk navbar utama */
  .navbar {
    justify-content: center;
    align-items: center;
    padding: 30px;
    background-color: #fff;
    color: #fff;
    position: relative;
    display: flex;
    align-items: center;
  }

  /* Gaya untuk item menu */
  .menu {
    list-style: none;
    display: none; /* Menu semula disembunyikan */
    align-items: center;
    position: absolute;
    top: 60px;
    left: 0;
    right: 0;
    background-color: #fff;
    z-index: 1;
  }

  .menu li {
    margin: 0;
    text-align: center;
    padding: 10px;
  }

  .menu a {
    text-decoration: none;
    color: #fff;
    font-size: 16px;
  }

  /* Gaya untuk ikon keranjang belanja */
  .menu li.icon-cart {
    display: flex;
    align-items: center;
    margin-left: auto;
  }

  .menu li.icon-cart svg {
    lebar: 24px;
    tinggi: 24px;
    margin-kanan: 5px;
  }

  .menu li.icon-cart span {
    background-color: #fff;
    color: #333;
    padding: 2px 6px;
    border-radius: 50%;
    font-size: 12px;
  }

  /* Gaya tambahan ketika menu ditampilkan */
  .menu.show {
    display: flex;
    flex-direction: column;
    position: absolute;
    top: 60px;
    left: 0;
    right: 0;
    background-color: #FF4500;
    z-index: 1;
  }
}

/* Gaya untuk ikon keranjang belanja */
.icon-cart {
  display: flex;
  align-items: center;
  cursor: pointer;
  margin-left: auto;
}

.icon-cart svg {
  lebar: 24px;
  tinggi: 24px;
  margin-kanan: 5px;
}

.icon-cart span {
  background-color: #fff;
  color: #333;
  padding: 2px 6px;
  border-radius: 50%;
  font-size: 12px;
}

/*men Sesuaikan posisi ikon keranjang belanja */
.menu li.icon-cart {
  margin-left: auto;
  margin-kanan: 20px;
}



/* Media query untuk layar antara 768px dan 1024px (tablet landscape) */
@media only screen and (min-width: 769px) and (max-width: 1024px) {
  /* Tambahkan gaya untuk tablet landscape */
}

/* Media query untuk layar lebih besar dari 1024px (desktop) */
@media only screen and (min-width: 1025px) {
  /* Tambahkan gaya untuk desktop */
}


</style>







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
<?php include 'header.php' ?>
<script src="JS/jquery.js"></script>
<script>
  document.addEventListener("DOMContentLoaded", function () {
    const hamburgerMenu = document.getElementById("hamburger-menu");
    const menu = document.querySelector(".menu");
    const closeBtn = document.querySelector(".closebtn"); // Tambahkan ini
    const cartIcon = document.querySelector(".icon-cart"); // Tambahkan ini

    hamburgerMenu.addEventListener("click", function () {
      menu.classList.toggle("show");
    });

    if (closeBtn) {
      closeBtn.addEventListener("click", function () {
        menu.classList.remove("show");
      });
    }

    if (cartIcon) {
      cartIcon.addEventListener("click", function () {
        menu.classList.remove("show");
      });
    }

    // Tambahkan event listener pada setiap item keranjang untuk menutup tampilan keranjang
    const cartItems = document.querySelectorAll('.listCart .item');
    cartItems.forEach(function(item) {
      item.addEventListener('click', function() {
        menu.classList.remove('show');
      });
    });
  });
</script>
<body class="">
 
  <!-- Add this HTML code where you want the "about" section -->
  


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

  
  <div id="beranda" class="about-container">
  <div class="about-text">
    <h2>Tentang Kami</h2>
    <p>Selamat datang di Toko Skin Minecraft! Kami menyediakan berbagai macam skin Minecraft yang unik dan keren untuk mempercantik karakter Minecraft Anda.</p>
    <p>Dengan koleksi skin terbaru dan harga yang terjangkau, kami bertekad memberikan pengalaman berbelanja yang menyenangkan bagi para penggemar Minecraft.</p>
  </div>
    <div class="about-image">
      <img src="Gambar/about.jpg" alt="Tentang Kami">
    </div>
  </div>

  <div class="container">
  
  <div id="produks" class="landing-page">
      <h1 class="menkrep">Selamat Datang di Toko Skin Minecraft!</h1>
      <div class="produk">
          <div id="skin2" class="skin">
            <div class="card">
              <img src="Gambar/skin2.png" alt="Skin 2">
              <div class="card-content">
                <h2>Skin 2</h2>
                <div class="price">
                  <p>$15</p>
                </div>
                <button class="beli" name="product_id" data-product-id="2" data-product-name="Skin 2" data-product-price="15"
                  data-product-image="Gambar/skin2.png" onclick="addToCart(this)">Add to Cart</button>
              </div>
            </div>
          </div>
        </div>

        <?php
        include('FUNCTION/koneksi.php');
        $query = "SELECT * FROM skin ORDER BY id_skin ASC";
        $result = mysqli_query($conn, $query);
        if (!$result) {
          die("Query Error: " . mysqli_errno($conn) . " - " . mysqli_error($conn));
        }

        $count = 0;
        while ($row = mysqli_fetch_assoc($result)) {
          
          echo '<div class="skin">';
          echo '<div class="card">';
          echo '<img src="Gambar/' . $row['gambar'] . '" alt="' . $row['nama'] . '">';
          echo '<div class="card-content">';
          echo '<h2>' . $row['nama'] . '</h2>';
          echo '<div class="price">';
          echo '<p>$' . $row['harga'] . '</p>';
          echo '</div>';
          echo '<button class="beli" name="product_id" data-product-id="' . $row['id_skin'] . '" data-product-name="' . $row['nama'] . '" data-product-price="' . $row['harga'] . '" data-product-image="Gambar/' . $row['gambar'] . '">Add to Cart</button>';
          echo '</div>';
          echo '</div>';
          echo '</div>';

          $count++;
          if ($count % 2 == 0) {
            echo '<div class="clearfix"></div>'; // Add a clearfix after every 2 skins
          }
        }
        ?>
      
      </div>
    </div>
    
  </div> <!-- Tutup container di sini -->

  <div class="cartTab">
      <h1>Shopping Cart</h1>
      <div class="listCart">
        <?php
        $totalPrice = 0; // Inisialisasi total harga
        foreach ($cart as $item) {
          echo '<div class="item">';
          echo '<div class="image">';
          echo '<img src="' . $item['image'] . '" alt="' . $item['name'] . '">';
          echo '</div>';
          echo '<div class="name">' . $item['name'] . '</div>';
          echo '<div class="totalprice">Rp' . ($item['price'] * $item['quantity']) . '</div>';
          echo '<div class="quantity">';
          echo '<span class="minus" data-product-id="' . $item['id'] . '">-</span>';
          echo '<span>' . $item['quantity'] . '</span>';
          echo '<span class="plus" data-product-id="' . $item['id'] . '">+</span>';
          echo '</div>';
          echo '</div>';

          $totalPrice += $item['price'] * $item['quantity']; // Akumulasi total harga
        }
        ?>
      </div>
      <div class="total-price">Total: Rp
        <?php echo $totalPrice; ?>
      </div>
      <div class="btn">
        <button class="closebtn">CLOSE</button>
        <button class="checkout">CHECK OUT</button>
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

  <?php include 'footer.php' ?>

  <script src="JS/popup.js"></script>
  <script src="JS/modal.js"></script>
  <script src="JS/script.js"></script>
  <script src="JS/smooth.js"></script>




</body>

</html>