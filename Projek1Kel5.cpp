//Kelompok 5 : 123250050, 123250060, 123250082

#include <iostream>
#include <iomanip>
using namespace std;

struct data_mobil{
    long no_stnk;
    string jenis_mobil;
    string warna_mobil;
} dataMobil[10];

int jumlah_data = 0;

void input_data(int menu){
	cout << "INPUT DATA" << endl;
        cout << "=============================" << endl;
        cout << "Jumlah data (maks 10) : ";
         cin >> jumlah_data;

        if (jumlah_data > 10) {
        cout << "Jumlah data lebih dari 10!";
        } 

    for (int i = 0; i < jumlah_data; i++) {
        cout << "Data ke-" << i + 1 << endl;
        cout << "No. STNK : ";
          cin >> dataMobil[i].no_stnk;
          cin.ignore();
        cout << "Jenis Mobil : ";
         getline(cin, dataMobil[i].jenis_mobil);
        cout << "Warna Mobil : ";
         getline(cin, dataMobil[i].warna_mobil);
        
         cout << endl;
    }
    
}

void tampil_data(int menu){
    if (jumlah_data == 0) {
        cout << "Data masih kosong!\n" << endl;
    }
        cout << "DATA MOBIL" << endl;
        cout << setfill('=') << setw (58) << "=" << endl;
        cout << setfill(' ');
        cout << left << setw(5) << "No"
             << setw (15) << "No.STNK"
             << setw (20) << "Jenis Mobil"
             << setw (15) << "Warna Mobil" << endl;
        cout << setfill('=') << setw (58) << "=" << endl;
        cout << setfill(' ');
    
		for(int i = 0;i < jumlah_data; i++){
			cout << left << setw(5) << i
				 << setw(15) << dataMobil[i].no_stnk
				 << setw(20) << dataMobil[i].jenis_mobil
				 << setw(15) << dataMobil[i].warna_mobil << endl;
    }
}

void searching(int menu){

}


void bubble_sort(){
	
		cout << "\nData sebelum disorting\n";
		tampil_data(0);

		for(int i = 0; i < jumlah_data - 1; i++){
			for(int j = 0; j < jumlah_data - i - 1; j++){
				if(dataMobil[j].no_stnk > dataMobil[j+1].no_stnk){
					swap(dataMobil[j], dataMobil[j + 1]);
				}
			}
		}
	
		cout << "\nData urut by NO. STNK dengan BUBBLE SORT\n";
		tampil_data(0);
}

void selection_sort(){
	
		cout << "\nData sebelum disorting\n";
		tampil_data(0);

		for(int i = 0; i < jumlah_data - 1; i++) {
			int k = i;
			for(int j = i + 1; j < jumlah_data; j++) {
				if (dataMobil[j].jenis_mobil < dataMobil[k].jenis_mobil) {
					k = j;
				}
			}
			swap(dataMobil[i], dataMobil[k]);
			cout << "\n";
		}
	
		cout << "\nData urut JENIS MOBIL dengan SELECTION SORT\n";
		tampil_data(0);
}

void insertion_sort(){

		cout << "\nData sebelum disorting\n";
		tampil_data(0);

		for (int i = 1; i < jumlah_data; i++){
			data_mobil temp = dataMobil[i]; 
			int j = i - 1;
			while (j >= 0 && dataMobil[j].warna_mobil > temp.warna_mobil){
				dataMobil[j + 1] = dataMobil[j];
				j--;
			}
			dataMobil[j + 1] = temp;
		}

		cout << "\nData urut by WARNA MOBIL dengan INSERTION SORT\n";
		tampil_data(0);
}

void shell_sort(){

		cout << "\nData sebelum disorting\n";
		tampil_data(0);

		for (int jarak = jumlah_data / 2; jarak > 0; jarak = jarak / 2) {
			for (int i = jarak; i < jumlah_data; i++) {
				for (int j = i - jarak; j >= 0; j = j - jarak) {
					if (dataMobil[j + jarak].no_stnk < dataMobil[j].no_stnk){
						swap(dataMobil[j], dataMobil[j + jarak]); 
					}
				}
			}
		}

		cout << "\nData urut by NO. STNK dengan SHELL SORT\n";
		tampil_data(0);
}

int bagi(int awal, int akhir){
	int ip = awal;  
	string pivot = dataMobil[akhir].jenis_mobil;
		
	for(int i = awal; i < akhir; i++){
		if(dataMobil[i].jenis_mobil <= pivot) {
				swap(dataMobil[i], dataMobil[ip]);
				ip++;
      }
    }
    swap(dataMobil[akhir], dataMobil[ip]);
    return ip;
}

void quick(int awal, int akhir){
	if(awal < akhir){
		int ip = bagi(awal, akhir);          
        quick(awal, ip-1);            
        quick(ip+1, akhir);
	}
}

void quick_sort(){
	
		cout << "\nData sebelum disorting\n";
		tampil_data(0);
	
	 quick(0, jumlah_data-1);

	cout << "\nData urut by JENIS MOBIL dengan QUUICK SORT\n";
	tampil_data(0);
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
			if (kiriArray[i].warna_mobil <= kananArray[j].warna_mobil) {
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

		cout << "\nData sebelum disorting\n";
		tampil_data(0);
		
		merge2(0, jumlah_data - 1);
		
		cout << "\nData urut by WARNA MOBIL dengan MERGE SORT\n";
		tampil_data(0);
}

void sorting(int menu){
	int pilihsort;
	char ulangsort, kembali;
	
	do{ 
		cout << "MENU SORTING : \n";
		cout << setfill('=') << setw(25) << "=" << endl;
		cout << "1. BUBBLE SORT\n";
		cout << "2. SELECTION SORT\n";
		cout << "3. INSERTION SORT\n";
		cout << "4. SHELL SORT\n";
		cout << "5. QUICK SORT\n";
		cout << "6. MERGE SORT\n";
		cout << "7. Kembali ke MENU UTAMA\n";
		cout << setfill('=') << setw(25) << "=";
		
		cout << "\nPilih : ";
			cin >> pilihsort;
			
			system("cls");
			
		switch(pilihsort) {
			case 1 :
				bubble_sort();
				break;
			case 2 :
				selection_sort();
				break;
			case 3 :
				insertion_sort();
				break;
			case 4 :
				shell_sort();
				break;
			case 5 :
				quick_sort();
				break;
			case 6 :
				merge_sort();
				break;
			case 7 :
				return;
				break;
		}
		cout << "\nUlangi sorting? (y/t) : ";
			cin >> ulangsort;
			
			system("cls");
		
		if(ulangsort == 't'){
			cout << "\nKembali ke menu utama? (y/t) : ";
				cin >> kembali;
		
			if(kembali == 'y'){
				return;
			}
		}
	} while(ulangsort == 'y');
}


int main(){
    int menu_utama;
    char kembali;

    do{
		cout<<setfill('=')<<setw(27)<<"="<<endl;
        cout<<"   MENU UTAMA DATA MOBIL\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		
		cout << "1. INPUT DATA\n";
		cout << "2. TAMPILKAN DATA\n";
		cout << "3. SEARCHING DATA\n";
		cout << "4. SORTING DATA\n";
		cout << "5. KELUAR\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "Pilih menu : ";
		cin >> menu_utama;
		
		system("cls");
		
		switch(menu_utama){
            case 1:
                input_data(menu_utama);
                system("cls");
            break;
            case 2:
                tampil_data(menu_utama);
            break;
            case 3:
                searching(menu_utama);
                system("cls");
            break;
            case 4:
                sorting(menu_utama);
                system("cls");
                return 0;
            break;
            case 5:
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
    } while (menu_utama != 5);
    
}

