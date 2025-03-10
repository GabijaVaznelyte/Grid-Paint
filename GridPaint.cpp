#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <windowsx.h>
#include <conio.h>

using namespace std;
char Blokas = 254;
char TopLeft = 218;
char TopRight = 191;
char BotLeft = 192;
char BotRight = 217;
char VerticalLine = 179;
char HorizontalLine = 196;

struct Blokelis {
    int x, y, spalva;
};
void IsvestiSpalva(int Spalva) {
    if (Spalva == 0) {
        cout << "\033[37m" << Blokas << "\033[0m"; //balta
    }
    if (Spalva == 1) {
        cout << "\033[34m" << Blokas << "\033[0m"; //melyna
    }
    if (Spalva == 2) {
        cout << "\033[32m" << Blokas << "\033[0m"; //zalia
    }
    if (Spalva == 3) {
        cout << "\033[31m" << Blokas << "\033[0m"; //raudona
    }
    if (Spalva == 4) {
        cout << "\033[35m" << Blokas << "\033[0m"; //violetine
    }
    if (Spalva == 5) {
        cout << "\033[33m" << Blokas << "\033[0m"; //geltona
    }
}
bool SaliaBlokasSutampa(int**& map, int a, int b, Blokelis Tikrinamas) {
    if (Tikrinamas.x > 0 && map[Tikrinamas.x - 1][Tikrinamas.y] == Tikrinamas.spalva) {
        return true;
    }
    else if (Tikrinamas.x < a - 1 && map[Tikrinamas.x + 1][Tikrinamas.y] == Tikrinamas.spalva) {
        return true;
    }
    else if (Tikrinamas.y > 0 && map[Tikrinamas.x][Tikrinamas.y - 1] == Tikrinamas.spalva) {
        return true;
    }
    else if (Tikrinamas.y < b - 1 && map[Tikrinamas.x][Tikrinamas.y + 1] == Tikrinamas.spalva) {
        return true;
    }
    else return false;
}
int RastiAtstuma(int**& map, int a, int b, Blokelis Tikrinamas) {
    int minimumas = max(a, b);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (!(i==Tikrinamas.x && j==Tikrinamas.y) && map[i][j] == Tikrinamas.spalva) {
                if (i == Tikrinamas.x && abs(Tikrinamas.y - j) < minimumas) {
                    minimumas = abs(Tikrinamas.y - j);
                }
                if (j == Tikrinamas.y && abs(Tikrinamas.x - i) < minimumas) {
                    minimumas = abs(Tikrinamas.x - i);
                }
                if (i != Tikrinamas.x && j != Tikrinamas.y && max(abs(Tikrinamas.x - i), abs(Tikrinamas.y - j)) < minimumas) {
                    minimumas = max(abs(Tikrinamas.x - i), abs(Tikrinamas.y - j));
                }
            }
        }
    }
    return minimumas;
}
class Zemelapis {
private:
    int a, b, ** map, BaltiBlokeliai; 
    vector <Blokelis> RNGcoords;
    vector <int> SekantiSpalva;
public:
    Zemelapis() :a(4), b(4), BaltiBlokeliai(0) {
        map = new int* [a];
        for (int i = 0; i < a; i++) {
            map[i] = new int[b];
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                map[i][j] = 0;
            }
        }
    }
    Zemelapis(int x, int y) :a(x), b(y), BaltiBlokeliai(0) {
        map = new int* [a];
        for (int i = 0; i < a; i++) {
            map[i] = new int[b];
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                map[i][j] = 0;
            }
        }
    }
    ~Zemelapis() {}
    void SukurtiLenta() {
        bool rasta = 0;
        Blokelis temp;
        temp.x = (rand() % a);
        temp.y = (rand() % b);
        temp.spalva = 1 + (rand() % 5);
        RNGcoords.push_back(temp);
        map[temp.x][temp.y] = temp.spalva;
        while (RNGcoords.size() < (a * b / 10)) {
            bool rasta = 0;
            temp.x = (rand() % a);
            temp.y = (rand() % b);
            for (int i = 0; i < RNGcoords.size(); i++) {
                if (RNGcoords[i].x == temp.x && RNGcoords[i].y == temp.y) {
                    rasta = 1;
                }
            }
            if (!rasta) {
                temp.spalva = 1 + (rand() % 5);
                map[temp.x][temp.y] = temp.spalva;
                while (SaliaBlokasSutampa(map, a, b, temp)) {
                    temp.spalva = 1 + (rand() % 5);
                    map[temp.x][temp.y] = temp.spalva;
                }
                RNGcoords.push_back(temp);
            }
        }
        for (int i = 0; i < 5; i++) {
            SekantiSpalva.push_back(1 + (rand() % 5));
        }
    }
    void Input() {
        int x, y;
        cout << "     ";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(a + 3) });
        cin >> x >> y;
        x--; y--;
        Blokelis temp;
        temp.x = x;
        temp.y = y;
        temp.spalva = SekantiSpalva[0];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(a + 4) });
        if (x >= a || y >= b) {
            cout << endl << " Irasytos koordinates yra uz lentos ribu." << endl;
        }
        if (x < a && y < b && map[x][y] != 0) {
            cout << endl << " Vieta jau nudazyta.                     " << endl;
        }
        if (x < a && y < b && map[x][y] == 0 && SaliaBlokasSutampa(map, a, b, temp)) {
            cout << endl << " Negalima dazyti prie tos pacios spalvos." << endl;
        }
        if (x < a && y < b && map[x][y] == 0 && !SaliaBlokasSutampa(map, a, b, temp)) {
            map[temp.x][temp.y] = temp.spalva;
            SekantiSpalva.erase(SekantiSpalva.begin());
            SekantiSpalva.push_back(1 + rand() % 5);
            cout << endl << "                                         " << endl;
        }
    }
    void IsvestiMap(int x, int y) {
        IsvestiSpalva(map[x][y]);
    }
    void IsvestiSekancia(int x) {
        IsvestiSpalva(SekantiSpalva[x]);
    }
    void KiekBaltuBlokeliu() {
        int suma = 0;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                if (map[i][j] == 0) {
                    suma++;
                }
            }
        }
        BaltiBlokeliai = suma;
    }
    bool NeberaBaltuBlokeliu(){
        if (BaltiBlokeliai == 0) {
            return true;
        }
        else return false;
    }
    bool YraEjimas() {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                if (map[i][j] == 0) {
                    Blokelis temp;
                    temp.x = i;
                    temp.y = j;
                    temp.spalva = SekantiSpalva[0];
                    if (!SaliaBlokasSutampa(map, a, b, temp)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int Taskai() {
        Blokelis temp;
        int suma = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(a + 10) });
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                if (map[i][j] != 0) {
                    Blokelis temp;
                    temp.x = i;
                    temp.y = j;
                    temp.spalva = map[i][j];
                    suma += RastiAtstuma(map, a, b, temp);
                }
            }
        }
        suma -= BaltiBlokeliai;
        return suma;
    }
};
class EkranoLenta {
private:
    int a, b;
public:
    EkranoLenta():a(0), b(0){}
    EkranoLenta(int x, int y) :a(x), b(y){}
    ~EkranoLenta() {}
    int get_a() {
        return a;
    }
    int get_b() {
        return b;
    }
    void Ivesti() {
        cout << "Iveskite kokio dydzio norite lentos. Minimalus lentos dydis 4 x 4, o maksimalios lentos 25 x 25." << endl;
        cin >> a >> b;
        try {
            if (a > 25 || b > 25) {
                throw max(a,b);
            }
            if (a < 4 || b < 4) {
                throw min(a, b);
            }
            system("cls");
        }
        catch (int error) {
            cout << "Ivestas netinkamas lentos dydis. Minimalus lentos dydis 4 x 4, o maksimalios lentos 25 x 25.  ";
            exit(0);
        }
    }
    void IsvestiLenta(Zemelapis Map) {
        cout << "   ";
        for (int i = 0; i <= a + 2; i++) {
            for (int j = 0; j <= b + 1; j++) {
                if (i == 0) {
                    if (j < b && j < 10) cout << "  " << j + 1;
                    if (j < b && j >= 10) cout << " " << j + 1;
                    if (j == b) cout << endl;
                }
                if (i == 1) {
                    if (j == 0) {
                        cout << "   " << TopLeft;
                    }
                    if (j == b + 1) {
                        cout << TopRight << "\t" << TopLeft << HorizontalLine << HorizontalLine << HorizontalLine << TopRight << endl;
                    }
                    if (j > 0 && j < b + 1) {
                        cout << HorizontalLine << HorizontalLine << HorizontalLine;
                    }
                }
                if (i == a + 2) {
                    if (j == 0) {
                        cout << "   " << BotLeft;
                    }
                    if (j == b + 1) {
                        if (a == 4) {
                            cout << BotRight << "\t" << VerticalLine << " ";
                            Map.IsvestiSekancia(3);
                            cout << " " << VerticalLine << endl;
                        }
                        if (a == 5) {
                            cout << BotRight << "\t" << BotLeft << HorizontalLine << HorizontalLine << HorizontalLine << BotRight << endl;
                        }
                        if (a > 5) {
                            cout << BotRight << endl;
                        }
                    }
                    if (j > 0 && j < b + 1) {
                        cout << HorizontalLine << HorizontalLine << HorizontalLine;
                    }
                }
                if (i > 1 && i < a + 2) {
                    if (j == 0) {
                        if (i - 1 < 10) cout << " " << i - 1 << " " << VerticalLine;
                        if (i - 1 >= 10) cout << i - 1 << " " << VerticalLine;
                    }
                    if (j == b + 1) {
                        if (i == 2) {
                            cout << VerticalLine << "\t" << VerticalLine << " ";
                            Map.IsvestiSekancia(i - 2);
                            cout << " " << VerticalLine << endl;
                        }
                        if (i > 3 && i < 7) {
                            cout << VerticalLine << "\t" << VerticalLine << " ";
                            Map.IsvestiSekancia(i - 3);
                            cout << " " << VerticalLine << endl;
                        }
                        if (i == 3) {
                            cout << VerticalLine << "\t" << (char)195 << HorizontalLine << HorizontalLine << HorizontalLine << (char)180 << endl;
                        }
                        if (i == 7) {
                            cout << VerticalLine << "\t" << BotLeft << HorizontalLine << HorizontalLine << HorizontalLine << BotRight << endl;
                        }
                        if (i > 7) {
                            cout << VerticalLine << endl;
                        }
                    }
                    if (j > 0 && j < b + 1) {
                        cout << " ";
                        Map.IsvestiMap(i-2, j-1);
                        cout << " ";
                    }
                }
            }
        }
        if (a == 4) {
            for (int i = 0; i < (b * 3 + 2); i++) {
                cout << " ";
            }
            cout << "  ";
            cout << "\t" << BotLeft << HorizontalLine << HorizontalLine << HorizontalLine << BotRight << endl;
        }
    }
};
void Zaidimas() {
    EkranoLenta box;
    box.Ivesti();
    srand((unsigned)time(NULL));
    //int random = 1 + (rand() % 6);
    Zemelapis Map(box.get_a(), box.get_b());
    Map.SukurtiLenta();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    box.IsvestiLenta(Map);
    int i = 0;
    while (true) {
        Map.Input();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
        box.IsvestiLenta(Map);
        Map.KiekBaltuBlokeliu();
        if (Map.NeberaBaltuBlokeliu()) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(box.get_a() + 4) });
            cout << " Jus laimejote ir surinkote " << Map.Taskai() << " taskus." << endl;
            exit(0);
        }
        if (!Map.YraEjimas()) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(box.get_a() + 4) });
            cout << " Nebera ejimu, pralaimejote ir surinkote " << Map.Taskai() << " taskus." << endl;
            exit(0);
        }
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, short(box.get_a() + 5) });
}

int main()
{
    cout << "Sveiki atvyke i dazymo zaidima!" << endl << "Ar pirma karta zaidziate?" << endl;
    string atsakymas;
    cin >> atsakymas;
    if (atsakymas == "taip" || atsakymas == "Taip") {
        system("cls");
        cout << "Zaidimo tikslas nudazyti lenta taip, kad nesiliestu spalvos ir vienodos spalvos butu kuo toliau viena nuo kitos." << endl << endl;
        cout << "Kelios taisykles:" << endl;
        cout << "Is viso yra 6 spalvos:" << endl;
        cout << "\033[37m" << Blokas << " Balta" << endl;
        cout << "\033[34m" << Blokas << " Melyna" << endl;
        cout << "\033[32m" << Blokas << " Zalia" << endl;
        cout << "\033[31m" << Blokas << " Raudona" << endl;
        cout << "\033[35m" << Blokas << " Violetine" << endl;
        cout << "\033[33m" << Blokas << " Geltona" << "\033[0m" << endl;
        cout << "Reikia stengtis kad neliktu baltu langeliu." << endl;
        cout << "Spalvu pats negali pasirinkti! Reikia issisukti su tomis kurios duotos!" << endl;
        cout << "Negalima salia esanciu langeliu nudazyti ta pacia spalva." << endl;
        cout << "Taciau jas galima dazyti istrizai." << endl;
        cout << "Taskai skiriami uz kiekviena langeli." << endl;
        cout << "Kuo toliau vienodos spalvos yra viena nuo kitos tuo daugiau tasku galima gauti." << endl;
        cout << "Jei neliko galimu ejimu, taciau liko baltu langeliu, jie bus atimami nuo galutiniu tasku." << endl;
        cout << "Jei viena spalva yra vienintele visoje lentoje uz ja skiriama daugiausia tasku." << endl;
        cout << endl << "Jei jauties pasiruoses dar karta ivesk 'taip'" << endl;
        cin >> atsakymas;
        if (atsakymas == "taip" || atsakymas == "Taip") {
            system("cls");
            Zaidimas();
        }
        if (atsakymas == "ne" || atsakymas == "Ne") {
            cout << "Ok ;(" << endl;
            exit(0);
        }
    }
    if (atsakymas == "ne" || atsakymas == "Ne") {
        system("cls");
        Zaidimas();
    }
    if (atsakymas != "taip" && atsakymas != "Taip" && atsakymas != "ne" && atsakymas != "Ne") {
        cout << "Kita karta iveskite 'taip' arba 'ne'." << endl;
    }
}