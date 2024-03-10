<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: login.php'); // Jika tidak ada sesi, kembali ke halaman login
    exit();
}

// Check for error parameter in the URL
if (isset($_GET['error'])) {
    $errorMessage = '';

    switch ($_GET['error']) {
        case 'duplicate_username':
            $errorMessage = 'Error: Duplicate username. Please choose a different username.';
            break;
        case 'insert_error':
            $errorMessage = 'Error: Unable to insert data. Please try again.';
            break;
        case 'upload_failed':
            $errorMessage = 'Error: Failed to upload the image. Please try again.';
            break;
        // Add more cases for other error types if needed
    }

    // Display JavaScript to show an alert with the error message
    echo "<script>
            window.onload = function() {
                alert('$errorMessage');
            };
          </script>";
}


?>

<!-- KEKURANGAN PROGRAM INI, TIDAK MENGGUNAKAN ROLE -->
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard</title>
    <link rel="stylesheet" href="CSS/halamanadmin.css">
    <style>
        th {
            color: black;
        }
    </style>
</head>

<body>
<div class="container">

    <h1>Admin Dashboard <a class="logout" href="FUNCTION/logout.php">Logout</a></h1>

    <!-- Tambah Pengguna Form -->
    
    <div class="box">
        <h2>Tambah Pengguna</h2>
        <form method="post" action="FUNCTION/admin.php" enctype="multipart/form-data">
            <label for="new_username">Username:</label>
            <input type="text" name="new_username" id="new_username" required>
            <label for="new_password">Password:</label>
            <input type="password" name="new_password" id="new_password" required>
            <label for="user_image">Gambar Pengguna:</label>
            <!-- Add this to your form -->
            <div class="file-input-container">
                <label for="fileInput" class="file-input-label">Choose File</label>
                <input type="file" id="fileInput" name="user_image" class="file-input-hidden" />
                <span class="file-name">File tidak ada </span>
            </div>
            <div id="image-container">
        <img height="250px" width="250px" id="uploaded-image" alt="Uploaded Image">
        <button id="remove-button" onclick="removeImage()">Remove</button>
    </div>
            <br>
            <button type="submit" name="submit">Tambah</button>
        </form>
    </div>
        
    <!-- Tampilkan Data Pengguna -->
    <h2>Data Pengguna</h2>
    <p>
        <?php
        $hari = array("Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu");
        $bulan = array("Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember");
        $currentDateTime = new DateTime("now", new DateTimeZone('Asia/Makassar'));
        $dayIndex = $currentDateTime->format('w');
        $formattedDate = $hari[$dayIndex] . ", " . $currentDateTime->format('d') . " " . $bulan[intval($currentDateTime->format('m')) - 1] . " " . $currentDateTime->format('Y');
        echo "Hari: " . $formattedDate . "<br>";
        echo "Zona Waktu: " . $currentDateTime->format('T') . "<br>";
        ?>
    </p>
    <table>
    <tr>
        <th>ID</th>
        <th>Username</th>
        <th>Password</th>
        <th>Gambar</th>
        <th>Action</th>
    </tr>
    <?php
    include 'FUNCTION/koneksi.php';
    $query = "SELECT * FROM user";
    $result = $conn->query($query);
    while ($row = $result->fetch_assoc()) {
        if ($row['username'] === 'admin' && $row['password'] === 'admin') {
            continue;
        } else {
            echo "<tr>";
            echo "<td>" . $row['id_user'] . "</td>";
            echo "<td>" . $row['username'] . "</td>";
            echo "<td>" . $row['password'] . "</td>";
            echo "<td><img src='Gambar/gambar_pengguna/" . $row['user_image'] . "' width='100' alt='Tidak ada Gambar' height='100'></td>";
            echo '<td>
                <form method="post" action="FUNCTION/admin.php" enctype="multipart/form-data">
                    <input type="hidden" name="user_id" value="' . $row['id_user'] . '">
                    <input type="text" name="new_username" placeholder="Edit Username" value="' . $row['username'] . '" required>
                    <input type="password" name="new_password" placeholder="Edit Password" value="' . $row['password'] . '" required>
                    
                    <!-- Unique IDs for each row -->
                    <div class="file-input-container" id="file-input-container-' . $row['id_user'] . '">
                        <label for="fileInput-' . $row['id_user'] . '" class="file-input-label">Choose File</label>
                        <input type="file" id="fileInput-' . $row['id_user'] . '" name="user_image" class="file-input-hidden" />
                        <input type="hidden" name="user_image_existing" value="' . $row['user_image'] . '">
                        <span class="file-name-' . $row['id_user'] . '">File tidak ada </span>
                    </div>
                    <div id="image-container-' . $row['id_user'] . '">
                        <img height="250px" width="250px" id="uploaded-image-' . $row['id_user'] . '" alt="Tidak ada Gambar">
                        <button id="remove-button-' . $row['id_user'] . '" onclick="removeImage1(' . $row['id_user'] . ', event)">Remove</button>
                    </div>
                    <br>
                    <button type="submit" name="update">Edit</button>
                    <button type="submit" name="delete">Hapus</button>
                </form>
            </td>';
            echo "</tr>";
        }
    }
    ?>
</table>
<section class="location-section">
    <h1 class="data">Data Anggota Kelompok</h1>

    <table>

      <thead>
        <tr>
          <th>No</th>
          <th>Nama Anggota</th>
          <th>Nim</th>
          <th>Kelas</th>
        </tr>
      </thead>

      <tbody>

        <tr>
          <td>1</td>
          <td>Muhammad Alif </td>
          <td>2209106127</td>
          <td>C 2022</td>
        </tr>
        <tr>
          <td>2</td>
          <td>Muhammad Khairrudin</td>
          <td>2209106128</td>
          <td>C 2022</td>
        </tr>
        <tr>
          <td>3</td>
          <td>Muhammad Yusuf Efendi</td>
          <td>2209106139</td>
          <td>C 2022</td>
        </tr>
        

      </tbody>

    </table>
  </section>


    <a href="skin.php">
        <!-- <a>Klik disini untuk menambahkan skin.</a> -->
        <h2>Tambah Skin</h2>
    </a>
</div>
</body>

    <script>
            document.getElementById('fileInput').addEventListener('change', function (e) {
                var fileName = e.target.files[0].name;
                document.querySelector('.file-name').textContent = fileName;

                // Display the uploaded image
                displayImage(e.target.files[0]);
            });


            function displayImage(file) {
                var reader = new FileReader();
                var uploadedImage = document.getElementById('uploaded-image');

                reader.onload = function (e) {
                    uploadedImage.src = e.target.result;
                    document.getElementById('image-container').style.display = 'block';
                };

                // Read the file as a data URL
                reader.readAsDataURL(file);
            }

            function removeImage() {
                document.getElementById('uploaded-image').src = '';
                document.getElementById('image-container').style.display = 'none';
                document.getElementById('fileInput').value = ''; // Reset the file input
                document.querySelector('.file-name').textContent = 'No file chosen';
            }

            <?php
    // Attach event listeners for file input change in each row
    $result = $conn->query($query);
    while ($row = $result->fetch_assoc()) {
        if ($row['username'] === 'admin' && $row['password'] === 'admin') {
            continue;
        } else {
            echo 'document.getElementById("fileInput-' . $row['id'] . '").addEventListener("change", function() { 
                    displayImage1(' . $row['id'] . '); 
                });';

            // Initialize display for the existing rows
            echo 'displayImage1(' . $row['id'] . ');';
        }
    }
    ?>

function displayImage1(rowId) {
        var fileInput = document.getElementById('fileInput-' + rowId);
        var fileName = document.querySelector('.file-name-' + rowId);
        var uploadedImage = document.getElementById('uploaded-image-' + rowId);
        var imageContainer = document.getElementById('image-container-' + rowId);
        var removeButton = document.getElementById('remove-button-' + rowId);

        // Check if a file is selected
        if (fileInput.files.length > 0) {
            var reader = new FileReader();
            reader.onload = function (e) {
                uploadedImage.src = e.target.result;
                imageContainer.style.display = 'block'; // Show the image container
                removeButton.style.display = 'block'; // Show the remove button
            };

            // Read the file as a data URL
            reader.readAsDataURL(fileInput.files[0]);

            // Update the file name display
            fileName.textContent = fileInput.files[0].name;
        } else {
            // Hide the image container and remove button when no file is selected
            imageContainer.style.display = 'none';
            removeButton.style.display = 'none';
            fileName.textContent = 'File tidak ada';
        }
    }

    function removeImage1(rowId, event) {
        // Prevent the form from being submitted
        event.preventDefault();

        var fileInput = document.getElementById('fileInput-' + rowId);
        var imageContainer = document.getElementById('image-container-' + rowId);
        var removeButton = document.getElementById('remove-button-' + rowId);
        var fileName = document.querySelector('.file-name-' + rowId); // Update the selector if needed

        fileInput.value = '';
        imageContainer.style.display = 'none';
        removeButton.style.display = 'none';
        fileName.textContent = 'Tidak ada file';
    }


            

        </script>


</html>