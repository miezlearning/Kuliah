import 'dart:io';

class User {
  final String username;
  final String password;
  final bool isSeller;

  User(this.username, this.password, this.isSeller);
}

class MinecraftItem {
  final String name;
  double price;

  MinecraftItem(this.name, this.price);
}

class MinecraftSkin {
  final String name;
  double price;

  MinecraftSkin(this.name, this.price);
}

class MinecraftShop {
  List<MinecraftItem> items = [];
  List<MinecraftSkin> skins = [];
  List<User> users = [];

  MinecraftShop() {
    users.add(User("alip", "123", true));
    users.add(User("aslab", "123", false));
  }

  void addItem(String name, double price) {
    items.add(MinecraftItem(name, price));
  }

  void addSkin(String name, double price) {
    skins.add(MinecraftSkin(name, price));
  }

  void displayItems() {
    print("\nDaftar Item Minecraft:");
    for (var i = 0; i < items.length; i++) {
      print("${i + 1}. ${items[i].name} - \$${items[i].price}");
    }
  }

  void displaySkins() {
    print("\nDaftar Skin Minecraft:");
    for (var i = 0; i < skins.length; i++) {
      print("${i + 1}. ${skins[i].name} - \$${skins[i].price}");
    }
  }

  void buyItem(int index) {
    if (index >= 0 && index < items.length) {
      print("Anda telah membeli ${items[index].name} seharga \$${items[index].price}");
    } else {
      print("Item tidak ditemukan.");
    }
  }

  void buySkin(int index) {
    if (index >= 0 && index < skins.length) {
      print("Anda telah membeli skin ${skins[index].name} seharga \$${skins[index].price}");
    } else {
      print("Skin tidak ditemukan.");
    }
  }

  void updateItemPrice(int index, double newPrice) {
    if (index >= 0 && index < items.length) {
      items[index].price = newPrice;
      print("Harga ${items[index].name} telah diupdate menjadi \$${newPrice}");
    } else {
      print("Item tidak ditemukan.");
    }
  }

  void updateSkinPrice(int index, double newPrice) {
    if (index >= 0 && index < skins.length) {
      skins[index].price = newPrice;
      print("Harga skin ${skins[index].name} telah diupdate menjadi \$${newPrice}");
    } else {
      print("Skin tidak ditemukan.");
    }
  }

  User? login(String username, String password) {
    return users.firstWhere(
      (user) => user.username == username && user.password == password,
      orElse: () => null as User,
    );
  }
}

void main() {
  var shop = MinecraftShop();

  shop.addItem("Diamond Sword", 50.0);
  shop.addItem("Enchanted Bow", 75.0);
  shop.addSkin("Skin Wakwaw", 15.0);
  shop.addSkin("Cape Optifine", 20.0);

// Implementasi null safety
// Deklarasi Variabel
  User? currentUser;

  while (true) {
    if (currentUser == null) {
      print("\nSelamat datang di Toko Minecraft!");
      print("1. Login");
      print("2. Keluar");
      
      stdout.write("Pilih menu (1-2): ");
      String? choice = stdin.readLineSync();

      switch (choice) {
        case "1":
          stdout.write("Username: ");
          String? username = stdin.readLineSync();
          stdout.write("Password: ");
          String? password = stdin.readLineSync();
          currentUser = shop.login(username ?? "", password ?? "");
          if (currentUser != null) {
            // Ternary operator
            print("Login berhasil sebagai ${currentUser.isSeller ? 'Penjual' : 'Pembeli'}!");
          } else {
            print("Login gagal. Username atau password salah.");
          }
          break;
        case "2":
          print("Terima kasih telah mengunjungi Toko Minecraft!");
          return;
        default:
          print("Pilihan tidak valid. Silakan coba lagi.");
      }
    } else if (currentUser.isSeller) {
      print("\nMenu Penjual:");
      print("1. Lihat Item");
      print("2. Lihat Skin");
      print("3. Update Harga Item");
      print("4. Update Harga Skin");
      print("5. Tambah Item Baru");
      print("6. Tambah Skin Baru");
      print("7. Logout");
      
      stdout.write("Pilih menu (1-7): ");
      String? choice = stdin.readLineSync();

      switch (choice) {
        case "1":
          shop.displayItems();
          break;
        case "2":
          shop.displaySkins();
          break;
        case "3":
          shop.displayItems();
          stdout.write("Pilih nomor item yang ingin diupdate: ");
          int? itemIndex = int.tryParse(stdin.readLineSync() ?? "");
          stdout.write("Masukkan harga baru: ");
          double? newPrice = double.tryParse(stdin.readLineSync() ?? "");
          if (itemIndex != null && newPrice != null) {
            shop.updateItemPrice(itemIndex - 1, newPrice);
          } else {
            print("Input tidak valid.");
          }
          break;
        case "4":
          shop.displaySkins();
          stdout.write("Pilih nomor skin yang ingin diupdate: ");
          int? skinIndex = int.tryParse(stdin.readLineSync() ?? "");
          stdout.write("Masukkan harga baru: ");
          double? newPrice = double.tryParse(stdin.readLineSync() ?? "");
          if (skinIndex != null && newPrice != null) {
            shop.updateSkinPrice(skinIndex - 1, newPrice);
          } else {
            print("Input tidak valid.");
          }
          break;
        case "5":
          stdout.write("Nama item baru: ");
          String? newItemName = stdin.readLineSync();
          stdout.write("Harga item baru: ");
          double? newItemPrice = double.tryParse(stdin.readLineSync() ?? "");
          if (newItemName != null && newItemPrice != null) {
            shop.addItem(newItemName, newItemPrice);
            print("Item baru telah ditambahkan.");
          } else {
            print("Input tidak valid.");
          }
          break;
        case "6":
          stdout.write("Nama skin baru: ");
          String? newSkinName = stdin.readLineSync();
          stdout.write("Harga skin baru: ");
          double? newSkinPrice = double.tryParse(stdin.readLineSync() ?? "");
          if (newSkinName != null && newSkinPrice != null) {
            shop.addSkin(newSkinName, newSkinPrice);
            print("Skin baru telah ditambahkan.");
          } else {
            print("Input tidak valid.");
          }
          break;
        case "7":
          currentUser = null;
          print("Logout berhasil.");
          break;
        default:
          print("Pilihan tidak valid. Silakan coba lagi.");
      }
    } else {
      print("\nMenu Pembeli:");
      print("1. Lihat Item");
      print("2. Lihat Skin");
      print("3. Beli Item");
      print("4. Beli Skin");
      print("5. Logout");
      
      stdout.write("Pilih menu (1-5): ");
      String? choice = stdin.readLineSync();

      switch (choice) {
        case "1":
          shop.displayItems();
          break;
        case "2":
          shop.displaySkins();
          break;
        case "3":
          shop.displayItems();
          stdout.write("Pilih nomor item yang ingin dibeli: ");
          int? itemIndex = int.tryParse(stdin.readLineSync() ?? "");
          itemIndex != null 
              ? shop.buyItem(itemIndex - 1) 
              : print("Input tidak valid.");
          break;
        case "4":
          shop.displaySkins();
          stdout.write("Pilih nomor skin yang ingin dibeli: ");
          int? skinIndex = int.tryParse(stdin.readLineSync() ?? "");
          skinIndex != null 
              ? shop.buySkin(skinIndex - 1) 
              : print("Input tidak valid.");
          break;
        case "5":
          currentUser = null;
          print("Logout berhasil.");
          break;
        default:
          print("Pilihan tidak valid. Silakan coba lagi.");
      }
    }
  }
}