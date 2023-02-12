#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_OF_PLAYERS 100

/* defining global variables
 N  - number of teams
 M  - number of teams
 k_super - counter for Super players

 */
int N;
int M;
int k_super = 0;
int actions_counter;

// Struct for Player
typedef struct p {
    char name[50];
    int team_number, power, visibility, is_valid;
} Player;


// Array of Players
Player ListOfPlayers[MAX_NUM_OF_PLAYERS * 2];


/**
 * function checking names of wizards and players
 */
int is_name_valid(char name[]) {
    if (!isupper(name[0])) {
        return 0;
    }
    for (int j = 1; j < strlen(name) - 1; j++) {
        if (!isalpha(name[j])) {
            return 0;
        }
    }
    return 1;
}

int min(int a, int b){
    return a > b ? b : a;
}

/**
 * function implementation of Attack
 * @param p1 Attacker
 * @param p2 Defender
 */
void attack(Player *p1, Player *p2) {
    int pl1 = p1->power;
    int pl2 = p2->power;
    if (pl1 > pl2) {
        int diff = pl1 - pl2;
        pl1 = min(pl1 + diff, 1000);
        pl2 = 0;
    } else if (pl1 < pl2) {
        int diff = pl2 - pl1;
        pl2 = min(pl2 + diff, 1000);
        pl1 = 0;
    } else if (pl1 == pl2) {
        pl1 = 0;
        pl2 = 0;
    }
    p1->power = pl1;
    p2->power = pl2;
}

/**
 * function implementation of flip_visibility action
 * @param p1 First player
 */
void flip_visibility(Player *p1) {
    p1->visibility = !p1->visibility;
}

/**
 * function implementation of heal action
 * @param p1 First player - healer
 * @param p2 Second player - who gets healed
 */
void heal(Player *p1, Player *p2) {
    p2->power = min((p1->power + 1) / 2 + p2->power, 1000);
    p1->power = (p1->power + 1) / 2;
}

/**
 * function implementation of Super player creation
 * @param p1 First player
 * @param p2 Second player
 * @param super Super player to be created
 */
void super(Player *p1, Player *p2, Player *super) {
    super->power = min(p1->power + p2->power, 1000);
    super->team_number = p1->team_number;
    super->visibility = 1;
    super->is_valid = 1;

    p1->is_valid = 0;
    p2->is_valid = 0;
}

/**
 * function checking if player exists
 * @param name Name of player
 * @return index
 */
int return_player_index(char name[]) {
    for (int i = 0; i < M + k_super; i++){
        if (strcmp(name, ListOfPlayers[i].name) == 0) {
            return i;
        }
    }
    return -100;
}

/**
 * function giving error to the output file
 * @param fo Output file
 */
void print_error(FILE *fo) {
    fclose(fo);
    FILE *outfile = fopen("output.txt", "w");
    fprintf(outfile, "%s", "Invalid inputs\n");
    fclose(outfile);
}

/**
 * function checking whether string contains only digits
 * @param s Input string
 * @return boolean value
 */
int is_number(char s[]){
    for (int i = 0; i < strlen(s) - 1; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    //opening files
    FILE *infile = fopen("input.txt", "r");
    FILE *outfile = fopen("output.txt", "w");

    char Num[100];

    //getting number of wizards from the input
    fgets(Num, 100, infile);

    //checking if it satisfies conditions
    if (!is_number(Num)){
        print_error(outfile);
    }
    N = atoi(Num);
    if (N < 1 || N > 10) {
        print_error(outfile);
        return 0;
    }

    //Array for the wizards
    char wizards[N][100];

    /*for loop to get wizards from the input +
     * check whether wizards_names satisfy conditions
     */
    for (int i = 0; i < N; i++) {
        fgets(wizards[i], 100, infile);
        int L = strlen(wizards[i]) - 1;
        if (L < 1 || L > 20) {
            print_error(outfile);
            return 0;
        }
        if (is_name_valid(wizards[i]) == 0) {
            print_error(outfile);
            return 0;
        }
    }

    char num_of_players[100];

    //getting number of players
    fgets(num_of_players, 100, infile);
    if (!is_number(num_of_players)){
        print_error(outfile);
    }
    M = atoi(num_of_players);

    // checking if number of players is within boundaries
    if (M < N || M > 100) {
        print_error(outfile);
        return 0;
    }

    //reading players from the input
    for (int k = 0; k < M; k++) {
        //fields for players qualities
        char name[100];
        char team[100];
        char power[100];
        char v[100];

        /*  setting initial state for players
         *  is_valid - flag identifying if player exists
        */
        ListOfPlayers[k].is_valid = 1;

        //getting name from the input
        fgets(name, 100, infile);
        int L = strlen(name) - 1;
        if  (L > 20 || L <= 1) {
            print_error(outfile);
            return 0;
        }
        strcpy(ListOfPlayers[k].name, name);
        if (is_name_valid(ListOfPlayers[k].name) == 0) {
            print_error(outfile);
            return 0;
        }

        //getting team number from the input
        fgets(team, 100, infile);
        if (!is_number(team)){
            print_error(outfile);
        }
        ListOfPlayers[k].team_number = atoi(team);
        if (ListOfPlayers[k].team_number >= N || ListOfPlayers[k].team_number < 0) {
            print_error(outfile);
            return 0;
        }

        //getting power from the input
        fgets(power, 100, infile);
        if (!is_number(power)){
            print_error(outfile);
        }
        ListOfPlayers[k].power = atoi(power);
        if (ListOfPlayers[k].power < 0 || ListOfPlayers[k].power > 1000) {
            print_error(outfile);
            return 0;
        }

        //getting visibility of the player
        fgets(v, 100, infile);
        if (strcmp(v, "True\n") == 0) {
            ListOfPlayers[k].visibility = 1;
        } else if (strcmp(v, "False\n") == 0) {
            ListOfPlayers[k].visibility = 0;
        } else {
            print_error(outfile);
            return 0;
        }
    }

    //variables for reading actions from the input
    char string[100];
    char player1[50];
    char player2[50];
    char action[50];

    /**
     * while loop for actions
     */
    while (fgets(string, 100, infile) != NULL) {
        //reading a string with action
        sscanf(string, "%s", action);

        //if the action equals to attack
        if (strcmp(action, "attack") == 0) {
            //splitting string by words to separate action and players
            sscanf(string, "%s %s %s", action, player1, player2);
            strcat(player1, "\n");
            strcat(player2, "\n");

            //returns error if player does not exist
            if (return_player_index(player1) == -100 || return_player_index(player2) == -100) {
                print_error(outfile);
                return 0;
            }

            Player *p1 = &ListOfPlayers[return_player_index(player1)];
            Player *p2 = &ListOfPlayers[return_player_index(player2)];

            //checking whether the action is invalid
            if (p1->visibility == 0) {
                fprintf(outfile, "%s\n", "This player can't play");
            } else if(p1->power == 0) {
                fprintf(outfile, "%s\n", "This player is frozen");
            //otherwise doing the action
            } else if (p2->visibility == 1) {
                attack(p1, p2);
            } else {p1->power = 0;}


        //if the action equals to flip_visibility
        } else if (strcmp(action, "flip_visibility") == 0) {
            //splitting strings by words to separate action and players
            sscanf(string, "%s %s %s", action, player1, player2);
            strcat(player1, "\n");
            int index = return_player_index(player1);

            //returns error if player does not exist
            if (index == -100) {
                print_error(outfile);
                return 0;

            //checking whether the action is invalid
            } else if (ListOfPlayers[index].power == 0) {
                fprintf(outfile, "%s\n", "This player is frozen");
            //otherwise doing the action
            } else { flip_visibility(&ListOfPlayers[index]);}


        //if the action equals to heal
        } else if (strcmp(action, "heal") == 0) {
            sscanf(string, "%s %s %s", action, player1, player2);
            strcat(player1, "\n");
            strcat(player2, "\n");
            int index1 = return_player_index(player1);
            int index2 = return_player_index(player2);

            //returns error if player does not exist
            if (index1 == -100 || index2 == -100) {
                print_error(outfile);
                return 0;

            //checking whether the action is invalid
            } else if (ListOfPlayers[index1].visibility == 0) {
                fprintf(outfile, "%s\n", "This player can't play");
            } else if (ListOfPlayers[index1].power == 0){
                fprintf(outfile, "%s\n", "This player is frozen");
            } else if(ListOfPlayers[index1].team_number != ListOfPlayers[index2].team_number) {
                fprintf(outfile, "%s\n", "Both players should be from the same team");
            } else if (strcmp(ListOfPlayers[index1].name, ListOfPlayers[index2].name) == 0){
                fprintf(outfile, "%s\n", "The player cannot heal itself");
            }
            //otherwise doing the action
            else if (ListOfPlayers[index1].team_number == ListOfPlayers[index2].team_number) {
                heal(&ListOfPlayers[index1], &ListOfPlayers[index2]);
            }


        //if the action equals to super_player creation
        } else if (strcmp(action, "super") == 0) {
            sscanf(string, "%s %s %s", action, player1, player2);
            strcat(player1, "\n");
            strcat(player2, "\n");
            int index1 = return_player_index(player1);
            int index2 = return_player_index(player2);

            //returns error if the player does not exist
            if (index1 == -100 || index2 == -100) {
                print_error(outfile);
                return 0;
            //checking whether the action is invalid
            } else if (ListOfPlayers[index1].visibility == 0) {
                fprintf(outfile, "%s\n", "This player can't play");
            } else if (ListOfPlayers[index1].power == 0) {
                fprintf(outfile, "%s\n", "This player is frozen");
            } else if(ListOfPlayers[index1].team_number != ListOfPlayers[index2].team_number) {
                fprintf(outfile, "%s\n", "Both players should be from the same team");
            } else if (index1 == index2) {
                fprintf(outfile, "%s\n", "The player cannot super action with itself");
            //otherwise doing the action
            } else if (ListOfPlayers[index1].team_number == ListOfPlayers[index2].team_number) {
                //creating name of the Super_player in the format "S_ "
                char super_name[5] = "S_";
                char k[3];
                sprintf(k, "%d", k_super);
                strcat(super_name, k);
                strcat(super_name, "\n");
                k_super += 1;

                //defining new_index for super_player
                int new_ind = M + k_super - 1;
                strcpy(ListOfPlayers[new_ind].name, super_name);
                //doing action of creating super_player
                super(&ListOfPlayers[index1], &ListOfPlayers[index2], &ListOfPlayers[new_ind]);
            }
        //if action does not match all of the above, returns error
        } else {
            print_error(outfile);
            return 0;
        }
        //increasing counter for actions
        actions_counter += 1;
    }
    if (actions_counter > 1000) {
        print_error(outfile);
        return 0;
    }

    //creating array for final points
    int final_points[N];
    for (int i = 0; i < N; i++) {
        final_points[i] = 0;
    }
    //adding values of power from existing players to an array
    for (int s = 0; s < M + k_super; s++) {
        if (ListOfPlayers[s].is_valid == 1) {
            final_points[ListOfPlayers[s].team_number] += ListOfPlayers[s].power;
        }
    }

    //calculating final results of the match
    int ind_of_winner;
    int max = 0;
    for (int s = 0; s < N; s++) {
        if (final_points[s] > max) {
            max = final_points[s];
            final_points[s] = 0;
            ind_of_winner = s;
        }
    }
    //checking a tie condition
    for (int s = 0; s < N; s++) {
        if (final_points[s] == max) {
            fprintf(outfile, "%s\n","It's a tie");
            return 0;
        }
    }
    //printing final winner
    fprintf(outfile, "The chosen wizard is %s", wizards[ind_of_winner]);

    //closing files
    fclose(infile);
    fclose(infile);
    return 0;
}