#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <math.h>

class Sieve {
private:
    std::set<int> s;
    int setRange;

public:
// Konstruktor, generuje zbiór <2, range>, następnie odsiewa z niego l. pierwsze
// Usuwa ze zbioru kolejne wielokrotności początkowych liczb pierwszych
    Sieve(int range) {
        setRange = range + 1;
        fill(range);
        std::set<int>::iterator iter;
        iter = s.begin();
        std::cout << "SIEVE: filtering..." << std::endl;
        while (*iter < int(sqrt(setRange))) {
            filter(*iter);
            iter++;
        }
        std::cout << "SIEVE: done! length: " << Size() << std::endl;
    }

// ładne wypisanie wyniku
    void Print() {
        for (int n : s) {
            std::cout << n << std::endl;
        }
    }

// zapisuje wynik do './path'
    void SaveToFile(std::string path) {
        std::cout << "SIEVE: saving to "<< path << std::endl;
        std::fstream strm;
        strm.open(path, std::ios_base::out);
        if (strm.is_open()) {
            std::string str = "";
            for (int n : s) {
                str += std::to_string(n) + ";";
            }
            strm << str;
            std::cout << "SIEVE: saved!" << std::endl;
            strm.close();
            if (strm.is_open())
                std::cout << "SIEVE: Stream could not close!" << std::endl;
        }
        else
            std::cout << "SIEVE: File could not be opened!" << std::endl;
    }

// zwraca ilość 'odsianych' liczb pierwszych
    int Size() {
        return s.size();
    }

// zwraca 'odsiane' liczby pierwsze
    std::set<int> GetGeneratedPrimes() {
        return s;
    }

private:
// wypełnianie początkowego zbioru <2, n> kolejnymi liczbami całkowitymi
    void fill(int n) {
        std::cout << "SIEVE: generating set <2, " << n << ">" << std::endl;
        for (int i = 2; i < n + 1; i++) {
            s.insert(i);
        }
        std::cout << "SIEVE: generated!" << std::endl;
    }

// filtrowanie zbioru poprzez usuwanie kolejnych wielokrotności n
    void filter(int n) {
        for (int i = n + n; i < setRange; i += n) {
            s.erase(i);
        }
    }

// sprawdzanie czy liczba jest pierwsza, f. statyczna, wyżej nie używana,
// jednak może się przydać czasami
    static bool isPrime(int n) {
        if (n == 2) {
            return true;
        }
        if (n < 2 || n == 4) {
            return false;
        }
        for (int i = 2; i < n/2; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
};


int main() {

    Sieve s(9000); // Tworzy obiekt klasy Sieve, zawierał on będzie
                   // wszystkie liczby pierwsze odsiane z <2, 9000>
    s.Print(); // Wypisanie odsianych liczb pierwszych
    std::cout << s.Size() << std::endl; // Ilosc l. pierwszych

    // Zapisanie wygenerowanych l. pierwszych w lokalnej zmiennej primes
    std::set<int> primes = s.GetGeneratedPrimes();


    // s.SaveToFile("primes.txt");

    return 0;
}
