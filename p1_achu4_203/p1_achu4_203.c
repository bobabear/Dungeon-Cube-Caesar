/*
<Amanda Chu and G01381239>
CS262, Lab Section203
<P1: A two-player game that randomly generates a 5 letter word 
and the number of sides for the 2 dices.> 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

//Macros
#define WORD_LENGTH 5 //length of the word
#define NAME_LENGTH 8 //length of the name

//Function Prototypes
int valid_seed(char *input);
void generate_word(char *word);
void updateString(char *word, char *updatedWord, int index);
int roll_dice(int sides);
void removeWhitespace(char *input, char *output);
int validate_sides(char *output, int *side1, int *side2);
int validate_player_name(char *name);
void ciphers(char *word, int shift);

int main(){
    char input[20]; //buffer for user input
    char output[20]; //buffer for output string
    char word[WORD_LENGTH + 1]; //buffer for 5 letter word
    char updatedWord[WORD_LENGTH + 1]; //updated word
    char name[100]; //buffer for name
    char player2[] = "Bob"; //player 2 name
    int seed = 0; //seed 
    int sides = 0; //number of sides
    int side1 = 0; //side1
    int side2 = 0; //side2
    int player1sum = 0; //sum of player1
    int player2sum = 0; //sum of player2
    int shift = 0; //shift

    //Introduce the game
    printf("Welcome to DungeonCubeCaesar!\n");
    printf("This game is a two-player game that randomly generates a 5 letter word");
    printf(" and the number of sides for the 2 dices.\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    do {
        //Prompts the user to enter the seed of the game
        printf("Enter the seed for the game [1-9999]: ");
        fgets(input, 20, stdin);

        //Checks if the input is a valid seed
        if (!valid_seed(input)) {
            printf("Invalid seed!\n");
        }
      //Stops if valid_seed(input) is invalid
    } while (!valid_seed(input));

    //Convert the validated input to integer
    seed = atoi(input);
    //Set the seed for random number generation
    srand(seed);
    printf("The seed for the game is %d.\n", seed);

    //Generate a 5 letter word
    generate_word(word);

    do {
        //Prompt the user to enter their name
        printf("Enter your name [2-8 charcters]: ");
        fgets(name, 100, stdin);
        //Checks if the name is valid
        if (!validate_player_name(name)) {
            printf("Invalid name!\n");
        }
    } while (!validate_player_name(name));

    printf("Welcome %s!\n", name);      

    do {
        //Prompts the user to enter the sides of 2 dices
        printf("Enter the sides of the 2 dice [3x3 or 2x 5 or 1    x4 or 5  x  5 ]: ");
        fgets(input, 20, stdin);
        //Removes whitespaces if any
        removeWhitespace(input, output);
        //Checks if the sides are valid
        if(!validate_sides(output, &side1, &side2)) {
            printf("Invalid sides!\n");
        }
    } while (!validate_sides(output, &side1, &side2));

    char player1word[6]; //the word of player1
    char player2word[6]; //the word of player2
    int player1index = 0; //player1 index
    int player2index = 0; //player2 index
    int max = side1 + side2; //maximum of both sides added
    int rounds = 1; //round incrementation
    int player1total = 0; //total of player1
    int player2total = 0; //total of player2

    do{
        //Print round is starting
        printf("\nRound %d is starting...\n", rounds);
        //Add the sum of the roll of each dice and assign it to player1sum
        player1sum = roll_dice(side1) + roll_dice(side2);
        //Add the sum to the total of player 1
        player1total += player1sum;
        //Print player 1 is rolling dice
        printf("    %s is rolling the dice now!\n", name);

        //Add the sum of the roll of each dice and assign it to player2sum
        player2sum = roll_dice(side1) + roll_dice(side2);
        //Print player 2 is rolling dice
        player2total += player2sum;
        //Print player 2 is rolling dice
        printf("    Bob is rolling the dice now!\n");

        //Checks if the sum of player1 is greater than the sum of player2(Bob)
        if(player1sum > player2sum){
            //Update the word for player2(Bob)
            updateString(word, player2word, player2index);
            //Update player2(Bob) index
            player2index++;
        }
    
        //Checks if the sum of player2(Bob) is greater than the sum of player1
        if(player1sum < player2sum){
            //Update the word for player1
            updateString(word, player1word, player1index);
            //Update player1 index
            player1index++;
        }

        //Checks if the sum of player1 is equal to the max
        if(player1sum == max){
            //Checks player1's index is greater than 0
            if(player1index > 0){
                //Subtract player1's index
                player1index--;
                //Update the word for player1
                updateString(word, player1word, player1index);
            }
        }
        
        //Checks if the sum of player2(Bob) is equal to the max
        if(player2sum == max){
            //Checks player2's index is greater than 0
            if(player2index > 0){
                //Subtract player2's index
                player2index--;
                //Update the word for player2(Bob)
                updateString(word, player2word, player2index);
            }
        }

        //Prints the current state of the game for player1
        printf("    %s word is: %s\n", name, player1word);
        //Prints the current state of the game for player2(Bob)
        printf("    Bob word is: %s\n", player2word);
        //Updates the round
        rounds++;

    } while(player1index != (WORD_LENGTH) && player2index != (WORD_LENGTH));

    //Checks if player1 is equal to the word length
    if (player1index == WORD_LENGTH){
        //Print player1 lost
        printf("\n%s lost the game!\n", name);
        //Set shift to player1's total mod 26
        shift = player1total % 26;
        //Cipher the word
        ciphers(player1word, shift);
        //Print the encrypted word
        printf("Their encrypted word is %s\n", player1word);
    }

    //Checks if player2(Bob) is equal to the word length
    if (player2index == WORD_LENGTH){
        //Print player2(Bob) lost
        printf("\nBob lost the game!\n");
        //Set shift to player2(Bob)'s total mod 26
        shift = player2total % 26;
        //Cipher the word
        ciphers(player2word, shift);
        //Print the encrypted word
        printf("Their encrypted word is %s\n", player2word);
    }

    //Prints the game ended message
    printf("\nGame Ended!\n");
    
    return 0;
}

int valid_seed(char *input){
    //Variable for the length of the seed
    int input_len = strlen(input);

    //Loops through each digit in the input string
    for(int i = 0; i < input_len; i++){
        //Checks if the character is not a digit or newline character
        if(!isdigit(input[i]) && input[i] != '\n'){
            return 0;
        }
    }
    
    int seed = 0;
    sscanf(input, "%d", &seed);

    //Checks if the seed is within the valid range [1-9999]
    if(seed < 1 || seed > 9999){
        return 0;
    }

    return 1;
}

void generate_word(char *word){
    //Loops through each index and generates a random letter
    for(int i = 0; i < WORD_LENGTH; i++){
        word[i] = 97 + (rand() % 26);
    }
    //Adds null terminator to the end of the word
    word[WORD_LENGTH] = '\0';

    //Prints the generated word
    printf("%s\n", word);
}

void updateString(char *word, char *updatedWord, int index){
    //Copies the word up to the index to the updated word
    updatedWord[index] = word[index];
    //Adds null terminator to the end of the updated word
    updatedWord[index + 1] = '\0';
}

int roll_dice(int sides){
    //Generate a random side of the dice
    int result = (rand() % sides) + 1;
    return result;
}

void removeWhitespace(char *input, char *output){
    //Variable for the index of the output string
    int j = 0;
    //Loops through each character in the input string
    for(int i = 0; i < strlen(input); i++){
        //Checks if the character is not a whitespace
        if(input[i]!= ' '){
            //Adds the character to the output string
            output[j++] = input[i];
        } 
        
    }
    //Adds null terminator to the end of the output string
    output[j] = '\0';
}

int validate_sides(char *output, int *side1, int *side2){
    //Checks all 3 statement to be true
    if((sscanf(output,"%d x %d",side1,side2) == 2) && (*side1 > 0 && *side1 <= 5) && (*side2 > 0 && *side2 <= 5)){
        return 1;
    }
    else{
        return 0;
    }
    
}

int validate_player_name(char *name){
    //Removes newline character
    name[strcspn(name, "\n")] = '\0';

    //Variable for the length of the name
    int name_len = strlen(name);

    //Checks if the name length is within range
    if(name_len < 2 || name_len > NAME_LENGTH){
        return 0;
    }

    //Loops through each letter in the name
    for(int i = 0; i < name_len - 1; i++){
        //Checks if the character is not an alphabet
        if (!isalpha(name[i])) {
            return 0;
        }
    }

    return 1;
}

void ciphers(char *word, int shift){
    //Loops through each letter in the word
    for(int i = 0; i < WORD_LENGTH; i++){
        //Shifts the letter by the given shift value
        int newletter = (word[i] - 'a') + shift;
        //New letter is lowercase and wraps it around if it goes beyond 'z'
        int wrapped_letter = newletter % 26;
        //Adds the shifted letter back to the word
        word[i] = 'a' + wrapped_letter;
    }
    
}
