# MODULE
import os 

bersihin = lambda: os.system("cls")

# LOGIN
user = input("Masukkan Username : ")
pw = input("Masukkan Password : ")

if (user == "alip"):
    if(pw == "alip123"):
        print(f"Selamat Datang Alip")
        print('''
        Pilih Program :
        1. Program Menghitung Luas
        2. Program Menghitung Volume
        3. Exit        
        ''')
        menu = int(input(">> "))

        if menu == 1:
            bersihin()
            print("Menu Program Menghitung Luas")
            print('''
                1. Menghitung Luas Persegi
                2. Menghitung Luas Persegi Panjang
                3. Menghitung Luas Jajar Genjang
                4. Menghitung Luas Segitiga
                5. Menghitung Luas Layang-Layang
                  ''')
            menu1 = int(input(">> "))
            if menu1 == 1:
                bersihin()
                print("Menghitung Luas Persegi")
                a = float(input("Masukkan cm Panjang Sisi Persegi : "))

                luas = a * a

                pembulatan = int(luas) + 0.5
                if(luas) > pembulatan:
                    hasil = int(luas) + 1
                    print(f"Luas Persegi adalah : {pembulatan}")
                    print(f"Luas Persegi setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Luas Persegi adalah : {luas}")
                    print(f'Luas Persegi jika dibulatkan : {round(luas)}')

            elif menu1 == 2:
                bersihin()
                print("Menghitung Luas Persegi Panjang")
                a = float(input("Masukkan cm Panjang Persegi Panjang : "))
                b = float(input("Masukkan cm Lebar Persegi Panjang : "))

                luas = a * b
                pembulatan = int(luas) + 0.5
                if(luas) > pembulatan:
                    hasil = int(luas) + 1
                    print(f"Luas Persegi Panjang adalah : {pembulatan}")
                    print(f"Luas Persegi Panjang setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Luas Persegi Panjang adalah : {luas}")
                    print(f'Luas Persegi Panjang jika dibulatkan : {round(luas)}')        
            elif menu1 == 3:
                bersihin()
                print("Menghitung Luas Jajar Genjang")
                a = float(input("Masukkan cm Alas Jajar Genjang : "))
                b = float(input("Masukkan cm Tinggi Jajar Genjang : "))

                luas = a * b
                pembulatan = int(luas) + 0.5
                if(luas) > pembulatan:
                    hasil = int(luas) + 1
                    print(f"Luas Jajar Genjang adalah : {pembulatan}")
                    print(f"Luas Jajar Genjang setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Luas Jajar Genjang adalah : {luas}")
                    print(f'Luas Jajar Genjang jika dibulatkan : {round(luas)}')        
            elif menu1 == 4:
                bersihin()
                print("Menghitung Luas Segitiga")
                a = float(input("Masukkan cm Alas Segitiga : "))
                b = float(input("Masukkan cm Tinggi Segitiga : "))

                luas = a * b / 2
                pembulatan = int(luas) + 0.5
                if(luas) > pembulatan:
                    hasil = int(luas) + 1
                    print(f"Luas Segitiga adalah : {pembulatan}")
                    print(f"Luas Segitiga setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Luas Segitiga adalah : {luas}")
                    print(f'Luas Segitiga jika dibulatkan : {round(luas)}')

            elif menu1 == 5:
                bersihin()
                print("Menghitung Luas Layang Layang")
                a = float(input("Masukkan cm Panjang Diagonal 1 Layang Layang : "))
                b = float(input("Masukkan cm Panjang Diagonal 2 Layang Layang : "))

                luas = a*b/2
                pembulatan = int(luas) + 0.5
                if(luas) > pembulatan:
                    hasil = int(luas) + 1
                    print(f"Luas Layang Layang adalah : {pembulatan}")
                    print(f"Luas Layang Layang setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Luas Layang Layang adalah : {luas}")
                    print(f'Luas Layang Layang jika dibulatkan : {round(luas)}')
                

        elif menu == 2:
            bersihin()
            print("Menu Program Menghitung Volume")
            print('''
                1. Menghitung Volume Tabung
                2. Menghitung Volume Kerucut
                3. Menghitung Volume Balok
                  ''')
            menu2 = int(input(">> "))
            if menu2 == 1:
                bersihin()
                print("Menghitung Volume Tabung")
                a = float(input("Masukkan Jari Jari Tabung : "))
                b = float(input("Masukkan Tinggi Tabung : "))

                phi = 3.14
                v = phi*a*a*b
                pembulatan = int(v) + 0.5
                if v > pembulatan:
                    hasil = int(v) + 1
                    print(f"Volume Tabung adalah : {pembulatan}")
                    print(f"Volume Tabung setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Volume Tabung adalah : {v}")
                    print(f'Volume Tabung jika dibulatkan : {round(v)}')

            elif menu2 == 2:
                bersihin()
                print("Menghitung Volume Kerucut")
                a = float(input("Masukkan Jari Jari Kerucut : "))
                b = float(input("Masukkan Tinggi Kerucut : "))

                phi = 3.14
                v = (phi*a*a*b)/3
                pembulatan = int(v) + 0.5
                if v > pembulatan:
                    hasil = int(v) + 1
                    print(f"Volume Kerucut adalah : {pembulatan}")
                    print(f"Volume Kerucut setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Volume Kerucut adalah : {v}")
                    print(f'Volume Kerucut jika dibulatkan : {round(v)}')

            elif menu2 == 3:
                bersihin()
                print("Menghitung Volume Balok")
                a = float(input("Masukkan Panjang Balok : "))
                b = float(input("Masukkan Lebar Balok : "))
                c = float(input("Masukkan Tinggi Balok : "))


                v = a * b * c
                pembulatan = int(v) + 0.5
                if v > pembulatan:
                    hasil = int(v) + 1
                    print(f"Volume Balok adalah : {pembulatan}")
                    print(f"Volume Balok setelah dibulatkan adalah : {hasil}")
                else:
                    print(f"Volume Balok adalah : {v}")
                    print(f'Volume Balok jika dibulatkan : {round(v)}')
            
    else:
        print("Salah Password")
        
else:
    print("Salah Username")