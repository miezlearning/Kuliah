import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: HomePage(),
    );
  }
}

class HomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Minecraft Store'),
        backgroundColor: Colors.green,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: ListView(
          children: [
            Container(
              height: 200,
              color: Colors.grey[300], // Placeholder untuk banner utama
              child: const Center(child: Text("Banner Toko Minecraft", style: TextStyle(fontSize: 18))),
            ),
            SizedBox(height: 20),
            const Text(
              "Kategori Produk:",
              style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 10),
            GridView(
              shrinkWrap: true,
              physics: NeverScrollableScrollPhysics(),
              gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: 2,
                crossAxisSpacing: 10,
                mainAxisSpacing: 10,
              ),
              children: [
                kategoriCard("Blocks", Colors.brown),
                kategoriCard("Tools", Colors.blueGrey),
                kategoriCard("Armor", Colors.yellow),
                kategoriCard("Potions", Colors.purple),
              ],
            ),
            SizedBox(height: 20),
            const Text(
              "Produk Unggulan:",
              style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 10),
            ListView(
              shrinkWrap: true,
              physics: const NeverScrollableScrollPhysics(),
              children: [
                productCard("Diamond Sword", "5000 Minecoins", Colors.blue[300]!),
                productCard("Ender Pearl", "2000 Minecoins", Colors.green[300]!),
                productCard("Netherite Armor", "10000 Minecoins", Colors.black),
              ],
            )
          ],
        ),
      ),
    );
  }

  // Widget untuk menampilkan kartu kategori
  Widget kategoriCard(String title, Color color) {
    return Container(
      padding: EdgeInsets.all(16),
      decoration: BoxDecoration(
        color: color,
        borderRadius: BorderRadius.circular(10),
      ),
      child: Center(
        child: Text(
          title,
          style: TextStyle(color: Colors.white, fontSize: 16, fontWeight: FontWeight.bold),
        ),
      ),
    );
  }

  // Widget untuk menampilkan kartu produk
  Widget productCard(String productName, String price, Color color) {
    return Card(
      margin: EdgeInsets.only(bottom: 10),
      child: ListTile(
        leading: Container(
          width: 50,
          height: 50,
          color: color, // Placeholder warna untuk gambar produk
        ),
        title: Text(productName),
        subtitle: Text(price),
      ),
    );
  }
}
