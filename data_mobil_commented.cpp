// Kelompok 5 : 123250050, 123250060, 123250082

// ============================================================
// LIBRARY / HEADER
// ============================================================
#include <iostream>   // cout, cin — input output standar
#include <iomanip>    // setw(), setfill() — format tampilan tabel
#include <stdio.h>    // fopen, fclose, fprintf — file I/O gaya C
#include <stdlib.h>   // system(), exit() — perintah sistem & keluar program
#include <conio.h>    // _getch() — khusus Windows (tidak dipakai secara eksplisit tapi di-include)
#include <fstream>    // ifstream, ofstream — file I/O gaya C++ (lebih modern)
#include <cstring>    // strcmp(), strncpy() — operasi string pada char array
#include <windows.h>  // FindFirstFileA, GetModuleFileNameA, SetCurrentDirectoryA — API Windows
using namespace std;

// ============================================================
// VARIABEL GLOBAL
// Bisa diakses langsung oleh semua fungsi tanpa perlu di-passing.
// ============================================================
FILE *ptr;                  // pointer file gaya C, dipakai di input_data()
char namefile[20];          // nama file versi char array (untuk fopen gaya C)
string filemerge, filecari;  // nama file versi string (untuk ifstream gaya C++)
                            // filecari = nama file yang dipakai di searching()
int jumlah_data, urut;      // jumlah_data = banyak record aktif di dataMobil[]
                            // urut = pilihan kolom sort: 1=STNK, 2=Jenis, 3=Warna
long cari_stnk;             // nomor STNK yang dicari user di fungsi searching

// ============================================================
// STRUCT: TIPE DATA CUSTOM
// struct mengelompokkan beberapa variabel menjadi satu "paket".
// Satu struct identitas_mobil = satu baris data mobil.
// ============================================================
struct identitas_mobil {
    long no_stnk;           // nomor STNK (angka panjang, misal: 123456789)
    char jenis_mobil[50];   // nama jenis mobil (char array, maks 49 karakter + '\0')
    char warna_mobil[50];   // warna mobil
} dataMobil[10];            // sekaligus deklarasi array 10 elemen bertipe identitas_mobil
                            // ini array global yang dipakai bersama oleh semua fungsi

// ============================================================
// FUNGSI: tampil_file()
// Menampilkan daftar semua file .txt dan .dat di folder aktif.
// Menggunakan Windows API untuk membaca isi direktori.
// ============================================================
void tampil_file(){
    int urutan = 1;
    WIN32_FIND_DATAA daftar;  // struct dari Windows API, menyimpan info file yang ditemukan
    
    cout << "Daftar file:\n";
    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');  // reset fill ke spasi supaya tidak mempengaruhi output berikutnya

    // -- Cari semua file *.txt --
    // FindFirstFileA: mulai pencarian file sesuai pola, return HANDLE
    // INVALID_HANDLE_VALUE artinya tidak ada file yang cocok
    HANDLE cari1 = FindFirstFileA("*.txt", &daftar);
    if(cari1 != INVALID_HANDLE_VALUE){
        do {
            cout << urutan << ". " << daftar.cFileName << endl;  // cFileName = nama file ditemukan
            urutan++;
        } while(FindNextFileA(cari1, &daftar));  // lanjut ke file .txt berikutnya
        FindClose(cari1);  // wajib tutup HANDLE setelah selesai (mencegah memory leak)
    } else {
        cout << "Tidak ada file (.txt)\n";
    }
    
    // -- Cari semua file *.dat (cara yang sama) --
    HANDLE cari2 = FindFirstFileA("*.dat", &daftar);
    if(cari2 != INVALID_HANDLE_VALUE){
        do {
            cout << urutan << ". " << daftar.cFileName << endl;
            urutan++;
        } while(FindNextFileA(cari2, &daftar));
        FindClose(cari2);
    } else {
        cout << "Tidak ada file (.dat)\n";
    }
    
    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');
}

// ============================================================
// FUNGSI: input_data()
// Menerima input data mobil dari user, lalu menyimpannya ke file
// dengan format: no_stnk|jenis_mobil|warna_mobil (satu baris per data).
// ============================================================
void input_data(){
	cout << "\nINPUT DATA" << endl;
    cout << "=============================" << endl;
    cout << "Jumlah data (maks 10) : ";
    cin >> jumlah_data;  // simpan jumlah data yang mau diinput
    
    // Validasi jumlah data
    if (jumlah_data > 10) {
        cout << "\nJumlah data lebih dari 10!\n";
        system("pause");
        return;  // keluar dari fungsi, tidak lanjut input
    } else if(jumlah_data <= 0){
		cout << "\nJumlah data terlalu sedikit.\n";
		system("pause");
	} 
    
    cout << "Disimpan di file bernama (tanpa spasi) : ";
    cin >> namefile;  // nama file disimpan ke char array global 'namefile'

    // fopen(namefile, "w"):
    //   "w" = write mode: buat file baru jika belum ada, timpa jika sudah ada
    //   return NULL jika gagal (misal: path tidak valid atau tidak ada izin)
    ptr = fopen(namefile,"w");
	if(ptr==NULL) {
		cout<<"\nError\n";  // gagal buka/buat file
    } else {
	  cout<<endl;
	  for(int i=0; i<jumlah_data; i++){
		cout<<"Data ke-"<<i+1<<endl;

        // cin >> hanya baca sampai spasi, cocok untuk angka
		cout << "No. STNK  : "; 
        cin >> dataMobil[i].no_stnk;

        // cin.ignore() buang karakter newline ('\n') yang tersisa di buffer
        // setelah cin >>, supaya cin.getline() di bawah tidak langsung terlewat
        cin.ignore();

        // cin.getline(array, ukuran): baca satu baris penuh termasuk spasi
		cout << "Jenis Mobil : "; 
        cin.getline(dataMobil[i].jenis_mobil, 50);
        cout << "Warna Mobil : ";
        cin.getline(dataMobil[i].warna_mobil, 50);

        // Tulis satu record ke file dengan format pipe-separated:
        // contoh hasil: "12345|Toyota Avanza|Putih\n"
        // %ld = format long int, %s = format string (char array)
		fprintf(ptr, "%ld|%s|%s\n",
				dataMobil[i].no_stnk,
				dataMobil[i].jenis_mobil,
				dataMobil[i].warna_mobil);
	  }
	  fclose(ptr);  // tutup file — data baru benar-benar tersimpan setelah ini
	}
}

// ============================================================
// FUNGSI: cetak_tabel()
// Menampilkan isi array dataMobil[] dalam bentuk tabel berformat rapi.
// Bergantung pada variabel global: dataMobil[] dan jumlah_data.
// ============================================================
void cetak_tabel(){
    // setfill('=') + setw(61): cetak '=' sebanyak 61 karakter (garis pemisah)
    cout << setfill('=') << setw(61) << "=" << endl;
    cout << setfill(' ');  // kembalikan fill ke spasi

    // left = rata kiri, setw(N) = lebar kolom N karakter
    cout << left
         << setw(6)  << "No."
         << setw(15) << "No. STNK"
         << setw(20) << "Jenis Mobil"
         << setw(20) << "Warna Mobil" << endl;
    cout << setfill('=') << setw(61) << "=" << endl;
    cout << setfill(' ');

    // Loop: cetak tiap elemen dataMobil[] sesuai jumlah_data
    for(int i = 0; i < jumlah_data; i++){
        cout << left
             << setw(6)  << i + 1                      // nomor urut
             << setw(15) << dataMobil[i].no_stnk        // kolom STNK
             << setw(20) << dataMobil[i].jenis_mobil    // kolom jenis
             << setw(20) << dataMobil[i].warna_mobil << endl;  // kolom warna
    }
}

// ============================================================
// FUNGSI: tampil_data(int)
// Membaca isi file yang dipilih user, parsing tiap baris,
// mengisi dataMobil[], lalu menampilkan hasilnya dengan cetak_tabel().
//
// Catatan: parameter 'int' diterima tapi tidak digunakan (sisa refactor).
// ============================================================
void tampil_data(int){
    string baris;  // untuk menyimpan satu baris yang dibaca dari file

    cout << "\tTAMPIL DATA\n";
    cout << "==================================\n";
    
    tampil_file();  // tampilkan daftar file yang tersedia
    
    cout << "Nama file yang akan ditampilkan : ";
    string namaFileTampil;
    cin >> namaFileTampil;  // ⚠️ BUG: variabel ini tidak dipakai di bawah
    cin.ignore();
    
    system("pause");
    system("cls");  // bersihkan layar sebelum tampilkan tabel
    
    // Buka file menggunakan ifstream (C++ style, lebih aman dari fopen)
    // ⚠️ BUG: yang dibuka adalah 'namefile' (global lama), bukan 'namaFileTampil' yang baru diinput
    ifstream file(namefile);
	if(!file.is_open()){
		cout << "\nFile tidak ditemukan atau gagal dibuka!\n";
		return;
	}

    // Reset jumlah_data sebelum baca ulang dari file
	jumlah_data = 0;
	
    // getline(file, baris): baca satu baris dari file, simpan ke 'baris'
    // Loop berhenti jika file habis atau sudah 10 data
	while(getline(file, baris) && jumlah_data < 10){
        // --- Parsing manual dengan delimiter '|' ---
        // Contoh baris: "12345|Toyota Avanza|Putih"
        
		int pisah1 = baris.find('|');              // cari posisi '|' pertama  → index 5
		int pisah2 = baris.find('|', pisah1 + 1); // cari '|' kedua mulai dari pisah1+1 → index 19

        // substr(pos, panjang): potong string dari posisi tertentu sepanjang N karakter
        // stol(): konversi string → long
		dataMobil[jumlah_data].no_stnk = stol(baris.substr(0, pisah1));

        // .c_str(): konversi std::string → const char* (diperlukan oleh strncpy)
        // strncpy(dest, src, n): salin maks n karakter dari src ke dest (lebih aman dari strcpy)
		strncpy(dataMobil[jumlah_data].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
		strncpy(dataMobil[jumlah_data].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
		jumlah_data++;
	}
	file.close();
	
    if(jumlah_data == 0){
        cout << "Tidak ada data dalam file.\n";
    }

    cout << "\nDATA MOBIL\n";
    cetak_tabel();  // tampilkan dataMobil[] yang sudah diisi dari file
}

// ============================================================
// FUNGSI: kondisi(a, b, urut)
// Komparator tunggal yang digunakan oleh SEMUA algoritma sort.
// Return true  → elemen 'a' lebih besar dari 'b' (perlu di-swap agar urut naik)
// Return false → 'a' sudah di posisi yang benar
//
// strcmp(x, y): return negatif jika x < y, 0 jika sama, positif jika x > y
// ============================================================
bool kondisi(identitas_mobil a, identitas_mobil b, int urut) {
    if(urut == 1) {
        return a.no_stnk > b.no_stnk;                      // bandingkan angka STNK
    } else if(urut == 2) {
        return strcmp(a.jenis_mobil, b.jenis_mobil) > 0;   // bandingkan string jenis (alfabet)
    } else {
        return strcmp(a.warna_mobil, b.warna_mobil) > 0;   // bandingkan string warna (alfabet)
    }
}

// ============================================================
// FUNGSI: bubble_sort()
// Prinsip: bandingkan dua elemen berdampingan, swap jika salah urut.
// Setiap iterasi luar (i), elemen terbesar "menggelembung" ke posisi akhir.
// Kompleksitas waktu: O(n²) — lambat untuk data besar.
// ============================================================
void bubble_sort(){
	for(int i = 0; i < jumlah_data - 1; i++){
        // -i-1 karena i elemen paling akhir sudah pada posisi benar setelah iterasi ke-i
		for(int j = 0; j < jumlah_data - i - 1; j++){
			if(kondisi(dataMobil[j], dataMobil[j+1], urut)){
                // jika elemen kiri lebih besar dari kanan → tukar posisi
				swap(dataMobil[j], dataMobil[j + 1]);
			}
		}
	}
}

// ============================================================
// FUNGSI: selection_sort()
// Prinsip: cari elemen terkecil dari sisa array yang belum terurut,
// lalu tempatkan di posisi i (depan).
// k menyimpan indeks elemen "terkecil" sementara.
// Kompleksitas waktu: O(n²).
// ============================================================
void selection_sort(){
	for(int i = 0; i < jumlah_data - 1; i++) {
		int k = i;  // asumsikan elemen ke-i adalah yang terkecil
		for(int j = i + 1; j < jumlah_data; j++) {
            // jika kondisi(dataMobil[k], dataMobil[j]) true → dataMobil[j] lebih kecil
			if (kondisi(dataMobil[k], dataMobil[j], urut)) {
				k = j;  // update indeks elemen terkecil
			}
		}
        // setelah loop dalam, k = indeks elemen terkecil → tukar ke posisi i
		swap(dataMobil[i], dataMobil[k]);
	}
}

// ============================================================
// FUNGSI: insertion_sort()
// Prinsip: ambil elemen ke-i, geser elemen-elemen yang lebih besar
// ke kanan satu posisi, lalu sisipkan elemen ke posisi yang tepat.
// Seperti menyortir kartu remi di tangan.
// Kompleksitas waktu: O(n²), tapi cepat untuk data yang hampir terurut.
// ============================================================
void insertion_sort(){
	for (int i = 1; i < jumlah_data; i++){
		identitas_mobil temp = dataMobil[i];  // simpan elemen yang akan disisipkan
		int j = i - 1;

        // geser semua elemen yang lebih besar dari temp ke kanan
		while (j >= 0 && kondisi(dataMobil[j], temp, urut)){
			dataMobil[j + 1] = dataMobil[j];  // geser satu posisi ke kanan
			j--;
		}
        // j+1 adalah posisi tepat untuk menyisipkan temp
		dataMobil[j + 1] = temp;
   	}
}

// ============================================================
// FUNGSI: shell_sort()
// Prinsip: varian insertion sort dengan "jarak" (gap) antar elemen.
// Mulai dengan jarak besar (n/2), lalu dikurangi setengah tiap iterasi.
// Elemen yang jauh bisa dipindahkan lebih cepat dibanding insertion sort biasa.
// Kompleksitas waktu: O(n log n) rata-rata — lebih cepat dari insertion sort.
// ============================================================
void shell_sort(){
    // jarak dimulai dari setengah jumlah_data, terus dibagi 2 sampai 0
	for (int jarak = jumlah_data / 2; jarak > 0; jarak = jarak / 2) {
		for (int i = jarak; i < jumlah_data; i++) {
            // bandingkan elemen yang berjarak 'jarak' satu sama lain
			for (int j = i - jarak; j >= 0; j = j - jarak) {
				if (kondisi(dataMobil[j], dataMobil[j + jarak], urut)) {
					swap(dataMobil[j], dataMobil[j + jarak]);
				}
			}
		}
	}
}

// ============================================================
// FUNGSI: bagi(awal, akhir, urut) — helper untuk quick_sort
// Memilih pivot (elemen terakhir = dataMobil[akhir]), lalu mempartisi
// array[awal..akhir] sehingga:
//   - elemen ≤ pivot ada di kiri
//   - elemen > pivot ada di kanan
// Return: indeks akhir pivot setelah partisi
// ============================================================
int bagi(int awal, int akhir, int urut){
	int ip = awal;  // ip = indeks partisi, menunjukkan batas kiri vs kanan
	string pivot = dataMobil[akhir].jenis_mobil;  // pivot = elemen terakhir
		
	for(int i = awal; i < akhir; i++){
        // jika dataMobil[i] ≤ pivot (kondisi false = tidak perlu swap dengan pivot)
        // maka pindahkan ke sisi kiri (posisi ip)
		if(!kondisi(dataMobil[i], dataMobil[akhir], urut)) {
				swap(dataMobil[i], dataMobil[ip]);
				ip++;  // geser batas partisi ke kanan
        }
    }
    // tempatkan pivot di posisi tengah yang tepat (ip)
    swap(dataMobil[akhir], dataMobil[ip]);
    return ip;  // kembalikan posisi pivot
}

// ============================================================
// FUNGSI: quick(awal, akhir, urut) — rekursi quick_sort
// Rekursi: partisi array, lalu panggil diri sendiri untuk
// sub-array kiri (awal..ip-1) dan kanan (ip+1..akhir).
// Kompleksitas waktu: O(n log n) rata-rata, O(n²) kasus terburuk.
// ============================================================
void quick(int awal, int akhir, int urut){
	if(awal < akhir){   // base case: berhenti jika hanya 1 elemen atau kosong
		int ip = bagi(awal, akhir, urut);  // partisi dan dapatkan posisi pivot
        quick(awal, ip-1, urut);           // rekursi sub-array kiri
        quick(ip+1, akhir, urut);          // rekursi sub-array kanan
	}
}

// Wrapper yang dipanggil dari menu sorting
void quick_sort(){
    quick(0, jumlah_data-1, urut);
}

// ============================================================
// FUNGSI: merge(kiri, tengah, kanan) — helper untuk merge_sort
// Menggabungkan dua sub-array yang sudah terurut:
//   - sub-array kiri : dataMobil[kiri..tengah]
//   - sub-array kanan: dataMobil[tengah+1..kanan]
// menjadi satu array terurut di dataMobil[kiri..kanan].
// ============================================================
void merge(int kiri, int tengah, int kanan){
	int a1 = tengah - kiri + 1;  // ukuran sub-array kiri
	int a2 = kanan - tengah;     // ukuran sub-array kanan

    // Array sementara untuk menyimpan salinan sub-array kiri dan kanan
	identitas_mobil kiriArray[10];
	identitas_mobil kananArray[10];
  
    // Salin data ke array sementara
	for (int i = 0; i < a1; i++)
		kiriArray[i] = dataMobil[kiri + i];
	for (int j = 0; j < a2; j++)
		kananArray[j] = dataMobil[tengah + 1 + j];
  
	int i = 0, j = 0;
	int k = kiri;  // k = posisi penulisan hasil merge di dataMobil[]
    
    // Bandingkan elemen kiri dan kanan secara bergantian,
    // masukkan yang "lebih kecil" ke dataMobil[k]
	while (i < a1 && j < a2) {
		if (kondisi(kiriArray[i], kananArray[j], urut)) {
            // kiriArray[i] lebih besar → masukkan kiriArray[i] dulu
            // ⚠️ Catatan: logika ini terbalik dari merge sort standar,
            //    tapi tetap menghasilkan urutan benar karena kondisi() sudah dikalibrasi
			dataMobil[k] = kiriArray[i];
			i++;
		} else {
            // kananArray[j] lebih kecil atau sama → masukkan kananArray[j]
           dataMobil[k] = kananArray[j];
           j++;
		}
		k++;
	}
    
    // Salin sisa elemen kiri yang belum diproses (jika ada)
	while (i < a1) {
		dataMobil[k] = kiriArray[i];
		i++;
		k++;
	}
    // Salin sisa elemen kanan yang belum diproses (jika ada)
	while (j < a2) {
		dataMobil[k] = kananArray[j];
		j++;
		k++;
	}
}

// ============================================================
// FUNGSI: merge2(awal, akhir) — rekursi merge_sort
// Membagi array terus menjadi dua bagian secara rekursi
// sampai ukurannya 1 (sudah "terurut" secara trivial),
// lalu panggil merge() saat naik kembali dari rekursi.
// Kompleksitas waktu: O(n log n) di semua kasus.
// ============================================================
void merge2(int awal, int akhir){
	if (awal >= akhir)  // base case: satu elemen atau kosong → sudah terurut
        return;
    int tengah = awal + (akhir - awal) / 2;  // hitung titik tengah (cara ini menghindari integer overflow)
    merge2(awal, tengah);        // rekursi belah kiri
    merge2(tengah + 1, akhir);   // rekursi belah kanan
    merge(awal, tengah, akhir);  // gabungkan dua bagian yang sudah terurut
}

// Wrapper yang dipanggil dari menu sorting
void merge_sort(){
	merge2(0, jumlah_data - 1);	
}

// ============================================================
// FUNGSI: sorting()
// Menu interaktif untuk memilih algoritma sort, file sumber,
// dan kolom yang dijadikan kunci pengurutan.
// Punya loop do...while sendiri agar user bisa ulangi tanpa balik menu utama.
// ============================================================
void sorting(){
	int pilihsort;
	char ulangsort, kembali;
	
	do{
        // --- Sub-loop pilih algoritma ---
		do{ 
			cout << "\nMENU SORTING : \n";
			cout<<setfill('=')<<setw(27)<<"="<<endl;
			cout << "1. BUBBLE SORT\n";
			cout << "2. SELECTION SORT\n";
			cout << "3. INSERTION SORT\n";
			cout << "4. SHELL SORT\n";
			cout << "5. QUICK SORT\n";
			cout << "6. MERGE SORT\n";
			cout << "7. Kembali ke MENU UTAMA\n";
			cout<<setfill('=')<<setw(27)<<"="<<endl;
			cout << "\nPilih : ";
			cin >> pilihsort;
			system("cls");
			
            // validasi: tolak input di luar range 1-7
			if(pilihsort < 1 || pilihsort > 7){
				cout << "Pilihan tidak valid!\n";
				system("pause");
				system("cls");
			}
		} while(pilihsort < 1 || pilihsort > 7);  // ulangi jika input tidak valid
		
        // --- Pilih dan baca file sumber ---
		tampil_file();
        cout << "\n\nData yang disorting dari file : ";
        string fileSort;
        cin >> fileSort;
        cin.ignore();
        
        // Reset jumlah_data, baca ulang dari file yang dipilih
        jumlah_data = 0;
        string baris;
        ifstream fileSortIn(fileSort);
        if(!fileSortIn.is_open()){
            cout << "File tidak ditemukan!\n";
            system("pause");
        }
        
        // Parsing isi file → dataMobil[] (sama dengan cara di tampil_data)
        while(getline(fileSortIn, baris) && jumlah_data < 10){
            int pisah1 = baris.find('|');
            int pisah2 = baris.find('|', pisah1 + 1);
            dataMobil[jumlah_data].no_stnk = stol(baris.substr(0, pisah1));
            strncpy(dataMobil[jumlah_data].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
            strncpy(dataMobil[jumlah_data].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
            jumlah_data++;
        }
        fileSortIn.close();
        
        if(jumlah_data == 0){
            cout << "File kosong.\n";
            system("pause");
		}
        
        // --- Pilih kolom kunci pengurutan → disimpan ke variabel global 'urut' ---
        do{
            cout << "\n Pengurutan berdasarkan: \n";
            cout<<setfill('=')<<setw(27)<<"="<<endl;
		    cout << "1. No. STNK\n";
		    cout << "2. Jenis Mobil\n";
		    cout << "3. Warna Mobil\n";
			cout << setfill('=') << setw(27) << "=" << endl;
            cout << "Pilih: ";
            cin >> urut;
        } while(urut < 1 || urut > 3);  // ulangi jika input tidak valid

		system("cls");

        // Tampilkan data SEBELUM di-sort sebagai pembanding
		cout << "\nData sebelum disorting\n";
		cetak_tabel();

        // --- Panggil fungsi sort sesuai pilihan, lalu tampilkan hasilnya ---
		switch(pilihsort) {
			case 1 :
				bubble_sort();
				cout << "\nData urut dengan BUBBLE SORT\n";
			break;
			case 2 :
				selection_sort();
				cout << "\nData urut dengan SELECTION SORT\n";
			break;
			case 3 :
				insertion_sort();
				cout << "\nData urut dengan INSERTION SORT\n";
			break;
			case 4 :
				shell_sort();
				cout << "\nData urut dengan SHELL SORT\n";
			break;
			case 5 :
				quick_sort();
				cout << "\nData urut dengan QUICK SORT\n";
			break;
			case 6 :
				merge_sort();
				cout << "\nData urut dengan MERGE SORT\n";
			break;
			case 7 :
				return;  // langsung kembali ke menu utama
			break;
			default :
				cout<<"Invalid menu!";
			break;
		}
		
		cetak_tabel();  // tampilkan data SESUDAH di-sort
		
        // --- Tanya apakah mau ulangi sorting ---
		cout << "\nUlangi sorting? (y/t) : ";
		cin >> ulangsort;
		system("cls");
		
		if(ulangsort == 't'){
            // Jika tidak mau ulangi, tanya apakah mau kembali ke menu utama
			cout << "\nKembali ke menu utama? (y/t) : ";
			cin >> kembali;
			if(kembali == 'y'){
				return;  // kembali ke main()
			} else { 
                cout << "Keluar dari program...\n\n";
                system("pause");
                exit(0);  // hentikan program sepenuhnya
            }
		}
	} while(ulangsort == 'y');  // ulangi jika user mau sorting lagi
}

// ============================================================
// FUNGSI: bub_sort_searchmerge(jml)
// Bubble sort versi sederhana, hanya untuk keperluan:
//   1. binary() — data harus terurut sebelum binary search
//   2. merging_urut() — data gabungan di-sort sebelum disimpan
// Sort berdasarkan no_stnk secara ascending (tidak pakai kondisi() global).
// Parameter 'jml' dipakai karena jumlah_data global belum tentu di-set.
// ============================================================
void bub_sort_searchmerge(int jml){
	for(int i = 0; i < jml - 1; i++){
		for(int j = 0; j < jml - i - 1; j++){
            // bandingkan langsung no_stnk (bukan lewat kondisi() global)
			if(dataMobil[j].no_stnk > dataMobil[j + 1].no_stnk){
				swap(dataMobil[j], dataMobil[j + 1]);
			}
		}
	}
}

// ============================================================
// FUNGSI: sequensial()
// Mencari data berdasarkan no_stnk menggunakan Sequential Search.
// Cek satu per satu dari index 0 sampai ketemu atau habis.
// Tidak membutuhkan data terurut.
// Kompleksitas: O(n) — semakin banyak data, semakin lama.
// ============================================================
void sequensial(){
    int i=0, n=0;
    bool found=false;  // flag: true jika data ditemukan
    string baris;
	
	system("pause");
	system("cls");
	
    cout<<"SEQUENSIAL SEARCH\n";
    cout<<setfill('=')<<setw(18)<<"="<<endl;
    
    // Buka file yang namanya disimpan di variabel global 'filecari'
    ifstream cari(filecari);
    if(cari.is_open()){
        // Baca dan parsing file → dataMobil[] (cara sama seperti tampil_data)
		while(getline(cari, baris) && n < 10){
			int pisah1 = baris.find('|');
			int pisah2 = baris.find('|', pisah1 + 1);
			dataMobil[n].no_stnk = stol(baris.substr(0, pisah1));
			strncpy(dataMobil[n].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
			strncpy(dataMobil[n].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
			n++;
		}
		jumlah_data = n;
		
        cout<<"\nMasukkan No. STNK yang dicari : ";
        cin>>cari_stnk;
        
        // Loop: terus cek selama belum habis (i < jumlah_data) dan belum ketemu (!found)
        while((i<jumlah_data) && (!found)){
            if(dataMobil[i].no_stnk == cari_stnk){
                found=true;  // ketemu! i sekarang = indeks data yang dicari
            } else {
                i++;         // belum ketemu, geser ke elemen berikutnya
            }
        }
        if(found){
            // Tampilkan data pada indeks i yang berhasil ditemukan
            cout << "Data ditemukan:\n";
            cout << setfill('=') << setw(27) << "=" << endl;
            cout << "No.STNK\t\t: " << dataMobil[i].no_stnk << endl;
            cout << "Jenis Mobil\t: " << dataMobil[i].jenis_mobil << endl;
            cout << "Warna Mobil\t: " << dataMobil[i].warna_mobil << endl;
            cout << setfill('=') << setw(27) << "=" << endl;
        } else {
            cout << "Mobil dengan No.STNK " << cari_stnk << " tidak ditemukan.\n";
        }
        cari.close();
    } else{
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }
}

// ============================================================
// FUNGSI: binary()
// Mencari data berdasarkan no_stnk menggunakan Binary Search.
// Data HARUS terurut → bub_sort_searchmerge() dipanggil lebih dulu.
// Cara kerja: cek elemen tengah, jika tidak cocok sempitkan rentang
// ke kiri atau kanan tergantung perbandingan nilai.
// Kompleksitas: O(log n) — jauh lebih cepat dari sequential untuk data besar.
// ============================================================
void binary(){
    int n=0;
    bool found=false;
    string baris;
    
    system("pause");
	system("cls");
    
    cout<<"BINARY SEARCH\n";
    cout<<setfill('=')<<setw(18)<<"="<<endl;

    ifstream cari(filecari);
    if(cari.is_open()){
        // Baca dan parsing file → dataMobil[] (cara sama seperti fungsi lain)
		while(getline(cari, baris) && n < 10){
			int pisah1 = baris.find('|');
			int pisah2 = baris.find('|', pisah1 + 1);
			dataMobil[n].no_stnk = stol(baris.substr(0, pisah1));
			strncpy(dataMobil[n].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
			strncpy(dataMobil[n].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
			n++;
		}
		
        // ⚠️ WAJIB: sort dulu sebelum binary search, karena binary search
        // hanya benar jika data sudah terurut ascending
		bub_sort_searchmerge(n);
		
        // left dan right = batas rentang pencarian saat ini
		int left=0, right=n-1, tengah;
		 
        cout<<"\nMasukkan No. STNK yang dicari : ";
        cin>>cari_stnk;

        while((left<=right) && (!found)){
            tengah = (left+right)/2;  // cek elemen di tengah rentang

            if(dataMobil[tengah].no_stnk == cari_stnk){
                found=true;  // ketemu di indeks 'tengah'
            } else {
                if(cari_stnk < dataMobil[tengah].no_stnk){
                    right=tengah-1;  // target ada di sisi kiri → persempit ke kiri
                } else{
                    left=tengah+1;   // target ada di sisi kanan → persempit ke kanan
                }
            }
        }
        if(found){
            // Tampilkan data pada indeks 'tengah' yang ditemukan
            cout<<"Data ditemukan:\n";
            cout<<setfill('=')<<setw(27)<<"="<<endl;
            cout<<"No.STNK\t\t: "<<dataMobil[tengah].no_stnk<<endl;
            cout<<"Jenis Mobil\t: "<<dataMobil[tengah].jenis_mobil<<endl;
            cout<<"Warna Mobil\t: "<<dataMobil[tengah].warna_mobil<<endl;
            cout<<setfill('=')<<setw(27)<<"="<<endl;
        } else{
            cout<<"Mobil dengan No.STNK "<<cari_stnk<<" tidak ditemukan.\n";
        }
        cari.close();
    } else {
        cout<<"Gagal membuka file!"<<endl;
        system("pause");
        return;
    }
}

// ============================================================
// FUNGSI: searching()
// Menu interaktif untuk memilih metode pencarian (sequential/binary).
// Punya loop do...while sendiri agar user bisa cari ulang.
// ============================================================
void searching(){
	int menu_search;
    char balik, balik_menu;

    do{
        cout<<setfill('=')<<setw(27)<<"="<<endl;
        cout<<"   Menu Searching\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "1. Sequensial Search\n";
		cout << "2. Binary Search\n";
		cout << "3. Kembali ke MENU UTAMA\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "Pilih : ";
		cin >> menu_search;

        system("cls");
		
        // Tampilkan daftar file, lalu minta nama file yang mau dicari
        // nama file disimpan ke variabel global 'filecari'
		tampil_file();
        cout << "\n\nData yang dicari dari file : ";
        cin >> filecari;
        cin.ignore();

        // Panggil fungsi search sesuai pilihan
        switch(menu_search){
            case 1 :
                sequensial();
            break;
            case 2 :
                binary();
            break;
            case 3 :
				return;  // kembali ke menu utama
            break;
            default :
                cout<<"Invalid menu!";
            break;
        }

        // Tanya apakah mau cari ulang
        cout<<"\nCari ulang? (y/t) : ";
        cin>>balik;
        system("cls");

        if(balik == 't'){
            // Jika tidak mau cari ulang, tanya apakah kembali ke menu utama
            cout<<"\nKembali ke menu utama? (y/t) : ";
            cin>>balik_menu;
            if(balik_menu == 'y'){
                return;  // kembali ke main()
            } else {
                cout<<"Keluar dari program...\n\n";
                system("pause");
                exit(0);  // hentikan program
            }
            return;
        }
	} while(menu_search != 3);  // ulangi jika bukan pilihan keluar
}

// ============================================================
// FUNGSI: merging_urut()
// Menggabungkan isi dari beberapa file (maks 4) menjadi satu file baru
// yang sudah terurut berdasarkan no_stnk secara ascending.
// ============================================================
void merging_urut(){
    char balik_menu;
    string filename[4];   // array untuk menyimpan nama-nama file yang digabung
    int banyak_file, n = 0;  // n = total data yang terkumpul dari semua file
    string baris;
    
    tampil_file();  // tampilkan file yang tersedia

    cout<<"\n\nBanyak file yang akan di-merge urut (max 4) : ";
    cin>>banyak_file;
    if(banyak_file > 4 || banyak_file <= 0) {
        cout << "Jumlah file tidak valid!\n";
        return;
    }
    
    cin.ignore();
    
    // Input nama-nama file yang akan digabung
    for (int i=0; i < banyak_file; i++){
        cout<<"Nama file "<<i+1<<" : ";
        cin>>filename[i];
    }
    cout << "Disimpan di file bernama (tanpa spasi) : ";
    cin >> filemerge;  // nama file output hasil merge

    // Baca semua file satu per satu, akumulasi datanya ke dataMobil[]
    for(int i=0; i < banyak_file; i++){
        ifstream file(filename[i]);
        if(!file.is_open()){
            cout<<"Gagal membuka file!"<<endl;
            system("pause");
            return;
        }
        // Parsing tiap baris → dataMobil[n], n terus bertambah lintas file
        while(getline(file, baris) && n < 10){
			int pisah1 = baris.find('|');
			int pisah2 = baris.find('|', pisah1 + 1);

			string stnk_str  = baris.substr(0, pisah1);
			string jenis_str = baris.substr(pisah1 + 1, pisah2 - pisah1 - 1);
			string warna_str = baris.substr(pisah2 + 1);

			dataMobil[n].no_stnk = stol(stnk_str);
			strncpy(dataMobil[n].jenis_mobil, jenis_str.c_str(), 49);
			strncpy(dataMobil[n].warna_mobil, warna_str.c_str(), 49);
			n++;
        }
        file.close();
    }
    
    // Sort semua data gabungan berdasarkan no_stnk sebelum disimpan
    bub_sort_searchmerge(n);
    
    // Tulis hasil merge yang sudah terurut ke file output
    ofstream filehasil(file);
    if(!filehasil.is_open()){
        cout<<"Gagal membuka file!"<<endl;
        system("pause");
        return;
    } else{
        for(int i=0; i < n; i++){
            // Format sama: no_stnk|jenis|warna
            filehasil << dataMobil[i].no_stnk << "|"
					  << dataMobil[i].jenis_mobil << "|"
					  << dataMobil[i].warna_mobil << endl;
        }
        filehasil.close();
    }
    
    // Tampilkan hasil merge di layar
    cout << "\nDATA MOBIL HASIL MERGE URUT" << endl;
    cout << setfill('=') << setw (58) << "=" << endl;
    cout << setfill(' ');
    cout << left << setw(15) << "No.STNK" 
         << setw(25) << "Jenis Mobil" 
         << setw(18) << "Warna Mobil" << endl;
    cout << setfill('=') << setw (58) << "=" << endl;
    cout << setfill(' ');

    // Buka file hasil untuk verifikasi (sebenarnya data sudah ada di dataMobil[])
    ifstream filehasil_in(filemerge);
    if(!filehasil_in.is_open()){
        cout<<"Gagal membuka file!"<<endl;
        system("pause");
        return;
    } else {
        // Tampilkan dari dataMobil[] yang sudah di-sort (bukan baca ulang dari file)
        for(int i = 0; i < n; i++){
        cout << left << setw(15) << dataMobil[i].no_stnk 
             << setw(25) << dataMobil[i].jenis_mobil 
             << setw(18) << dataMobil[i].warna_mobil << endl;
		}
    }
    
    // Tanya apakah kembali ke menu utama atau keluar
    cout<<"\nKembali ke menu utama? (y/t) : ";
    cin>>balik_menu;
    if(balik_menu == 'y'){
		return;  // kembali ke main()
    } else {
		cout<<"Keluar dari program...\n\n";
		system("pause");
        exit(0);
    }
}

// ============================================================
// FUNGSI: main()
// Entry point program. Menampilkan menu utama dalam loop do...while,
// membaca pilihan user, dan memanggil fungsi yang sesuai.
// Program berhenti saat user pilih 6 atau menjawab 't' saat ditanya keluar.
// ============================================================
int main(){
    int menu_utama;
    char kembali;
    
    // --- Setup working directory ---
    // Ambil path file .exe yang sedang berjalan, lalu set direktori aktif
    // ke folder tempat .exe berada. Ini supaya fopen/ifstream bisa menemukan
    // file .txt/.dat yang ada di folder yang sama dengan program.
    char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);  // dapatkan path lengkap .exe
	string dir(exePath);
	dir = dir.substr(0, dir.find_last_of("\\/"));  // ambil folder-nya saja (hapus nama file)
	SetCurrentDirectoryA(dir.c_str());             // set sebagai direktori aktif

    // --- Loop utama program ---
    // do...while: menu SELALU ditampilkan minimal sekali sebelum kondisi dicek
    do{
		cout<<setfill('=')<<setw(27)<<"="<<endl;
        cout<<"   MENU UTAMA DATA MOBIL\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "1. INPUT DATA\n";
		cout << "2. TAMPILKAN DATA\n";
		cout << "3. SEARCHING DATA\n";
		cout << "4. SORTING DATA\n";
        cout << "5. MERGING URUT FILE\n";
		cout << "6. KELUAR\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "Pilih menu : ";
		cin >> menu_utama;  // baca pilihan → menentukan case mana yang jalan
		cout<<setfill('=')<<setw(27)<<"="<<endl;
		
		system("cls");  // bersihkan layar sebelum masuk fungsi
		
		switch(menu_utama){
            case 1:
                input_data();   // terima input & simpan ke file
                cout<<setfill('=')<<setw(27)<<"="<<endl;
                cout<<"Kembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 'y'){
                    system("cls");
                } else {
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
            break;
            case 2:
                tampil_data(jumlah_data);  // baca file & tampilkan tabel
                cout<<"\nKembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 'y'){
                    system("cls");
                } else {
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
            break;
            case 3:
                searching();    // menu searching (punya loop sendiri di dalam)
                system("cls");
            break;
            case 4:
                sorting();      // menu sorting (punya loop sendiri di dalam)
                system("cls");
            break;
            case 5:
                merging_urut(); // gabung & urutkan beberapa file
                system("cls");
            break;
            case 6:
                cout<<"Keluar dari program...\n\n";
                system("pause");
                return 0;  // keluar dari main() → program selesai
            break;
            default :
                // Jika input bukan 1-6
				cout<<"Menu tidak tersedia.\n";
                cout<<"Kembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 't'){
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
                system("cls");
			break;
        }
    } while (menu_utama != 6);  // loop selama bukan pilihan keluar
}
