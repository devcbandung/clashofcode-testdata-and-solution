#include <iostream>
using namespace std;

int main() {
    int x, panjang,lebar, i, j, k, l;
    int star = 1;
    cin >> x;
    cin >> lebar >> panjang;

    if(x > 0 && panjang > 0 && lebar > 0){
        for(i = 0;i < lebar; i++){
            for(j = 0;j < x; j++){
                if(star == 1){
                    for(k = 0;k < panjang; k++){
                        if(k%2 == 0){
                            for(l = 0;l < x;l++){
                                cout << "*";
                            }
                        }else{
                            for(l = 0;l < x;l++){
                                cout << " ";    
                            }
                        }
                    }
                    cout << endl;
                }else{
                    for(k = 0;k < panjang; k++){
                        if(k%2 == 0){
                            for(l = 0;l < x;l++){
                                cout << " ";
                            }
                        }else{
                            for(l = 0;l < x;l++){
                                cout << "*";    
                            }
                        }
                    }
                    cout << endl;
                }        
            }
            
            if(star == 1){
                star = 0;
            }else{
                star = 1;
            }
        }
    }

    return 0;
}