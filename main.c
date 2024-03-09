#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

//Text to be decrypted:
//Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.


void getDistributionArr(double distr_arr[]){
    FILE* file = fopen("/Users/razvanbocra/CLionProjects/Lab2 Extra -OOP/distribution.txt", "r");
    char line[10];
    for(int i = 0; i < 26; i++){
        fgets(line, sizeof(line), file);
        distr_arr[i] = atof(line);
    }
    fclose(file);
}

void computeNormalisedFreq(char text[], double letter_freq[]){
    int i = 0;
    char copy_text[1000];
    strcpy(copy_text, text);
    while (copy_text[i] != '\0'){
        copy_text[i] = tolower(copy_text[i]);
        if(!strchr(" .,?!", copy_text[i]))
            letter_freq[copy_text[i]-97]++;
        i++;

    }

}

double computeChiDist(double distr_arr[], double letter_freq[]){
    double chi_dist = 0;
    for(int i = 0; i < 26; i++){
        chi_dist += ((distr_arr[i] - letter_freq[i]) * (distr_arr[i] - letter_freq[i]) / distr_arr[i]);
    }
    return chi_dist;
}

void encryptText(char text[], int key){
    char temp_text[strlen(text)];
    for (int i = 0; i < strlen(text); i++){
        if(!strchr(" .?!,\n", text[i])){
            if(isupper(text[i]))
                temp_text[i] = (text[i] - 'A' + key) % 26 + 'A';
            else
                temp_text[i] = (text[i] - 'a' + key) % 26 + 'a';
        }
        else if(text[i]!='\n')
            temp_text[i] = text[i];
    }
    strcpy(text, temp_text);
}

void solveCypher(char text[], int size_of_text, char decrypted_text[]){
    int key;
    double letter_freq[27]={} ,min_chi_dist, distr_arr[27];
    char new_array[size_of_text+2];
    getDistributionArr(distr_arr);
    computeNormalisedFreq(text, letter_freq);
    min_chi_dist = computeChiDist(distr_arr, letter_freq);
    for(key = 1; key <= 26; key++){
        strcpy(new_array, text);
        encryptText(new_array, key);
        double new_letter_freq[27] = {};
        computeNormalisedFreq(new_array, new_letter_freq);
        double chi_dist = computeChiDist(distr_arr, new_letter_freq);
        if(chi_dist < min_chi_dist){
            min_chi_dist = chi_dist;
            strcpy(decrypted_text, new_array);
        }
    }
}


void displayMenu(){
    printf("\nPlease select an option:\n");
    printf("1. Encrypt text using Caesar's Cypher\n");
    printf("2. Break Caesar's Cypher using frequency analysis\n");
    printf("3. Exit\n");
}


void displayString(char text[]){
    for (int i=0; i < strlen(text); i++)
        printf("%c", text[i]);
}


int main() {
    char text[1001], decrypted_text[1001];
    printf("Caesar's Cypher Frequency Analysis Decryptor\nAuthor: Razvan-Andrei Bocra\n------------------------------\n");
    int option = 0, key;
    do {
        displayMenu();
        scanf("%d", &option);
        getchar(); // Consume the newline character (this line helps us use scanf together with fgets)
        switch (option) {
            case 1:
                printf("\nGive the message:\n");
                fgets(text, 1000, stdin);
                printf("\nGive key:\n");
                scanf("%d", &key);
                getchar(); // Consume the newline character
                encryptText(text, key);
                displayString(text);
                break;
            case 2:
                printf("\nGive the message:\n");
//                getchar(); // Consume the newline character
                fgets(text, 1000, stdin);
                solveCypher(text, strlen(text), decrypted_text);
                displayString(decrypted_text);
                break;
            case 3:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid option!\n");
        }
    } while (option != 3);

    return 0;
}
