

let iconcart = document.querySelector('.icon-cart');
let closecart = document.querySelector('.closebtn');
let body = document.querySelector('body');


iconcart.addEventListener('click', () => {
  body.classList.toggle('showcart')
})

closecart.addEventListener('click', () => {
  body.classList.toggle('showcart')
})

// ...

const cart = [];

// Tambahkan event listener untuk tombol "Add to Cart"
document.querySelectorAll('.beli').forEach((button) => {
  button.addEventListener('click', function () {
    const productId = this.getAttribute('data-product-id');
    const productName = this.getAttribute('data-product-name');
    const productPrice = parseFloat(this.getAttribute('data-product-price'));
    const productImage = this.getAttribute('data-product-image');


    // Anda dapat menggunakan productId, productName, dan productPrice sesuai kebutuhan Anda
    // Misalnya, tambahkan produk ke keranjang dengan detail ini
    const productDetails = {
      id: productId,
      image: productImage,
      name: productName,
      price: productPrice,
      quantity: 1
    };

    // Cek apakah produk sudah ada dalam keranjang
    const existingProduct = cart.find((item) => item.id === productId);

    if (existingProduct) {
      // Jika produk sudah ada dalam keranjang, tambahkan jumlahnya
      existingProduct.quantity += 1;
    } else {
      // Jika produk belum ada dalam keranjang, tambahkan produk ke keranjang
      cart.push(productDetails);
    }

    // Update tampilan keranjang (sesuaikan dengan desain Anda)
    updateCartDisplay();
  });
});

document.querySelector('.checkout').addEventListener('click', function () {
  // Show a confirmation dialog
  const isConfirmed = window.confirm('Are you sure you want to proceed with the checkout?');

  // If the user confirms, proceed with checkout
  if (isConfirmed) {
    // Clear the cart when the checkout button is clicked
    cart.length = 0;

    // Update the cart display
    updateCartDisplay();

    // Optionally, you can add additional logic for the checkout process
    // For example, send the cart data to the server for processing
    // ...

    // Show a success message (you can customize this part)
    alert('Order placed successfully!');

    // Close the cart after successful checkout
    body.classList.remove('showcart');
  }
  // If the user cancels, do nothing
});


function updateCartDisplay() {
  const cartContainer = document.querySelector('.listCart');
  const totalContainer = document.querySelector('.total-price'); // Tambahkan ini

  // Hapus tampilan keranjang yang sudah ada
  cartContainer.innerHTML = '';

  // Loop melalui produk dalam keranjang dan tambahkan ke tampilan
  cart.forEach((product) => {
    const cartItem = document.createElement('div');
    cartItem.classList.add('item');
    cartItem.innerHTML = `
      <div class="image">
        <img src="${product.image}" alt="${product.name}">
      </div>
      <div class="name">${product.name}</div>
      <div class="totalprice">$${product.price * product.quantity}</div>
      <div class="quantity">
        <span class="minus" data-product-id="${product.id}">-</span>
        <span>${product.quantity}</span>
        <span class="plus" data-product-id="${product.id}">+</span>
      </div>
    `;

    cartContainer.appendChild(cartItem);
  });

  // Tampilkan total harga
  totalContainer.textContent = 'Total: $' + calculateTotalPrice(); // Tambahkan ini

  // Update ikon keranjang dengan jumlah total item di keranjang
  const cartIcon = document.querySelector('.icon-cart');
  cartIcon.querySelector('span').textContent = cart.length;
}

// Tambahkan fungsi untuk menghitung total harga
function calculateTotalPrice() {
  let total = 0;
  cart.forEach((product) => {
    total += product.price * product.quantity;
  });
  return total;
}

// ...

// Tambahkan event delegation untuk tombol "minus" dan "plus"
document.addEventListener('click', (event) => {
  if (event.target.classList.contains('minus')) {
    const productId = event.target.getAttribute('data-product-id');
    decreaseQuantity(productId);
  }
  if (event.target.classList.contains('plus')) {
    const productId = event.target.getAttribute('data-product-id');
    increaseQuantity(productId);
  }
});

// ...

// Implementasikan fungsi untuk mengurangi jumlah produk
function decreaseQuantity(productId) {
  const productIndex = cart.findIndex((item) => item.id === productId);
  if (productIndex > -1) {
    const product = cart[productIndex];
    if (product.quantity > 1) {
      product.quantity -= 1;
    } else {
      // Jika jumlah produk menjadi 0, hapus produk dari keranjang
      cart.splice(productIndex, 1);
    }
    updateCartDisplay();
  }
}



// Implementasikan fungsi untuk menambah jumlah produk
function increaseQuantity(productId) {
  const product = cart.find((item) => item.id === productId);
  if (product) {
    product.quantity += 1;
    updateCartDisplay();
  }

  // Update tampilan keranjang (sesuaikan dengan desain Anda)
  updateCartDisplay();
}

$('#mode-toggle').click(function () {
  $('body').toggleClass('light-mode');
  $('body').toggleClass('dark-mode');
});
