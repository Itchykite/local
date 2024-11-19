#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <filesystem>

class Student
{
public:
    std::string imie;
    std::string nazwisko;
    int numerIndeksu;
    float ocenaKoncowa;
    double pesel;
    std::string data_urodzenia = "DD-MM-RRRR";
    std::string data_rozpoczecia = "DD-MM-RRRR";
    std::string data_zakonczenia = "DD-MM-RRRR";

    void saveToFile(std::ofstream& outFile) const
    {
        outFile << imie << " " << nazwisko << " " << numerIndeksu << " " << ocenaKoncowa << " " << pesel << " " << data_urodzenia << " " << data_rozpoczecia << " " << data_zakonczenia << "\n";
    }

    void loadFromFile(std::ifstream& inFile)
    {
        inFile >> imie >> nazwisko >> numerIndeksu >> ocenaKoncowa >> pesel >> data_urodzenia >> data_rozpoczecia >> data_zakonczenia;
    }
};

void studentMenu(std::vector<Student>& bazaStudentow);
void bazaMenu(std::vector<Student>& bazaStudentow);
void mainMenu(std::vector<Student>& bazaStudentow);
void infoStudentMenu(std::vector<Student>& bazaStudentow);
int pobierzLiczbe();

bool czyIstniejeIndeks(const std::vector<Student>& baza, int numer) 
{
    for (const auto& student : baza) 
    {
        if (student.numerIndeksu == numer) return true;
    }

    return false;
}

void dodajStudenta(std::vector<Student>& baza)
{
    Student nowyStudent;
    std::cout << "Podaj imie studenta: ";
    std::cin >> nowyStudent.imie;
    std::cout << "Podaj nazwisko studenta: ";
    std::cin >> nowyStudent.nazwisko;
    std::cout << "Podaj numer indeksu studenta: ";
    std::cin >> nowyStudent.numerIndeksu;
    std::cout << "Podaj ocene koncowa studenta: ";
    std::cin >> nowyStudent.ocenaKoncowa;
    std::cout << "Podaj pesel studenta: ";
    std::cin >> nowyStudent.pesel;
    std::cout << "Podaj date urodzenia studenta: ";
    std::cin >> nowyStudent.data_urodzenia;
    std::cout << "Podaj date rozpoczecia studiow: ";
    std::cin >> nowyStudent.data_rozpoczecia;
    std::cout << "Podaj przewidywana date ukonczenia studiow: ";
    std::cin >> nowyStudent.data_zakonczenia;

    if (czyIstniejeIndeks(baza, nowyStudent.numerIndeksu))
    {
        std::cout << "\nStudent z takim numerem indeksu juz istnieje!" << std::endl;
    }

    else if(czyIstniejeIndeks(baza, nowyStudent.pesel))
    {
        std::cout << "\nStudent z takim peselem juz istnieje!" << std::endl;
    }

    else
    {
        baza.push_back(nowyStudent);
        std::cout << "\nStudent zostal dodany!\n";
    }
}

void wyswietlStudentow(const std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
        return;
    }

    std::cout << "\nLista studentow:\n";
    std::cout << std::setw(15) << "Imie"
        << std::setw(15) << "Nazwisko"
        << std::setw(15) << "Numer Indeksu"
        << std::setw(10) << "Ocena\n";
    std::cout << "-------------------------------------------------------------\n";

    for (const auto& student : baza)
    {
        std::cout << std::setw(15) << student.imie
            << std::setw(15) << student.nazwisko
            << std::setw(15) << student.numerIndeksu
            << std::setw(10) << student.ocenaKoncowa << '\n';
    }
}

void usunStudenta(std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
        return;
    }

    int numerIndeksu;
    std::cout << "\nPodaj numer indeksu studenta do usuniecia: ";
    numerIndeksu = pobierzLiczbe();

    for (auto it = baza.begin(); it != baza.end(); ++it)
    {
        if (it->numerIndeksu == numerIndeksu)
        {
            baza.erase(it);
            std::cout << "\nStudent zostal usuniety!\n";
            return;
        }
    }

    std::cout << "\nNie znaleziono studenta o podanym numerze indeksu.\n";
}

void zmianaStudent(std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
        return;
    }

    int numerIndeksu;
    std::cout << "\nPodaj numer indeksu studenta do zmiany oceny: ";
    std::cin >> numerIndeksu;

    for (auto& student : baza)
    {
        if (student.numerIndeksu == numerIndeksu)
        {
            std::cout << "Aktualna ocena studenta " << student.imie << " " << student.nazwisko << ": " << student.ocenaKoncowa << std::endl;
            std::cout << "Podaj nowa ocene: ";
            std::cin >> student.ocenaKoncowa;
            std::cout << "Ocena zostala zmieniona na " << student.ocenaKoncowa << ".\n";
            return;
        }
    }
}

void sortujStudentow(std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
        return;
    }

    int wybor;

    std::cout << "\nJak posortowac?" << std::endl;
    std::cout << "1. Po numerze indeksu\n";
    std::cout << "2. Po nazwisku\n";
    std::cout << "3. Po ocenie\n";
    std::cout << "Wybierz opcje: ";
    std::cin >> wybor;

    switch (wybor)
    {
    case 1:
        std::sort(baza.begin(), baza.end(), [](const Student& a, const Student& b)
            {
                return a.numerIndeksu < b.numerIndeksu;
            });
        break;
    case 2:
        std::sort(baza.begin(), baza.end(), [](const Student& a, const Student& b)
            {
                return a.nazwisko < b.nazwisko;
            });
        break;
    case 3:
        std::sort(baza.begin(), baza.end(), [](const Student& a, const Student& b)
            {
                return a.ocenaKoncowa < b.ocenaKoncowa;
            });
    default:
        std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        break;
    }
}

void znajdzStudent(std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
    }

    int wybor;
    std::cout << "\nPo czym filtrowac?\n";
    std::cout << "1. Imie\n";
    std::cout << "2. Nazwisko\n";
    std::cout << "3. Ocena\n";
    std::cout << "Wybierz opcje: ";
    std::cin >> wybor;

    if (wybor == 1)
    {
        bool found = false;

        std::string imie;
        std::cout << "\nPodaj imie: ";
        std::cin >> imie;

        std::cout << "\nLista studentow:\n";
        std::cout << std::setw(15) << "Imie"
            << std::setw(15) << "Nazwisko"
            << std::setw(15) << "Numer Indeksu"
            << std::setw(10) << "Ocena\n";
        std::cout << "-------------------------------------------------------------\n";

        for (auto& student : baza)
        {
            if (student.imie == imie)
            {
                found = true;

                std::cout << std::setw(15) << student.imie
                    << std::setw(15) << student.nazwisko
                    << std::setw(15) << student.numerIndeksu
                    << std::setw(10) << student.ocenaKoncowa << '\n';
            }
        }
    
        if (!found)
        {
            std::cerr << "\nBrak imienia w bazie!" << std::endl;
        }
    }

    else if (wybor == 2)
    {
        bool found = false;

        std::string nazwisko;
        std::cout << "\nPodaj Nazwisko: ";
        std::cin >> nazwisko;

        std::cout << "\nLista studentow:\n";
        std::cout << std::setw(15) << "Imie"
            << std::setw(15) << "Nazwisko"
            << std::setw(15) << "Numer Indeksu"
            << std::setw(10) << "Ocena\n";
        std::cout << "-------------------------------------------------------------\n";

        for (auto& student : baza)
        {
            if (student.nazwisko == nazwisko)
            {
                found = true;

                std::cout << std::setw(15) << student.imie
                    << std::setw(15) << student.nazwisko
                    << std::setw(15) << student.numerIndeksu
                    << std::setw(10) << student.ocenaKoncowa << '\n';
            }
        }

        if (!found)
        {
            std::cerr << "\nBrak nazwiska w bazie!" << std::endl;
        }
    }

    else if (wybor == 3)
    {
        bool found = false;

        int ocenaKoncowa;
        std::cout << "\nPodaj ocene: ";
        std::cin >> ocenaKoncowa;

        std::cout << "\nLista studentow:\n";
        std::cout << std::setw(15) << "Imie"
            << std::setw(15) << "Nazwisko"
            << std::setw(15) << "Numer Indeksu"
            << std::setw(10) << "Ocena\n";
        std::cout << "-------------------------------------------------------------\n";

        for (auto& student : baza)
        {
            if (student.ocenaKoncowa == ocenaKoncowa)
            {
                found = true;

                std::cout << std::setw(15) << student.imie
                    << std::setw(15) << student.nazwisko
                    << std::setw(15) << student.numerIndeksu
                    << std::setw(10) << student.ocenaKoncowa << '\n';
            }
        }

        if (!found)
        {
            std::cerr << "\nBrak oceny w bazie!" << std::endl;
        }
    }

    else
    {
        return;
    }
}

void jakieBazy()
{
    std::string path = "./bazy";

    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }

    else
    {
        try
        {
            std::cout << "\n--- LISTA BAZ ---\n";

            for (const auto& entry : std::filesystem::directory_iterator(path))
            {
                std::cout << entry.path().filename().string() << std::endl;
            }

        }

        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Blad: " << e.what() << std::endl;
        }
    }
}

void zapiszBaze(const std::vector<Student>& baza, const std::string& nazwa_pliku)
{
    std::string path = "bazy/";

    std::ofstream outFile(path + nazwa_pliku);

    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }

    else
    {
        if (!outFile)
        {
            std::cerr << "\nNie mozna otworzyc pliku do zapisu!" << std::endl;
            return;
        }

        for (const auto& student : baza)
        {
            student.saveToFile(outFile);
        }
        std::cout << "\nBaza zostala zapisana!\n";
        outFile.close();
    }   
}

std::vector<Student> wczytajBaze(const std::string& nazwa_pliku)
{
    std::vector<Student> baza;
    std::ifstream inFile("bazy/" + nazwa_pliku);

    if (!inFile)
    {
        std::cerr << "\nNie mozna otworzyc pliku do odczytu!" << std::endl;
        return baza;
    }

    Student student;
    while (inFile >> student.imie >> student.nazwisko >> student.numerIndeksu >> student.ocenaKoncowa >> student.pesel >> student.data_urodzenia >> student.data_rozpoczecia >> student.data_zakonczenia)
    {
        baza.push_back(student);
    }
    inFile.close();
    std::cout << "\nBaza zostala wczytana!\n";
    return baza;
}

std::string nazwaBazy()
{
    std::string nazwa_bazy;
    std::cout << "\nPodaj nazwe bazy: "; 
    std::cin >> nazwa_bazy;

    return nazwa_bazy + ".txt";
}

int pobierzLiczbe() 
{
    int wybor;
    while (!(std::cin >> wybor)) 
    {
        std::cerr << "\nNieprawidlowy wybor. Podaj liczbe: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return wybor;
}

void infoStudent(std::vector<Student>& baza)
{
    bool found = false;

    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
    }

    else
    {
        int numerIndeksu;
        std::cout << "\nPodaj numer indeksu studenta: ";
        std::cin >> numerIndeksu;

        for (auto& student : baza)
        {
            if (student.numerIndeksu == numerIndeksu)
            {
                found = true;
                std::cout << "\n-------------------------------------------------------------\n";
                std::cout << std::setw(25) << "Imie: " << std::setw(15) << student.imie << std::endl
                    << std::setw(25) << "Nazwisko: " << std::setw(15) << student.nazwisko << std::endl
                    << std::setw(25) << "Pesel: " << std::setw(15) << std::fixed << std::setprecision(0) << student.pesel << std::endl
                    << std::setw(25) << "Data urodzenia: " << std::setw(15) << student.data_urodzenia << std::endl
                    << std::setw(25) << "Data rozpoczecia: " << std::setw(15) << student.data_rozpoczecia << std::endl
                    << std::setw(25) << "Data zakonczenia: " << std::setw(15) << student.data_zakonczenia << std::endl;
            }
        }
    
        if (!found)
        {
            std::cerr << "\nBrak studenta w bazie!" << std::endl;
        }
    }
}

void zmienInfoStudent(std::vector<Student>& baza)
{
    if (baza.empty())
    {
        std::cout << "\nBaza danych jest pusta!\n";
    }

    int numerIndeksu;
    std::cout << "\nPodaj numer indeksu studenta do zmiany oceny: ";
    std::cin >> numerIndeksu;

    for (auto& student : baza)
    {
        if (student.numerIndeksu == numerIndeksu)
        {
            std::cout << "Aktualne dane studenta " << student.pesel << " " << student.data_urodzenia << " " << student.data_rozpoczecia << " " << student.data_zakonczenia << std::endl;
            std::cout << "Podaj nowy pesel: ";
            std::cin >> student.pesel;
            std::cout << "Podaj nowa date urodzenia studenta: ";
            std::cin >> student.data_urodzenia;
            std::cout << "Podaj nowa date rozpoczecia studiow: ";
            std::cin >> student.data_rozpoczecia;
            std::cout << "Podaj nowa przewidywana date ukonczenia studiow: ";
            std::cin >> student.data_zakonczenia;
        }
    }
}

void mainMenu(std::vector<Student>& bazaStudentow)
{
    int wybor;
    
    do
    {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Student\n";
        std::cout << "2. Baza\n";
        std::cout << "3. Informacje o studencie\n";
        std::cout << "4. Wyjscie\n";
        std::cout << "Wybierz opcje: ";
        wybor = pobierzLiczbe();

        switch (wybor)
        {
        case 1:
            system("cls");
            studentMenu(bazaStudentow);
            break;
        case 2:
            system("cls");
            bazaMenu(bazaStudentow);
            break;
        case 3:
            system("cls");
            infoStudentMenu(bazaStudentow);
            break;
        case 4:
            system("cls");
            std::cout << "Koniec programu.\n";
            system("close");
            break;
        default:
            system("cls");
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            break;
        }
    } while (wybor != 4);
}

void studentMenu(std::vector<Student>& bazaStudentow)
{
    int wybor;

    std::cout << "\n--- MENU STUDENT ---\n";
    std::cout << "1. Dodaj studenta\n";
    std::cout << "2. Wyswietl studentow\n";
    std::cout << "3. Usun studenta\n";
    std::cout << "4. Zmien ocene\n";
    std::cout << "5. Znajdz\n";
    std::cout << "6. Powrot\n";
    std::cout << "Wybierz opcje: ";
    wybor = pobierzLiczbe();

    switch (wybor)
    {
    case 1:
        system("cls");
        dodajStudenta(bazaStudentow);
        studentMenu(bazaStudentow);
        break;
    case 2:
        system("cls");
        wyswietlStudentow(bazaStudentow);
        studentMenu(bazaStudentow);
        break;
    case 3:
        system("cls");
        usunStudenta(bazaStudentow);
        studentMenu(bazaStudentow);
        break;
    case 4:
        system("cls");
        zmianaStudent(bazaStudentow);
        studentMenu(bazaStudentow);
        break;
    case 5:
        system("cls");
        znajdzStudent(bazaStudentow);
        studentMenu(bazaStudentow);
        break;
    case 6:
        system("cls");
        mainMenu(bazaStudentow);
        studentMenu(bazaStudentow);
    default:
        system("cls");
        std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        studentMenu(bazaStudentow);
        break;
    }
}

void bazaMenu(std::vector<Student>& bazaStudentow)
{
    int wybor;

    std::cout << "\n--- MENU BAZA ---\n";
    std::cout << "1. Lista baz\n";
    std::cout << "2. Zapisz baze do pliku\n";
    std::cout << "3. Wczytaj baze z pliku\n";
    std::cout << "4. Powrot\n";
    std::cout << "Wybierz opcje: ";
    wybor = pobierzLiczbe();

    switch (wybor)
    {
    case 1:
        system("cls");
        jakieBazy();
        bazaMenu(bazaStudentow);
        break;
    case 2:
        system("cls");
        zapiszBaze(bazaStudentow, nazwaBazy());
        bazaMenu(bazaStudentow);
        break;
    case 3:
        system("cls");
        bazaStudentow = wczytajBaze(nazwaBazy());
        bazaMenu(bazaStudentow);
        break;
    case 4:
        system("cls");
        mainMenu(bazaStudentow);
    default:
        system("cls");
        std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        bazaMenu(bazaStudentow);
        break;
    }
}

void infoStudentMenu(std::vector<Student>& bazaStudentow)
{
    int wybor;

    std::cout << "\n--- MENU INFORMACJE O STUDENCIE ---\n";
    std::cout << "1. Info\n";
    std::cout << "2. Powrot\n";
    std::cout << "Wybierz opcje: ";
    wybor = pobierzLiczbe();

    switch (wybor)
    {
    case 1:
        system("cls");
        infoStudent(bazaStudentow);
        break;
    case 2:
        system("cls");
        mainMenu(bazaStudentow);
    default:
        system("cls");
        std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        infoStudentMenu(bazaStudentow);
        break;
    }
}

int main()
{
    std::vector<Student> bazaStudentow;
    int wybor;

    mainMenu(bazaStudentow);

    return 0;
}