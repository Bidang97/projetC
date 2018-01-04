//
//  main.c
//  projetC
//
//  Created by Van Anh Nguyen on 04/01/2018.
//  Copyright © 2018 Van Anh Nguyen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int cao [99], n , i = 1, tong;
    while(1){
        printf("phan tu thu %d: ",i );
        scanf("%d",&cao[i]);
        if(cao[i] == 0){
            n = i - 1;
            break;
        }
        i++;
        
    }
    for(int j=1; j<= n; j++){
        tong = tong + cao[j];
    }
    printf("tong cua %d phan tu %d\n", n, tong);
    
    return 0;
}
