// Fungsi untuk menampilkan modal
function showModal(message) {
  const modal = document.getElementById('myModal');
  const modalOutput = document.getElementById('modalOutput');

  modalOutput.innerHTML = message;
  modal.style.display = 'block';

  const closeBtn = document.getElementsByClassName('close')[0];
  closeBtn.onclick = function () {
    modal.style.display = 'none';
  }

  window.onclick = function (event) {
    if (event.target == modal) {
      modal.style.display = 'none';
    }
  }
}

// Menangani pengiriman formulir
document.getElementById('kontak').addEventListener('submit', function (e) {
  e.preventDefault();
  const formData = new FormData(this);

  // Menampilkan modal konfirmasi
  const name = formData.get('name');
  const email = formData.get('email');
  const message = formData.get('message');
  const confirmationMessage = `\nNama: ${name}\nEmail: ${email}\n\nPesan: ${message}\n\n\nApakah Anda yakin ingin mengirim pesan ini?`;

  const confirmationModal = document.getElementById('confirmationModal');
  const confirmationMessageElement = document.getElementById('confirmationMessage');

  confirmationMessageElement.textContent = confirmationMessage;
  confirmationModal.style.display = 'block';

  // Menangani konfirmasi pengiriman formulir
  document.getElementById('confirmSubmit').addEventListener('click', function () {
    confirmationModal.style.display = 'none';

    // Kirim formulir jika dikonfirmasi
    fetch('FUNCTION/kirim.php', {
      method: 'POST',
      body: formData
    })
      .then(response => response.text())
      .then(data => {
        showModal(data);
      })
      .catch(error => {
        console.error('Error:', error);
      });
  });

  // Menangani pembatalan pengiriman formulir
  document.getElementById('cancelSubmit').addEventListener('click', function () {
    confirmationModal.style.display = 'none';
  });
});