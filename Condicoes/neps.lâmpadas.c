#include <stdio.h>
#include <stdbool.h>

int main(){
    bool a=false, b=false;
    int n=0;
    int numA=0, numB=0;

    scanf("%i", &n);
    int v[n];
    if(n>1 && n<100001){
        for(int i=0; i<n; i++){
            scanf("%i", &v[i]);
        }
        
        for(int i=0; i<n; i++){
            //
            if(v[i] == 1){
                if(a){
                    a=false;
                }
                else{
                    a=true;
                }

            }
            //
            else if(v[i] == 2){
                if(a){
                    a=false;
                }
                else{
                    a=true;
                }

                if(b){
                    b=false;
                }
                else{
                    b=true;
                }
            }
        }

        if(a){
            numA=1;
        }
        else{
            numA=0;
        }

        if(b){
            numB=1;
        }
        else{
            numB=0;
        }


        printf("%i\n%i", numA, numB);
    }
    


    return 0;
}