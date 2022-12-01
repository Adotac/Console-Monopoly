#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "h_monopoly.h"

void main(void){
	srand(time(NULL));
	///Initialize
	int current_Player=1, dice = 0, mflag = TRUE;
	int rowBPos = B-3, colBPos = B-2; //The position of the GO LINE
	char board[B][B][B];

	int MX_playingPlayers = 0; //This is treated as N-1 MX players due to zero not being accounted for
	int *defeatedPlayers = (int*)calloc(MX_PLAYERS, sizeof(int)); //allocating all elements to zero
	player person[MX_PLAYERS];
	property prop[PROPSIZE];

	
	do{
		switch(Menu()){
		case 1:
			PlayerPos_Initialize(person, rowBPos, colBPos, defeatedPlayers);
			BoxNotOwnedInitialize(prop);
			MX_playingPlayers = selectHowManyPlayers() + 1; //Remember the N-1 MX players
			MainGame(person, prop, current_Player, defeatedPlayers, MX_playingPlayers, board, dice);
			mflag = TRUE;
			break;
		case 2:
			theRules();
			mflag = TRUE;
			break;
		case 0:
			mflag = FALSE;
			break;
		}
	}while(mflag == TRUE);
	

	//free the allocated array
	free(defeatedPlayers);
	exit(0);
}

