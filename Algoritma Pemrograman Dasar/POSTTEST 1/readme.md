## Algoritma Deskriptif

### Sistematis

1. **Langkah 1: Meminta Input Waktu**
   - Tampilkan pesan "Masukkan waktu dalam format HH:MM (24-jam):"
   - Terima input waktu dari pengguna

2. **Langkah 2: Menentukan Waktu**
   - Jika waktu berada di antara 00.00-05.00, maka tampilkan "Subuh"
   - Jika waktu berada di antara 05.01-09.00, maka tampilkan "Pagi"
   - Jika waktu berada di antara 09.01-14.59, maka tampilkan "Siang"
   - Jika waktu berada di antara 15.00-18.00, maka tampilkan "Sore"
   - Jika waktu berada di antara 18.01-23.59, maka tampilkan "Malam"

3. **Langkah 3: Menyimpan Output**
   - Tampilkan hasil ke pengguna

### Pseudocode

```plaintext
Procedure MenentukanWaktu()
    Tampilkan "Masukkan waktu dalam format HH:MM (24-jam):"
    Input waktu
    
    If waktu >= 00.00 and waktu <= 05.00 then
        Tampilkan "Subuh"
    Else If waktu >= 05.01 and waktu <= 09.00 then
        Tampilkan "Pagi"
    Else If waktu >= 09.01 and waktu <= 14.59 then
        Tampilkan "Siang"
    Else If waktu >= 15.00 and waktu <= 18.00 then
        Tampilkan "Sore"
    Else If waktu >= 18.01 and waktu <= 23.59 then
        Tampilkan "Malam"
    End If
End Procedure
