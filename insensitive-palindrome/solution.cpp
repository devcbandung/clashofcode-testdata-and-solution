#include <bits/stdc++.h>
using namespace std;

// Program kita akan tetap benar jika kita menggunakan toLowerCase
char toUpperCase(char c) {
  // Jika c sudah upper-case, maka tidak perlu ubah apa-apa
  if ('A' <= c && c <= 'Z') {
    return c;
  }
  // Jika c bukan upper-case, maka asumsikan c adalah lower-case.
  // Kita dapat mengubah c menjadi upper-case dengan perhitungan sederhana.
  // c - 'a' menyatakan huruf ke berapa c, jika 'a' dihitung 0 dan 'z' dihitung 25.
  // maka, menambahkan nilai ini dengan 'A' akan menghasilkan huruf yang sama tapi dalam case yang berbeda.
  return c - 'a' + 'A';
}

int main() {
  string s;
  cin >> s;

  int n = s.length();
  bool isPalindrome = true;
  bool isSensitive = true;

  // iterasi dari kiri dan kanan secara simultan.
  // pada tiap iterasi, increment indeks di kiri dan decrement indeks di kanan.
  for (int l = 0, r = n-1; l < r; l++, r--) {
    // pertama-tama, bandingkan secara case-insenstive.
    if (toUpperCase(s[l]) != toUpperCase(s[r])) {
      isPalindrome = false;
      isSensitive = false;
      break;
    }
    // kemudian, baru bandingkan secara case-sensitive.
    if (s[l] != s[r]) {
      isSensitive = false;
      break;
    }
  }

  if (isPalindrome && isSensitive) {
    cout << "sensitive palindrome" << endl;
  } else if (isPalindrome) {
    cout << "insensitive palindrome" << endl;
  } else {
    cout << "not a palindrome" << endl;
  }
}