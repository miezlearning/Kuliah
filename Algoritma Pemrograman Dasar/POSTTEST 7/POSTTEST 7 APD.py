# 1. User daftar
# 2. User login
# 3. Jika user login mahasiswa biasa, maka hanya bisa memiliki fitur
# a. Menambahkan data (nama, kelas)
# 4. Jika user login admin, maka bisa memiliki fitur
# a. menambah data, mengubah data, menghapus data, melihat data

import os
from time import sleep
from pwinput import pwinput as passw

clean = lambda: os.system("cls")

login = {
    'username' : [],
    'password' :  [],
    'role': []
        
}

praktikan = {
"praktikan_nama" : ["Muhammad Alif", "Muhammad Khairuddin", "Roihan Ningrat Saputra", "Kurang Kenal"],
"praktikan_nim" : ["2209106127", "2209106128", "2209106129", "2209106130"]
}
def line():
    print(50*"-")

def viewData(): 
    print("""
-------------------------------------------------------------------------------------------------
| Nomor |                 Nama Lengkap                   |                  NIM               |      
-------------------------------------------------------------------------------------------------
""")                
    for items in range(len(praktikan["praktikan_nama"])):
        kolom_1 = str(items+1)
        kolom_2 = str(praktikan["praktikan_nama"][items])
        kolom_3 = str(praktikan["praktikan_nim"][items])
        print("|   " + kolom_1 + (4-len(kolom_1))*" "
            + "|  " + kolom_2 + (46-len(kolom_2))*" "
            + "|  " + kolom_3 + (36-len(kolom_3))*" "+"|")

def tambahBarang():
    clean()
    viewData()
    a = False
    while (a == False):
        nama_tambah = str(input("Masukkan Nama Lengkap : "))
        nim_tambah = str(input("Masukkan NIM : "))
        if(nama_tambah and nim_tambah.isnumeric()):
            #Masukan Data Nama Praktikan kedalam List
            praktikan["praktikan_nama"].append(nama_tambah)
            #Masukan Data NIM Praktikan kedalam List
            praktikan["praktikan_nim"].append(nim_tambah)
        sleep(0.5)
        break

def editBarang():
    clean()
    viewData()
    update = str(input("Masukkan Pilihan : "))
    if(update.isnumeric()):
        update_index = int(update) - 1
    
        namaA = str(input("Masukkan Nama Lengkap : "))
        nimA = str(input("Masukkan NIM : "))
        line()
        if(namaA.isalnum() and nimA.isnumeric()):
            #untuk hapus item pada list berdasarkan index
            praktikan["praktikan_nama"].pop(update_index)
            praktikan["praktikan_nim"].pop(update_index)
            
                #untuk memasukkan item pada list berdasarkan index yang diinginkan
            praktikan["praktikan_nama"].insert(update_index, namaA)
            praktikan["praktikan_nim"].insert(update_index, nimA)
        sleep(0.5)

def hapusBarang():
    clean()
    viewData()
    try :
        while True:
            delete = str(input("Masukkan Pilihan : "))
            if(delete.isnumeric()):
                delete_index = int(delete) - 1

                praktikan["praktikan_nama"].pop(delete_index)
                praktikan["praktikan_nim"].pop(delete_index)
            sleep(0.5)
            break
    except ValueError:
        print("Input yang benar!")

def lihatBarang():
    viewData()

# MENU PRAKTIKAN
def menu_pengguna():
    # a = ''.join(login.get('nama'))
    clean()
    while True:
        try:
            line()
            print("Selamat Datang Mahasiswa")
            print("1. Tambah Data Praktikan")
            print("2. Lihat Data Praktikan")
            print("3. Logout")
            line()

            mah_pilih = int(input("Pilih Menu >> "))

            if mah_pilih == 1 :
                tambahBarang()
            elif mah_pilih == 2 :
                lihatBarang()
            elif mah_pilih == 3 :
                masuk()
        except ValueError:
            print("Salah Input.")
    



# MENU ADMIN
def menu_admin():
    # a = ''.join(login.get('nama'))
    clean()
    while True:
        try:
            line()
            print("Selamat Datang Admin")
            print("1. Tambah Data Praktikan")
            print("2. Edit Data Praktikan")
            print("3. Hapus Data Praktikan")
            print("4. Lihat Data Praktikan")
            print("5. Logout")
            line()

            admin_pil = int(input("Pilih Menu >> "))

            if admin_pil == 1 :
                tambahBarang()
            elif admin_pil == 2 :
                editBarang()
            elif admin_pil == 3 :
                hapusBarang()
            elif admin_pil == 4 :
                lihatBarang()
            elif admin_pil == 5 :
                masuk()
        except ValueError:
            print("Salah Input.")



# Login/Masuk Pengguna
def masuk():
    hmm = input("Anda ingin login? [y]/[n] ")
    if (hmm == "y" or hmm == "Y"):
        p = 0
        while p < 3:
            try:
                print(login)
                print("==========================================")
                print(" \033[1m[ Login User ]\033[0m ")
                # cek = ''.join(login.get('role'))
                user = str(input("Masukkan Username : "))
                pw = str(passw(mask='\u2022',prompt="Masukkan Password : "))
                if (login["username"].index(user) == login["password"].index(pw)):
                    index = login["username"].index(user)
                    if(login["role"][index] == "Admin"):
                        menu_admin()
                    elif(login["role"][index] == "Mahasiswa"):
                        menu_pengguna()
                else:
                    print("Tidak jelass.")
                p+=1
            except ValueError:
                print("Mohon input data yang Valid.")
    elif (hmm == "n" or hmm == "N"):
        register()


# Register/Daftar Pengguna  
def register():
    while True:
        try:
            print("==========================================")
            print(" \033[1m[ Register User ]\033[0m ")
            login['username'].append(str(input("Masukkan Username : ")))
            login["password"].append(str(passw(mask='\u2022',prompt="Masukkan Password : ")))
            try:
                while True:
                    print("Hak Akses : ")
                    print("\u2022 Mahasiswa")
                    print("\u2022 Admin")
                    role = str(input("Piiih Hak Akses : ")).title()
                    if role == "Mahasiswa":
                        login["role"].append(role)
                        break
                    elif role == "Admin":
                        login["role"].append(role)
                        break
                    else:
                        print("Perhatikan Input.") 
                        input("ENTER untuk melanjutkan...")
                        clean()
                        print('Input anda sebelumnya : ', role)       
                    print(login["role"])
            except ValueError:
                print("\033[91mMasukkan data yang valid.\033[0m")
            break
        except ValueError:
            print("\033[91mMohon untuk memasukkan data yang Valid.\033[0m")   
            break    
    masuk()                

            


            

if __name__ == '__main__':
    register()