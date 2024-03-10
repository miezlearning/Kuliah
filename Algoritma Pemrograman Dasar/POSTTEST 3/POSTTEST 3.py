# INPUT BIODATA
import os
clear = lambda: os.system('cls')


print('''
Selamat Datang Di Program Input Biodata Mahasiswa 
    UNIVERSITAS MULAWARMAN | PRODI INFORMATIKA

Isi Biodata kamu segera ya!
==================================================
''')
# Nama
nama = str(input("Nama : "))
# Umur
while True:
  try:
    umur = int(input("Masukkan Umur: ")) 
    if umur >= 17 and umur <= 100:
      break
    else:
      print("Umur minimal 17 keatas")      
  except ValueError:
    print("Mohon maaf masukkan data")
    continue

# Kelamin
while True:
  try:
    kelamin = str(input("Masukkan Kelamin: ")) 
    if kelamin == "Laki-Laki" or kelamin == "laki-laki" :
        break
    elif kelamin == "Perempuan" or kelamin == "perempuan":
        break
    else:
      print("[ERROR] INVALID\nDaftar Kelamin :\n Laki-Laki & Perempuan")      
  except ValueError:
    print("Mohon Maaf data kamu Invalid")
    continue

# NIM
while True:
    nim = int(input("NIM : "))
    nim_bool = int(input("Masukkan 3 Digit Terakhir NIM : "))

    Nim = nim_bool % 2
    Nim1 = bool(Nim)
    try:
        bool(nim)
        break
    except ValueError:
            print("Ini bukan Boolean. Tolong input data yang valid.")
# Prodi
prodi = str(input("Prodi : "))
# Alamat
alamat = input("Alamat : ")
# Golongan Darah
goldar = ''

while True:
    goldar = input('Golongan Darah : ')

    if len(goldar) <= 2 and goldar.isalpha():

        if(goldar == "O" or goldar == "o"):
            break
        elif(goldar == "A" or goldar == "a"):
            break
        elif(goldar == "B" or goldar == "b"):
            break
        elif(goldar == "AB" or goldar == "ab"):
            break
        else:
            print("Mohon maaf Golongan darah Invalid.")
            print('''
            Berikut Daftar Golongan :
            Golongan Darah : A, B, O, AB
            ''')

    else:
        print('Mohon maaf hanya bisa input 2 karakter.')
        continue
# Berat Badan
bb = float(input("Berat Badan (kg): "))
# Tinggi Badan
tb = float(input("Tinggi Badan (cm): "))
# BMI dari Berat Badan dan Tinggi Badan
bmi = bb / (tb/100) ** 2




clear()

print(f'''
╔══════════════════════════╗
║ Biodata Dari  {nama}        
╠══════════════════════════╣
║ Nama : {nama}            
╠══════════════════════════╣
║ Umur : {umur}            
╠══════════════════════════╣
║ Kelamin : {kelamin}      
╠══════════════════════════╣
║ NIM : {nim}
║ NIM Modulus : {Nim}
║ NIM Boolean : {Nim1}             
╠══════════════════════════╣
║ Prodi : {prodi}          
╠══════════════════════════╣
║ Alamat : {alamat}        
╠══════════════════════════╣
║ Golongan Darah : {goldar}
╠══════════════════════════╣
║ Berat Badan : {bb}       
╠══════════════════════════╣
║ Tinggi Badan : {tb}      
╠══════════════════════════╣
║ Indeks TB & BG :{bmi}''')

if bmi <= 18.5:  
    print('''
║ Oops! berat badan kurang!.             
╚══════════════════════════╝
''')  
elif bmi <= 24.9:  
    print('''║ Mantap! Kamu memiliki tubuh yang sehat!.             
╚══════════════════════════╝
''')  
elif bmi <= 29.9:  
    print('''║ Sheesh! Kamu kelebihan berat badan!.             
╚══════════════════════════╝
    ''')  
else:
    print('''║ WKWK OBESITAS.             
╚══════════════════════════╝
    ''')
