#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h> 

using namespace std;	
const int rozmiar = 500;

std::string f_wylosuj ()
	{ 	
		srand(time(NULL));
		//std::string wynik;
		std::string zbior[62]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
		std::string wynik="";
		
    for (int i = 0; i < 5; i++)  
        wynik = wynik + zbior[rand() % 62]; 
    return wynik;
	}
//-------------------------------------------------------------------------------------
bool f_czyZawieraKropke ( string v_url)
{
	std::string v_szukanyZnak = ".";
	size_t znalezionaPozycja = v_url.find( v_szukanyZnak );
	if( znalezionaPozycja != std::string::npos )
	         return true;
	    else
	         return false;
}
//-------------------------------------------------------------------------------------
void f_czyPlikIstnieje()
{	
	fstream plik;
	plik.open ("url_file.txt", ios::in);
	if (plik.good()==false)
		{	plik.open( "url_file.txt", ios::out | ios::app );
		}
    plik.close();
}
//-------------------------------------------------------------------------------------
string f_czyBylaWylosowana (std::string v_url)
{
    std::string tab_short_url[rozmiar];
    int i,j;
	fstream plik;
	
	plik.open ("url_file.txt", ios::in);
	if (plik.good()==false)
		{	cout <<"Plik nie istnieje" <<endl;	
			return "BRAK" ;
		}
	string v_linia;
	i=0;
	//cout << "true : " << true << endl; //1
	//cout << "false: " << false << endl;	//0	
	while (getline(plik, v_linia))
		{
			tab_short_url[i] = v_linia;
			i++;
		}
	plik.close();		
		for (j =0; j<i; j++)
		{	
			size_t znalezionaPozycja = tab_short_url[j].find( v_url );
			if( znalezionaPozycja != std::string::npos )
			//cout << "znaleziono url"<< endl;
			//getch();
			return tab_short_url[j];	
		}
			return "BRAK";	 
}
//-------------------------------------------------------------------------------------
void f_zapisz_url2file (std::string v_url, std::string & v_short_url)
{
    fstream plik;
    plik.open( "url_file.txt", ios::out | ios::app );
            plik << "url: "<< v_url <<"; "<< "short url: www.ag.pl/"<< v_short_url <<endl;
            plik.flush();
    plik.close();
//    return( 0 );
}

//-------------------------------------------------------------------------------------
void f_skracaj_url()
{	
	srand(time ( 0 ) );
	bool v_kropka = false;
	string tab_url[rozmiar], tab_short_url[rozmiar]; 
	string v_short_url="", v_url="", v_wylosowany_url="", v_wylosowany_short_url="";
	int n =0;
	
	do
	{ 	do
		{	cin.clear();
			cin.sync();
			system("cls");
			cout<<"Adres url musi zawierac przynajmniej jedna kropke. "<< endl;
			cout<<"podaj adres url: ";
			getline(cin, v_url);
			if (f_czyZawieraKropke( v_url ) == false)
			{ 	cout << "W Url-u brakuje kropki. " << endl;
				cout << "Press any key to continue..." << endl;
   				cin.clear();
   				cin.sync();
				getch();
			}
		} while (v_url.length() < 5 || v_url.length() > rozmiar || f_czyZawieraKropke( v_url ) == false);
		
		//v_kropka = f_czyZawieraKropke( v_url ) ;
		v_wylosowany_url = f_czyBylaWylosowana( v_url );
		if (v_wylosowany_url !="BRAK")
			{	cout<< "Url istnieje w bazie url-i: " << v_wylosowany_url << endl;
				cout<< "Press Enter to continue..." << endl;
				getch();
			}
	} while (v_wylosowany_url != "BRAK" // || v_kropka == false 
			);
	
	do
	{ 	//losowanie short url-a
		v_short_url = f_wylosuj ();
		v_wylosowany_short_url = f_czyBylaWylosowana( v_short_url );
		if ( v_wylosowany_url == "BRAK" && v_wylosowany_short_url  == "BRAK" )
			{	cout << "przyporzadkowany do URL-a skrot to: " << v_short_url << endl;
//				tab_url[n]=v_url;
//				tab_short_url[n]=v_short_url;
//				n=n+1;
				f_zapisz_url2file (v_url, v_short_url);				
			}
	} while (v_wylosowany_short_url  == "BRAK");
		
	cout<< endl << "Press Enter to continue ..."	<< endl;
	getch();	
}
//-------------------------------------------------------------------------------------
void f_wyswietl_historie()
{
	cin.ignore();
	cin.clear();
	system("cls");	
	fstream plik;
	plik.open ("url_file.txt", ios::in);
	if (plik.good()==false)
		{	cout <<"Plik nie istnieje" <<endl;	
			exit ;
		}
	string v_linia;
	//	int v_nr_linii;
	while (getline(plik, v_linia))
		{
			cout<< v_linia << endl;
		}
	plik.close();	
	cout<< endl << "Press any key to continue ..."	<< endl;
	getch();

}
//-------------------------------------------------------------------------------------
void f_znajdz_url()
{	string v_short_url, v_wylosowany_short_url;
	int n =0;
	
	cin.ignore();
	cin.clear();
	system("cls");
	cout<<"podaj adres URL lub skrot: \n";
	getline(cin, v_short_url);
		
	v_wylosowany_short_url = f_czyBylaWylosowana( v_short_url );
	if (v_wylosowany_short_url !="BRAK")
		{	cout<< "Znalazlem " << v_wylosowany_short_url << endl;		}
	else
		{	cout<< "Nie znalazlem takich danych w bazie url-i. " << endl;		}

	cout<< endl << "Press any key to continue ..."	<< endl;
	getch();
}
//-------------------------------------------------------------------------------------
int main()
{	
	char v_znak;
	f_czyPlikIstnieje();
    do 
	{		
			cin.clear();
			cin.sync();			
			system("cls");
			cout <<"*************** MENU ***************"	<< endl;
			cout << "1. skracanie URL-i" 					<< endl;
			cout << "2. wyszukiwanie URL-i i short URL-i"	<< endl;
			cout << "3. wyswietl historie" 					<< endl;
			cout << "4. wyjscie z programu" 				<< endl;
		    cout<<"Wybieram : ";
	    
	    v_znak = getchar();
	    switch (v_znak)
	    {
	       	case '1':
	            f_skracaj_url();
	            break;
	       	case '2':
	            f_znajdz_url();  
	            break;
	       	case '3':
	            f_wyswietl_historie();    
	            break;
	       	case '4':
	            exit(0);
	            break;
			default:
				cout << "Nie ma takiej opcji w menu."<< flush;
				Sleep(750); 
				break;
		}		
    } while (v_znak!='4');

	return 0;
}



