//Kelompok 5 : 123250050, 123250060, 123250082

#include <iostream>
#include <iomanip>
using namespace std;

struct data_mobil{
    long no_stnk;
    string jenis_mobil;
    string warna_mobil;
} data[10];

void input_data(int menu){

}

void tampil_data(int menu){

}

void searching(int menu){

}

void sorting(int menu){

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
                system("cls");
            break;
            case 3:
                searching(menu_utama);
                system("cls");
            break;
            case 4:
                sorting(menu_utama);
                system("cls");
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

