#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cariModInverse(int angka, int mod) {
    angka %= mod;
    for (int i = 1; i < mod; i++) {
        if ((angka * i) % mod == 1)
            return i;
    }
    return -1;
}

int determinan2x2(vector<vector<int>> matriks) {
    return matriks[0][0] * matriks[1][1] - matriks[0][1] * matriks[1][0];
}

vector<vector<int>> inversMatriks2x2(vector<vector<int>> matriks, int mod) {
    int det = determinan2x2(matriks) % mod;
    if (det < 0) det += mod;

    int detInverse = cariModInverse(det, mod);
    if (detInverse == -1) {
        cout << "Matriks tidak memiliki invers. Operasi tidak dapat dilanjutkan.\n";
        exit(1);
    }

    vector<vector<int>> invers(2, vector<int>(2));
    invers[0][0] = (matriks[1][1] * detInverse) % mod;
    invers[0][1] = (-matriks[0][1] * detInverse) % mod;
    invers[1][0] = (-matriks[1][0] * detInverse) % mod;
    invers[1][1] = (matriks[0][0] * detInverse) % mod;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (invers[i][j] < 0) invers[i][j] += mod;
        }
    }

    return invers;
}

vector<int> enkripsi(vector<int> teks, vector<vector<int>> matriksKunci) {
    vector<int> hasil(2);
    hasil[0] = (matriksKunci[0][0] * teks[0] + matriksKunci[0][1] * teks[1]) % 26;
    hasil[1] = (matriksKunci[1][0] * teks[0] + matriksKunci[1][1] * teks[1]) % 26;
    return hasil;
}

vector<int> dekripsi(vector<int> teks, vector<vector<int>> matriksInvers) {
    vector<int> hasil(2);
    hasil[0] = (matriksInvers[0][0] * teks[0] + matriksInvers[0][1] * teks[1]) % 26;
    hasil[1] = (matriksInvers[1][0] * teks[0] + matriksInvers[1][1] * teks[1]) % 26;
    return hasil;
}

void prosesTeks(string teks, vector<vector<int>> matriksKunci, bool enkripsiMode) {
    if (teks.length() % 2 != 0) teks += 'X';

    vector<int> teksNumerik(2);
    string hasil = "";

    vector<vector<int>> matriksInvers;
    if (!enkripsiMode) {
        matriksInvers = inversMatriks2x2(matriksKunci, 26);
    }

    for (size_t i = 0; i < teks.length(); i += 2) {
        teksNumerik[0] = toupper(teks[i]) - 'A';
        teksNumerik[1] = toupper(teks[i + 1]) - 'A';

        vector<int> teksHasil;
        if (enkripsiMode) {
            teksHasil = enkripsi(teksNumerik, matriksKunci);
        } else {
            teksHasil = dekripsi(teksNumerik, matriksInvers);
        }

        hasil += (char)(teksHasil[0] + 'A');
        hasil += (char)(teksHasil[1] + 'A');
    }

    cout << (enkripsiMode ? "Hasil Enkripsi: " : "Hasil Dekripsi: ") << hasil << endl;
}

void masukkanMatriksKunci(vector<vector<int>>& matriksKunci) {
    cout << "Masukkan nilai matriks kunci (2x2):\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "Elemen [" << i << "][" << j << "]: ";
            cin >> matriksKunci[i][j];
        }
    }
}

int main() {
    vector<vector<int>> matriksKunci(2, vector<int>(2));
    bool selesai = false;
    string teks;
    int pilihan;

    masukkanMatriksKunci(matriksKunci);

    while (!selesai) {
        cout << "\nPilihan Menu:\n";
        cout << "1. Enkripsi\n2. Dekripsi\n3. Ubah Kunci\n4. Keluar\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan teks untuk dienkripsi: ";
                cin.ignore();
                getline(cin, teks);
                prosesTeks(teks, matriksKunci, true);
                break;
            case 2:
                cout << "Masukkan teks untuk didekripsi: ";
                cin.ignore();
                getline(cin, teks);
                prosesTeks(teks, matriksKunci, false);
                break;
            case 3:
                masukkanMatriksKunci(matriksKunci);
                break;
            case 4:
                selesai = true;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
