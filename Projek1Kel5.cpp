//Kelompok 5 : 123250050, 123250060, 123250082

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

FILE *ptr;
char namefile[20];
string namafile, filecari;
int jumlah_data, urut;
long cari_stnk;

struct data_mobil{
    long no_stnk;
    char jenis_mobil[50];
    char warna_mobil[50];
} dataMobil[10];

void tampil_file(){
    int urutan = 1;
    WIN32_FIND_DATAA daftar;
    
    cout << "Daftar file:\n";
    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');

    HANDLE cari1 = FindFirstFileA("*.txt", &daftar);
    if(cari1 != INVALID_HANDLE_VALUE){
        do {
            cout << urutan << ". " << daftar.cFileName << endl;
            urutan++;
        } while(FindNextFileA(cari1, &daftar));
        FindClose(cari1);
    } else {
        cout << "Tidak ada file (.txt)\n";
    }
    
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

void input_data(){
	cout << "\nINPUT DATA" << endl;
    cout << "=============================" << endl;
    cout << "Jumlah data (maks 10) : ";
    cin >> jumlah_data;
    
    if (jumlah_data > 10) {
        cout << "\nJumlah data lebih dari 10!\n";
        system("pause");
        return;
    } else if(jumlah_data <= 0){
		cout << "\nJumlah data terlalu sedikit.\n";
		system("pause");
	} 
    
    cout << "Disimpan di file bernama (tanpa spasi) : ";
    cin >> namefile;
    ptr = fopen(namefile,"w");
	if(ptr==NULL) {
		cout<<"\nError\n";
    } else {
	  cout<<endl;
	  for(int i=0; i<jumlah_data; i++){
		cout<<"Data ke-"<<i+1<<endl;
		cout << "No. STNK  : "; 
        cin >> dataMobil[i].no_stnk;
        cin.ignore();
		cout << "Jenis Mobil : "; 
        cin.getline(dataMobil[i].jenis_mobil, 50);
        cout << "Warna Mobil : ";
        cin.getline(dataMobil[i].warna_mobil, 50);
		fprintf(ptr, "%ld|%s|%s\n",
				dataMobil[i].no_stnk,
				dataMobil[i].jenis_mobil,
				dataMobil[i].warna_mobil);
	  }
	  fclose(ptr);
	}
}

void cetak_tabel(){
    cout << setfill('=') << setw(61) << "=" << endl;
    cout << setfill(' ');
    cout << left
         << setw(6)  << "No."
         << setw(15) << "No. STNK"
         << setw(20) << "Jenis Mobil"
         << setw(20) << "Warna Mobil" << endl;
    cout << setfill('=') << setw(61) << "=" << endl;
    cout << setfill(' ');
    for(int i = 0; i < jumlah_data; i++){
        cout << left
             << setw(6)  << i + 1
             << setw(15) << dataMobil[i].no_stnk
             << setw(20) << dataMobil[i].jenis_mobil
             << setw(20) << dataMobil[i].warna_mobil << endl;
    }
}

void tampil_data(int){
    string baris;

    cout << "\tTAMPIL DATA\n";
    cout << "==================================\n";
    
    tampil_file();
    
    cout << "Nama file yang akan ditampilkan : ";
    string namaFileTampil;
    cin >> namaFileTampil;
    cin.ignore();
    
    system("pause");
    system("cls");
    
    ifstream file(namefile);
	if(!file.is_open()){
		cout << "\nFile tidak ditemukan atau gagal dibuka!\n";
		return;
	}
	jumlah_data = 0;
	
	while(getline(file, baris) && jumlah_data < 10){
			int pisah1 = baris.find('|');
			int pisah2 = baris.find('|', pisah1 + 1);
			dataMobil[jumlah_data].no_stnk = stol(baris.substr(0, pisah1));
			strncpy(dataMobil[jumlah_data].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
			strncpy(dataMobil[jumlah_data].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
			jumlah_data++;
	}
	file.close();
	
    if(jumlah_data == 0){
        cout << "Tidak ada data dalam file.\n";
    }

    cout << "\nDATA MOBIL\n";
    cetak_tabel();
	
}

bool kondisi(data_mobil a, data_mobil b, int urut) {
    if(urut == 1) { 
        return a.no_stnk > b.no_stnk;
    } else if(urut == 2) {
        return strcmp(a.jenis_mobil, b.jenis_mobil) > 0;
    } else {
        return strcmp(a.warna_mobil, b.warna_mobil) > 0;
    };

}

void bubble_sort(){
	for(int i = 0; i < jumlah_data - 1; i++){
		for(int j = 0; j < jumlah_data - i - 1; j++){
			if(kondisi(dataMobil[j], dataMobil[j+1], urut)){
				swap(dataMobil[j], dataMobil[j + 1]);
			}
		}
	}
}

void selection_sort(){
	for(int i = 0; i < jumlah_data - 1; i++) {
		int k = i;
		for(int j = i + 1; j < jumlah_data; j++) {
			if (kondisi(dataMobil[k], dataMobil[j], urut)) {
				k = j;
			}
		}
		swap(dataMobil[i], dataMobil[k]);
	}
}

void insertion_sort(){
	for (int i = 1; i < jumlah_data; i++){
		data_mobil temp = dataMobil[i]; 
		int j = i - 1;
		while (j >= 0 && kondisi(dataMobil[j], temp, urut)){
			dataMobil[j + 1] = dataMobil[j];
			j--;
		}
		dataMobil[j + 1] = temp;
   	}
}

void shell_sort(){
	for (int jarak = jumlah_data / 2; jarak > 0; jarak = jarak / 2) {
		for (int i = jarak; i < jumlah_data; i++) {
			for (int j = i - jarak; j >= 0; j = j - jarak) {
				if (kondisi(dataMobil[j], dataMobil[j + jarak], urut)) {
					swap(dataMobil[j], dataMobil[j + jarak]); 
				}
			}
		}
	}
}

int bagi(int awal, int akhir, int urut){
	int ip = awal;  
	string pivot = dataMobil[akhir].jenis_mobil;
		
	for(int i = awal; i < akhir; i++){
		if(!kondisi(dataMobil[i], dataMobil[akhir], urut)) {
				swap(dataMobil[i], dataMobil[ip]);
				ip++;
      }
    }
    swap(dataMobil[akhir], dataMobil[ip]);
    return ip;
}

void quick(int awal, int akhir, int urut){
	if(awal < akhir){
		int ip = bagi(awal, akhir, urut);          
        quick(awal, ip-1, urut);            
        quick(ip+1, akhir, urut);
	}
}

void quick_sort(){
    quick(0, jumlah_data-1, urut);
}
		
void merge(int kiri, int tengah, int kanan){
	int a1 = tengah - kiri + 1;
	int a2 = kanan - tengah;
		data_mobil kiriArray[10];
		data_mobil kananArray[10];
  
	for (int i = 0; i < a1; i++)
		kiriArray[i] = dataMobil[kiri + i];
	for (int j = 0; j < a2; j++)
		kananArray[j] = dataMobil[tengah + 1 + j];
  
	int i= 0, j = 0;
	int k = kiri;
    
	while (i < a1 && j < a2) {
		if (kondisi(kiriArray[i], kananArray[j], urut)) {
			dataMobil[k] = kiriArray[i];
			i++;
		} else {
           dataMobil[k] = kananArray[j];
           j++;
		}
		 k++;
	}
    
	while (i < a1) {
		dataMobil[k] = kiriArray[i];
		i++;
		k++;
	}
	while (j < a2) {
		dataMobil[k] = kananArray[j];
		j++;
		k++;
	}
}

void merge2(int awal, int akhir){
	if (awal >= akhir)
        return;
    int tengah = awal + (akhir - awal) / 2;
    merge2(awal, tengah);
    merge2(tengah + 1, akhir);
    merge(awal, tengah, akhir);
}

void merge_sort(){
	merge2(0, jumlah_data - 1);	
}

void sorting(){
	int pilihsort;
	char ulangsort, kembali;
	
	do{
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
			
				if(pilihsort < 1 || pilihsort > 7){
					cout << "Pilihan tidak valid!\n";
					system("pause");
					system("cls");
				}
			} while(pilihsort < 1 || pilihsort > 7);
			
		tampil_file();
        cout << "\n\nData yang disorting dari file : ";
        string fileSort;
        cin >> fileSort;
        cin.ignore();
        
        jumlah_data = 0;
        string baris;
        ifstream fileSortIn(fileSort);
        if(!fileSortIn.is_open()){
            cout << "File tidak ditemukan!\n";
            system("pause");
        }
        
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
        
        do{
            cout << "\n Pengurutan berdasarkan: \n";
            cout<<setfill('=')<<setw(27)<<"="<<endl;
		    cout << "1. No. STNK\n";
		    cout << "2. Jenis Mobil\n";
		    cout << "3. Warna Mobil\n";
			cout << setfill('=') << setw(27) << "=" << endl;
            cout << "Pilih: ";
            cin >> urut;
        } while(urut < 1 || urut > 3);

		system("cls");

		cout << "\nData sebelum disorting\n";
		cetak_tabel();

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
				return;
			break;
			default :
				cout<<"Invalid menu!";
			break;
		}
		
		cetak_tabel();
		
		cout << "\nUlangi sorting? (y/t) : ";
			cin >> ulangsort;
			
		system("cls");
		
		if(ulangsort == 't'){
			cout << "\nKembali ke menu utama? (y/t) : ";
			cin >> kembali;
			if(kembali == 'y'){
				return;;
			} else { 
                cout << "Keluar dari program...\n\n";
                system("pause");
                exit(0);
            }
		}
	} while(ulangsort == 'y');
}

void bub_sort_searchmerge(int jml){
	for(int i = 0; i < jml - 1; i++){
		for(int j = 0; j < jml - i - 1; j++){
			if(dataMobil[j].no_stnk > dataMobil[j + 1].no_stnk){
				swap(dataMobil[j], dataMobil[j + 1]);
			}
		}
	}
}

void sequensial(){
    int i=0, n=0;
    bool found=false;
    string baris;
	
	system("pause");
	system("cls");
	
    cout<<"SEQUENSIAL SEARCH\n";
    cout<<setfill('=')<<setw(18)<<"="<<endl;
        
    ifstream cari(filecari);
    if(cari.is_open()){
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
        
        while((i<jumlah_data) && (!found)){
            if(dataMobil[i].no_stnk == cari_stnk){
                found=true;
            } else {
                i++;
            }
        }
        if(found){
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
		while(getline(cari, baris) && n < 10){
			int pisah1 = baris.find('|');
			int pisah2 = baris.find('|', pisah1 + 1);
			dataMobil[n].no_stnk = stol(baris.substr(0, pisah1));
			strncpy(dataMobil[n].jenis_mobil, baris.substr(pisah1+1, pisah2-pisah1-1).c_str(), 49);
			strncpy(dataMobil[n].warna_mobil, baris.substr(pisah2+1).c_str(), 49);
			n++;
		}
		
		bub_sort_searchmerge(n);
		
		int left=0, right=n-1, tengah;
		 
        cout<<"\nMasukkan No. STNK yang dicari : ";
        cin>>cari_stnk;
        while((left<=right) && (!found)){
            tengah = (left+right)/2;
            if(dataMobil[tengah].no_stnk == cari_stnk){
                found=true;
            }
            else{
                if(cari_stnk < dataMobil[tengah].no_stnk){
                    right=tengah-1;
                } else{
                    left=tengah+1;
                }
            }
        }
        if(found){
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
		
		tampil_file();
        cout << "\n\nData yang dicari dari file : ";
        cin >> filecari;
        cin.ignore();

        switch(menu_search){
            case 1 :
                sequensial();
            break;
            case 2 :
                binary();
            break;
            case 3 :
				return;
            break;
            default :
                cout<<"Invalid menu!";
            break;
        }

        cout<<"\nCari ulang? (y/t) : ";
        cin>>balik;
        
        system("cls");

        if(balik == 't'){
            cout<<"\nKembali ke menu utama? (y/t) : ";
            cin>>balik_menu;
            if(balik_menu == 'y'){
                return;
            } else {
                cout<<"Keluar dari program...\n\n";
                system("pause");
                exit(0);
            }
            return;
        }
	} while(menu_search != 3);
}

void merging_urut(){
    char balik_menu;
    string filename[4];
    int banyak_file, n = 0;
    string baris;
    
    tampil_file();

    cout<<"\n\nBanyak file yang akan di-merge urut (max 4) : ";
    cin>>banyak_file;
    if(banyak_file > 4 || banyak_file <= 0) {
        cout << "Jumlah file tidak valid!\n";
        return;
    }
    
    cin.ignore();
    
    for (int i=0; i < banyak_file; i++){
        cout<<"Nama file "<<i+1<<" : ";
        cin>>filename[i];
    }
    cout << "Disimpan di file bernama (tanpa spasi) : ";
    cin >> namafile;
    
    for(int i=0; i < banyak_file; i++){
        ifstream file(filename[i]);
        if(!file.is_open()){
            cout<<"Gagal membuka file!"<<endl;
            system("pause");
            return;
        }
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
    
    bub_sort_searchmerge(n);
    
    ofstream filehasil(namafile);
    if(!filehasil.is_open()){
        cout<<"Gagal membuka file!"<<endl;
        system("pause");
        return;
    } else{
        for(int i=0; i < n; i++){
            filehasil << dataMobil[i].no_stnk << "|"
					  << dataMobil[i].jenis_mobil << "|"
					  << dataMobil[i].warna_mobil << endl;
        }
        filehasil.close();
    }
    
    cout << "\nDATA MOBIL HASIL MERGE URUT" << endl;
    cout << setfill('=') << setw (58) << "=" << endl;
    cout << setfill(' ');
    cout << left << setw(15) << "No.STNK" 
         << setw(25) << "Jenis Mobil" 
         << setw(18) << "Warna Mobil" << endl;
    cout << setfill('=') << setw (58) << "=" << endl;
    cout << setfill(' ');

    ifstream filehasil_in(namafile);
    if(!filehasil_in.is_open()){
        cout<<"Gagal membuka file!"<<endl;
        system("pause");
        return;
    } else {
        for(int i = 0; i < n; i++){
        cout << left << setw(15) << dataMobil[i].no_stnk 
             << setw(25) << dataMobil[i].jenis_mobil 
             << setw(18) << dataMobil[i].warna_mobil << endl;
		}
    }
    
    cout<<"\nKembali ke menu utama? (y/t) : ";
    cin>>balik_menu;
    if(balik_menu == 'y'){
		return;
    } else {
		cout<<"Keluar dari program...\n\n";
		system("pause");
        exit(0);
    }
}

int main(){
    int menu_utama;
    char kembali;
    
    char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	string dir(exePath);
	dir = dir.substr(0, dir.find_last_of("\\/"));
	SetCurrentDirectoryA(dir.c_str());

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
		cin >> menu_utama;
		cout<<setfill('=')<<setw(27)<<"="<<endl;
		
		system("cls");
		
		switch(menu_utama){
            case 1:
                input_data();
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
                tampil_data(jumlah_data);
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
                searching();
                system("cls");
            break;
            case 4:
                sorting();
                system("cls");
            break;
            case 5:
                merging_urut();
                system("cls");
            break;
            case 6:
                cout<<"Keluar dari program...\n\n";
                system("pause");
                return 0;
            break;
            default :
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
    } while (menu_utama != 6);   
}
