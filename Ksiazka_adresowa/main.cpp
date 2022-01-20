#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Adresat
{
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};
struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};
void wczytajKsiazkeAdresowa (vector <Adresat>& adresaci)
{
    int ileKontakow=0;
    string linia;
    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in);
    if (plik.good()==false)
    {
        cout<<"Nie znaleziono lub nie udalo sie otworzyc pliku Ksiazka adresowa!"<<endl;
        Sleep(1000);
    }
    else
    {
        while(getline(plik, linia))
        {
            Adresat bufor;
            vector<string> adresyZpliku;
            stringstream liniaDoPodzielenia {linia};
            string wyraz;
            while(getline(liniaDoPodzielenia, wyraz, '|'))
            {
                adresyZpliku.push_back(wyraz);
            }
            bufor.id = atoi(adresyZpliku[0].c_str());
            bufor.imie = adresyZpliku[1];
            bufor.nazwisko = adresyZpliku[2];
            bufor.numerTelefonu = adresyZpliku[3];
            bufor.email = adresyZpliku[4];
            bufor.adres = adresyZpliku[5];
            adresaci.push_back(bufor);
            adresyZpliku.clear();
        }
        plik.close();
    }
}
void dodajNowyKontakt (vector <Adresat>& adresaci)
{
    int liczbaKontaktow = adresaci.size();
    int ostatniID;
    if (adresaci.size() == 0) ostatniID = 0;
    else ostatniID = adresaci.back().id;
    adresaci.push_back(Adresat());
    adresaci[liczbaKontaktow].id = ostatniID+1;
    cout<<"Podaj imie: ";
    cin>>adresaci[liczbaKontaktow].imie;
    cout<< "Podaj nazwisko: ";
    cin>>adresaci[liczbaKontaktow].nazwisko;
    cout<< "Podaj nr telefonu: ";
    cin.sync();
    getline(cin,adresaci[liczbaKontaktow].numerTelefonu);
    cout<< "Podaj email: ";
    cin>>adresaci[liczbaKontaktow].email;
    cout<< "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin,adresaci[liczbaKontaktow].adres);
    fstream plik;
    plik.open("Ksiazka adresowa.txt",ios::out | ios::app);
    plik<<adresaci[liczbaKontaktow].id<<"|";
    plik<<adresaci[liczbaKontaktow].imie<<"|";
    plik<<adresaci[liczbaKontaktow].nazwisko<<"|";
    plik<<adresaci[liczbaKontaktow].numerTelefonu<<"|";
    plik<<adresaci[liczbaKontaktow].email<<"|";
    plik<<adresaci[liczbaKontaktow].adres<<"|"<<endl;
    plik.close();
    cout<< "Kontakt zostal dodany.";
    Sleep(1000);
}
void szukajPoImieniu(vector <Adresat> adresaci)
{
    system("cls");
    string szukaneImie;
    cout<< "Podaj imie: ";
    cin>>szukaneImie;
    for (int i=0; i<adresaci.size(); i++)
    {
        if (adresaci[i].imie == szukaneImie)
        {
            cout<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
    }
    system("pause");
}
void szukajPoNazwisku(vector <Adresat> adresaci)
{
    system("cls");
    string szukaneNazwisko;
    cout<< "Podaj nazwisko: ";
    cin>>szukaneNazwisko;
    for (int i=0; i<adresaci.size(); i++)
    {
        if (adresaci[i].nazwisko == szukaneNazwisko)
        {
            cout<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
    }
    system("pause");
}
void wyswietlWszystkieKontakty(vector <Adresat> adresaci)
{
    system("cls");
    for (int i=0; i<adresaci.size(); i++)
    {
        cout<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
    }
    system("pause");
}
void usunKontakt (vector <Adresat>& adresaci)
{
    system("cls");
    int idDoUsuniecia;
    cout<<"Podaj numer ID adresata w celu jego usuniecia: ";
    cin>>idDoUsuniecia;
    char wybor;
    cout<< "Czy na pewno chcesz usunac tego adresata?"<<endl;
    for (int i=0; i<adresaci.size(); i++)
    {
        if (adresaci[i].id == idDoUsuniecia)
        {
            cout<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
    }
    cout<< "Potwierdz wciskajac klawisz t lub inny klawisz aby wrocic do menu: ";
    cin>>wybor;
    if (wybor== 't')
    {
        for (vector <Adresat>::iterator iter = adresaci.begin(); iter != adresaci.end(); iter++)
        {
            if (iter->id == idDoUsuniecia)
            {
                iter = adresaci.erase(iter);
                break;
            }
        }
    }
    else if (wybor != 't')
    {
        system("cls");
    }
}
void edytujWybraneDane(vector <Adresat>& adresaci, string noweDane, char ktoreDane, int idDoEdycji)
{
    for (int i=0; i<adresaci.size(); i++)
    {
        if (adresaci[i].id == idDoEdycji)
        {
            if (ktoreDane == '1')
            {
                adresaci[i].imie = noweDane;
            }
            else if (ktoreDane == '2')
            {
                adresaci[i].nazwisko = noweDane;
            }
            else if (ktoreDane == '3')
            {
                adresaci[i].numerTelefonu = noweDane;
            }
            else if (ktoreDane == '4')
            {
                adresaci[i].email = noweDane;
            }
            else if (ktoreDane == '5')
            {
                adresaci[i].adres = noweDane;
            }
        }
    }
}
void edytujKontakt (vector <Adresat>& adresaci)
{
    system("cls");
    int idDoEdycji;
    string noweDane;
    char wybor;
    cout<<"Podaj numer ID adresata w celu jego edytowania: ";
    cin>>idDoEdycji;
    cout<< "Aktualne dane tego adresata: ";
    for (int i=0; i<adresaci.size(); i++)
    {
        if (adresaci[i].id == idDoEdycji)
        {
            cout<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
    }
    cout<< "Wybierz dane do edycji: "<<endl;
    cout<< "1 - imie" <<endl;
    cout<< "2 - nazwisko" <<endl;
    cout<< "3 - numer telefonu" <<endl;
    cout<< "4 - email" <<endl;
    cout<< "5 - adres" <<endl;
    cout<< "6 - powrot do menu" <<endl;
    cout<< "Twoj wybor: ";
    cin>>wybor;
    if (wybor== '1')
    {
        cout<<"Podaj nowe imie: ";
        cin>>noweDane;
        edytujWybraneDane(adresaci, noweDane, wybor, idDoEdycji);
    }
    else if (wybor=='2')
    {
        cout<<"Podaj nowe nazwisko: ";
        cin>>noweDane;
        edytujWybraneDane(adresaci, noweDane, wybor, idDoEdycji);
    }
    else if (wybor=='3')
    {
        cout<<"Podaj nowy numer telefonu: ";
        cin.sync();
        getline(cin,noweDane);
        edytujWybraneDane(adresaci, noweDane, wybor, idDoEdycji);
    }
    else if (wybor=='4')
    {
        cout<<"Podaj nowy email: ";
        cin>>noweDane;
        edytujWybraneDane(adresaci, noweDane, wybor, idDoEdycji);
    }
    else if (wybor=='5')
    {
        cout<<"Podaj nowy adres: ";
        cin.sync();
        getline(cin,noweDane);
        edytujWybraneDane(adresaci, noweDane, wybor, idDoEdycji);
    }
    else if (wybor=='6')
        system("cls");
}
void zapiszZmianyDoPliku (vector <Adresat>& adresaci)
{
    int liczbaKontaktow = adresaci.size();
    fstream plik;
    plik.open("Ksiazka adresowa.txt",ios::out | ios::trunc);
    for (int i=0; i<liczbaKontaktow; i++)
    {
        plik<<adresaci[i].id<<"|";
        plik<<adresaci[i].imie<<"|";
        plik<<adresaci[i].nazwisko<<"|";
        plik<<adresaci[i].numerTelefonu<<"|";
        plik<<adresaci[i].email<<"|";
        plik<<adresaci[i].adres<<"|"<<endl;
    }
    plik.close();
    cout<< "Zapisano zmiany w pliku.";
    Sleep(1000);
}

int main()
{
    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    char wybor;

    while(true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout<< "1. Rejestracja" <<endl;
            cout<< "2. Logowanie" <<endl;
            cout<< "9. Zakoncz program" <<endl;
            cin>>wybor;

            if (wybor== '1')
            {
                //iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
            }
            else if (wybor=='2')
            {
                //idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                wczytajKsiazkeAdresowa(adresaci);
                idZalogowanegoUzytkownika++;
            }
            else if (wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<< "1. Dodaj adresata" <<endl;
            cout<< "2. Wyszukaj po imieniu" <<endl;
            cout<< "3. Wyszukaj po nazwisku" <<endl;
            cout<< "4. Wyswietl wszystkich adresatow" <<endl;
            cout<< "5. Usun adresata" <<endl;
            cout<< "6. Edytuj adresata" <<endl;
            cout<< "7. Zmiana hasla" <<endl;
            cout<< "9. Wyloguj sie" <<endl;
            cout<< "Twoj wybor: ";
            cin>>wybor;
            if (wybor== '1')
            {
                dodajNowyKontakt(adresaci);
            }
            else if (wybor=='2')
            {
                szukajPoImieniu(adresaci);
            }
            else if (wybor=='3')
            {
                szukajPoNazwisku(adresaci);
            }
            else if (wybor=='4')
            {
                wyswietlWszystkieKontakty(adresaci);
            }
            else if (wybor=='5')
            {
                usunKontakt(adresaci);
                zapiszZmianyDoPliku(adresaci);
            }
            else if (wybor=='6')
            {
                edytujKontakt(adresaci);
                zapiszZmianyDoPliku(adresaci);
            }
            else if (wybor=='7')
            {
                //zmianaHasla(uzytkownicy,iloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wybor=='9')
            {
                system("cls");
                idZalogowanegoUzytkownika = 0;
            }
        }

    }
    return 0;
}
