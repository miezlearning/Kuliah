# MODULE
import os
import sys
import time

bersihin = lambda: os.system("cls")

# DICTIONARY
login = {
    'user' : '',
    'password' : '',
    'nama':''
}

while True:
    try:
        print('''
                                Selamat Datang!
        Silahkan Register Terlebih Dahulu Jika Ingin Mengakses Program
        ''')
        a = str(input("Apakah kamu yakin ? [Y]/[N]"))
        if a == "Y" or a == "y":
            bersihin()
            break
        elif a == "N" or a == "n":
            sys.exit(0)
        else:
            print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")
            bersihin()
            continue
    except ValueError:
        print('\033[91mMohon untuk memasukkan tipe data String.\033[0m')
        continue
        

# LIST & TUPLE []
# DICTIONARY  {}

# REGISTER
while True:
    try:
        print("==========================================")
        print(" \033[1m[ Register User ]\033[0m ")
        login['user'] = str(input("Masukkan Username : "))
        login["password"] = str(input("Masukkan Password : "))
        login["nama"] = str(input("Masukkan Nama Anda : "))
        break
    except ValueError:
        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")   
        break

# LOGIN
hooh = 0
while hooh < 3:
    print("==========================================")
    print(" \033[1m[ Login User ]\033[0m ")
    user = input("Masukkan Username : ")
    pw = input("Masukkan Password : ")
    # VALIDASI LOGIN
    if (user == login["user"] and pw == login["password"]): 
        while True:
        
            try:
                bersihin()
                print(f"Selamat Datang {login['nama']}")
                print('''
                Pilih Program :
                1. Program Menghitung Luas
                2. Program Menghitung Volume
                3. Exit        
                ''')
                menu = int(input(">> "))

                if menu == 1:
                    while True:
                        try: 
                            bersihin()
                            print("Menu Program Menghitung Luas")
                            print('''
                                0. Keluar Program
                                1. Menghitung Luas Persegi
                                2. Menghitung Luas Persegi Panjang
                                3. Menghitung Luas Jajar Genjang
                                4. Menghitung Luas Segitiga
                                5. Menghitung Luas Layang-Layang
                                    ''')
                            menu1 = int(input(">> "))
                            if menu1 == 1:
                                while True:
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")
            
                            elif menu1 == 2:
                                while True:
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")   
                            elif menu1 == 3:
                                while True:
                                    try:
                            
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")        
                            elif menu1 == 4:
                                while True:
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")

                            elif menu1 == 5:
                                while True:
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")    

                            elif menu1 == 0:
                                break
                            else:
                                continue                
                        except ValueError:
                            print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")            
                elif menu == 2:
                    while True:
                        try:

                            bersihin()
                            print("Menu Program Menghitung Volume")
                            print('''
                                0. Keluar Program
                                1. Menghitung Volume Tabung
                                2. Menghitung Volume Kerucut
                                3. Menghitung Volume Balok
                                    ''')
                            menu2 = int(input(">> "))
                            if menu2 == 1:
                                while True:
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")
                                        continue
                                        
                            elif menu2 == 2:
                                while True:
            
                                    try:
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
                                            input("Tekan ENTER untuk melanjutkan")
                                            
                                        else:
                                            print(f"Volume Kerucut adalah : {v}")
                                            print(f'Volume Kerucut jika dibulatkan : {round(v)}')
                                            print("===============================")
                                            input("Tekan ENTER untuk melanjutkan")
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("Masukkan Data yang Valid.")
                            elif menu2 == 3:
                                while True:
                                    bersihin()
                                    try:
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
                                        time.sleep(5)
                                        break
                                    except ValueError:
                                        print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")
                            elif menu2 == 0:
                                break 
                            else:
                                break
                        except ValueError:
                                    print("\033[91mMasukkan Data yang Valid.\033[0m")
                elif menu == 3:
                    sys.exit(0)
            except ValueError:
                print("\033[91mMasukkan Data yang Valid.\033[0m")

    elif(user == login['user'] and pw != login['password']):
        print("\033[91mMohon maaf password anda salah\033[0m")
        hooh+=1
        
    elif(user != login['user'] and pw == login['password']):
        print("\033[91mMohon maaf username anda salah.\033[0m")
        hooh+=1
    else:   
        print("\033[91mMohon maaf Username dan Password anda salah.\033[0m")
        hooh+=1