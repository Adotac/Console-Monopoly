#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "h_monopoly.h"
//to check of numeric input 
int isNumeric(const int* num) {
    if(  *num < 0 || *num > 9){
           return FALSE;
	}
	else{
	    return TRUE;
 	}
}
//Display status of the current player
void DisplayStatus(int dice, int current_Player, player *p, property *prB){
	
	printf("Rolled Value: %d\n", dice);
	printf("--------------------------------\n");		
	printf("Current Player:\t\tP%d", current_Player);
	printf("\nCurrent Money:\t\t%.2f", p[current_Player].money);
	printf("\nCurrent NetWorth:\t%.2f", p[current_Player].netWorth);
	printf("\nCurrent Position:\t%d", p[current_Player].currBoxId);
	printf("\nCurrent property:\t%4s\n", prB[p[current_Player].currBoxId].desc.name);
}
//Prints the current board situation
void BoardDisplay(char arr[][B][B]){

	for(int row = 0; row < B; row++){		
		printf("\t\t");
		for(int col = 0; col < B; col++){
			printf("%4s", arr[row][col]);
		}
		printf("\n");
	}
}
//Updates the board data
void BoardUpdate(char arr[][B][B], property *pr, int curr_pl){
	int bCtr = 1;
	char c_Player[5];
	char rowChar[5] = {205,205,205,205};
	char colChar[2] = {186};
	_itoa(curr_pl, c_Player, 10);
	for(int row = 0, ctr = PROPSIZE; row < B; row++){		
		for(int col = 0; col < B; col++){
			if(strcmp(arr[row][col], "P") == 0){
				strcat_s(arr[row][col], c_Player);
			}
			else if((row > 3 && row < B-4) && (col > 3 && col < B-4)){
				strcpy(arr[row][col], " ");
			}
			else if(row != 0 && row == B || row%3 == 0 && col != 0){
				strcpy(arr[row][col], rowChar);

			}
			else if(col == 0 || col == B-1 || col%3 == 0 ){
				strcpy(arr[row][col], colChar);
			}
			/////		
			else if(col%2 == 0 && (row+1)%3 == 0){			
				BoxDisplayNames(arr, row,col, ctr, &bCtr);
				BoxProperties(pr, row, col, ctr);
				ctr--;
			}
			else{
				strcpy(arr[row][col], " ");
			}		
	
		}
	
		
	}
}


void BoxProperties(property *pr, int row, int col, int ctr){
	pr[ctr].posX = row;
	pr[ctr].posY = col;
	pr[ctr].propBoxId = ctr;

	switch(ctr){
	case 1:
		pr[ctr].propertyID = GO;
		strcpy(pr[ctr].desc.name, "GO");
		break;
	case 2:
		pr[ctr].propertyID = BROWN;
		strcpy(pr[ctr].desc.name, "A2");
		
		pr[ctr].desc.rent = 2;
		pr[ctr].desc.monopolyRent = 4;

		//rent with n houses
		pr[ctr].desc.wH1 = 10;
		pr[ctr].desc.wH2 = 30;
		pr[ctr].desc.wH3 = 90;
		pr[ctr].desc.wH4 = 160;
		pr[ctr].desc.hotel = 250;

		pr[ctr].desc.price = 60;
		pr[ctr].desc.sellValue = 30;
		pr[ctr].desc.buildCost = 50;
		break;
	case 3:
		pr[ctr].propertyID = COMM_BOX;
		strcpy(pr[ctr].desc.name, "CommunityBox");
		break;
	case 4:
		pr[ctr].propertyID = BROWN;	
		strcpy(pr[ctr].desc.name, "A1");
		pr[ctr].desc.rent = 4;
		pr[ctr].desc.monopolyRent = 8;

		//rent with n houses
		pr[ctr].desc.wH1 = 20;
		pr[ctr].desc.wH2 = 60;
		pr[ctr].desc.wH3 = 180;
		pr[ctr].desc.wH4 = 320;
		pr[ctr].desc.hotel = 450;

		pr[ctr].desc.price = 60;
		pr[ctr].desc.sellValue = 30;
		pr[ctr].desc.buildCost = 50;
		break;
	case 5:
		pr[ctr].propertyID = TAX;
		strcpy(pr[ctr].desc.name, "TAX AREA");
		break;
	case 6:
		pr[ctr].propertyID = TRAIN;

		strcpy(pr[ctr].desc.name, "CabS");
		//depends the number of trains you owned
		pr[ctr].desc.rent = 25;
		pr[ctr].desc.monopolyRent = 200;
		pr[ctr].desc.price = 200;
		pr[ctr].desc.sellValue = 100;
		break;
	case 7:
		pr[ctr].propertyID = SBLUE;
		strcpy(pr[ctr].desc.name, "B3");
		pr[ctr].desc.rent = 6;
		pr[ctr].desc.monopolyRent = 12;

		//rent with n houses
		pr[ctr].desc.wH1 = 30;
		pr[ctr].desc.wH2 = 90;
		pr[ctr].desc.wH3 = 270;
		pr[ctr].desc.wH4 = 400;
		pr[ctr].desc.hotel = 550;

		pr[ctr].desc.price = 100;
		pr[ctr].desc.sellValue = 50;
		pr[ctr].desc.buildCost = 50;
		break;
	case 8:
		pr[ctr].propertyID = CHANCE;
		strcpy(pr[ctr].desc.name, "Chance Box");
		break;
	case 9:
		pr[ctr].propertyID = SBLUE;
		strcpy(pr[ctr].desc.name, "B2");
		pr[ctr].desc.rent = 6;
		pr[ctr].desc.monopolyRent = 12;

		//rent with n houses
		pr[ctr].desc.wH1 = 30;
		pr[ctr].desc.wH2 = 90;
		pr[ctr].desc.wH3 = 270;
		pr[ctr].desc.wH4 = 400;
		pr[ctr].desc.hotel = 550;

		pr[ctr].desc.price = 100;
		pr[ctr].desc.sellValue = 50;
		pr[ctr].desc.buildCost = 50;
		break;
	case 10:
		pr[ctr].propertyID = SBLUE;
		strcpy(pr[ctr].desc.name, "B1");
		pr[ctr].desc.rent = 8;
		pr[ctr].desc.monopolyRent = 16;

		//rent with n houses
		pr[ctr].desc.wH1 = 40;
		pr[ctr].desc.wH2 = 100;
		pr[ctr].desc.wH3 = 300;
		pr[ctr].desc.wH4 = 450;
		pr[ctr].desc.hotel = 600;

		pr[ctr].desc.price = 120;
		pr[ctr].desc.sellValue = 60;
		pr[ctr].desc.buildCost = 50;
		break;

	case 11:
		pr[ctr].propertyID = JAIL;
		strcpy(pr[ctr].desc.name, "JAIL");
		break;
	case 40:
		pr[ctr].propertyID = BLUE;
		strcpy(pr[ctr].desc.name, "H1");
		pr[ctr].desc.rent = 50;
		pr[ctr].desc.monopolyRent = 100;

		//rent with n houses
		pr[ctr].desc.wH1 = 200;
		pr[ctr].desc.wH2 = 600;
		pr[ctr].desc.wH3 = 1400;
		pr[ctr].desc.wH4 = 1700;
		pr[ctr].desc.hotel = 2000;

		pr[ctr].desc.price = 400;
		pr[ctr].desc.sellValue = 200;
		pr[ctr].desc.buildCost = 200;
		break;
	case 12:
		pr[ctr].propertyID = PINK;
		strcpy(pr[ctr].desc.name, "C1");
		pr[ctr].desc.rent = 10;
		pr[ctr].desc.monopolyRent = 20;

		//rent with n houses
		pr[ctr].desc.wH1 = 50;
		pr[ctr].desc.wH2 = 150;
		pr[ctr].desc.wH3 = 450;
		pr[ctr].desc.wH4 = 625;
		pr[ctr].desc.hotel = 750;

		pr[ctr].desc.price = 140;
		pr[ctr].desc.sellValue = 70;
		pr[ctr].desc.buildCost = 100;
		break;
	case 39:
		pr[ctr].propertyID = TAX;
		strcpy(pr[ctr].desc.name, "TAX AREA");
		break;
	case 13:
		pr[ctr].propertyID = COMPANY;

		strcpy(pr[ctr].desc.name, "PwrC");
		
		pr[ctr].desc.price = 150;
		//rent 4 times the dice || if 2 10x
		pr[ctr].desc.rent = 4;
		pr[ctr].desc.monopolyRent = 10;
		pr[ctr].desc.sellValue = 100;
		break;
	case 38:
		pr[ctr].propertyID = BLUE;
		strcpy(pr[ctr].desc.name, "H2");
		pr[ctr].desc.rent = 35;
		pr[ctr].desc.monopolyRent = 70;

		//rent with n houses
		pr[ctr].desc.wH1 = 175;
		pr[ctr].desc.wH2 = 500;
		pr[ctr].desc.wH3 = 1100;
		pr[ctr].desc.wH4 = 1300;
		pr[ctr].desc.hotel = 1500;

		pr[ctr].desc.price = 350;
		pr[ctr].desc.sellValue = 175;
		pr[ctr].desc.buildCost = 200;
		break;
	case 14:
		pr[ctr].propertyID = PINK;
	
		strcpy(pr[ctr].desc.name, "C2");
		pr[ctr].desc.rent = 10;
		pr[ctr].desc.monopolyRent = 20;

		//rent with n houses
		pr[ctr].desc.wH1 = 50;
		pr[ctr].desc.wH2 = 150;
		pr[ctr].desc.wH3 = 450;
		pr[ctr].desc.wH4 = 625;
		pr[ctr].desc.hotel = 750;

		pr[ctr].desc.price = 140;
		pr[ctr].desc.sellValue = 70;
		pr[ctr].desc.buildCost = 100;

		break;
	case 37:
		pr[ctr].propertyID = CHANCE;
		strcpy(pr[ctr].desc.name, "Chance Box");
		break;
	case 15:
		pr[ctr].propertyID = PINK;
	
		strcpy(pr[ctr].desc.name, "C3");
		pr[ctr].desc.rent = 12;
		pr[ctr].desc.monopolyRent = 24;

		//rent with n houses
		pr[ctr].desc.wH1 = 60;
		pr[ctr].desc.wH2 = 180;
		pr[ctr].desc.wH3 = 500;
		pr[ctr].desc.wH4 = 700;
		pr[ctr].desc.hotel = 900;

		pr[ctr].desc.price = 160;
		pr[ctr].desc.sellValue = 80;
		pr[ctr].desc.buildCost = 100;
		break;

	case 36:
		pr[ctr].propertyID = TRAIN;
		strcpy(pr[ctr].desc.name, "CabE");
		//depends the number of trains you owned
		pr[ctr].desc.rent = 25;
		pr[ctr].desc.monopolyRent = 200;
		pr[ctr].desc.price = 200;
		pr[ctr].desc.sellValue = 100;
		break;
	case 16:
		pr[ctr].propertyID = TRAIN;
		strcpy(pr[ctr].desc.name, "CabW");
		//depends the number of trains you owned
		pr[ctr].desc.rent = 25;
		pr[ctr].desc.monopolyRent = 200;
		pr[ctr].desc.price = 200;
		pr[ctr].desc.sellValue = 100;
		break;
	case 35:
		pr[ctr].propertyID = GREEN;
		strcpy(pr[ctr].desc.name, "G1");
		pr[ctr].desc.rent = 28;
		pr[ctr].desc.monopolyRent = 56;

		//rent with n houses
		pr[ctr].desc.wH1 = 150;
		pr[ctr].desc.wH2 = 450;
		pr[ctr].desc.wH3 = 1000;
		pr[ctr].desc.wH4 = 1200;
		pr[ctr].desc.hotel = 1400;

		pr[ctr].desc.price = 320;
		pr[ctr].desc.sellValue = 160;
		pr[ctr].desc.buildCost = 200;
		break;
	case 17:
		pr[ctr].propertyID = ORANGE;
		
		strcpy(pr[ctr].desc.name, "D1");
		pr[ctr].desc.rent = 14;
		pr[ctr].desc.monopolyRent = 28;

		//rent with n houses
		pr[ctr].desc.wH1 = 70;
		pr[ctr].desc.wH2 = 200;
		pr[ctr].desc.wH3 = 550;
		pr[ctr].desc.wH4 = 725;
		pr[ctr].desc.hotel = 950;

		pr[ctr].desc.price = 180;
		pr[ctr].desc.sellValue = 90;
		pr[ctr].desc.buildCost = 100;
		break;
	case 18:
		pr[ctr].propertyID = COMM_BOX;
		strcpy(pr[ctr].desc.name, "CommunityBox");
		break;
	case 34:
		pr[ctr].propertyID = COMM_BOX;
		strcpy(pr[ctr].desc.name, "CommunityBox");
		break;
	case 33:
		pr[ctr].propertyID = GREEN;
		strcpy(pr[ctr].desc.name, "G2");
		pr[ctr].desc.rent = 26;
		pr[ctr].desc.monopolyRent = 52;

		//rent with n houses
		pr[ctr].desc.wH1 = 130;
		pr[ctr].desc.wH2 = 390;
		pr[ctr].desc.wH3 = 900;
		pr[ctr].desc.wH4 = 1100;
		pr[ctr].desc.hotel = 1275;

		pr[ctr].desc.price = 300;
		pr[ctr].desc.sellValue = 150;
		pr[ctr].desc.buildCost = 200;
		break;
	case 19:
		pr[ctr].propertyID = ORANGE;
		strcpy(pr[ctr].desc.name, "D2");
		pr[ctr].desc.rent = 14;
		pr[ctr].desc.monopolyRent = 28;

		//rent with n houses
		pr[ctr].desc.wH1 = 70;
		pr[ctr].desc.wH2 = 200;
		pr[ctr].desc.wH3 = 550;
		pr[ctr].desc.wH4 = 725;
		pr[ctr].desc.hotel = 950;

		pr[ctr].desc.price = 180;
		pr[ctr].desc.sellValue = 90;
		pr[ctr].desc.buildCost = 100;
		break;
	case 32:
		pr[ctr].propertyID = GREEN;
		strcpy(pr[ctr].desc.name, "G3");
		pr[ctr].desc.rent = 26;
		pr[ctr].desc.monopolyRent = 52;

		//rent with n houses
		pr[ctr].desc.wH1 = 130;
		pr[ctr].desc.wH2 = 390;
		pr[ctr].desc.wH3 = 900;
		pr[ctr].desc.wH4 = 1100;
		pr[ctr].desc.hotel = 1275;

		pr[ctr].desc.price = 300;
		pr[ctr].desc.sellValue = 150;
		pr[ctr].desc.buildCost = 200;
		break;
	case 20:
		pr[ctr].propertyID = ORANGE;
		strcpy(pr[ctr].desc.name, "D3");
		pr[ctr].desc.rent = 16;
		pr[ctr].desc.monopolyRent = 32;

		//rent with n houses
		pr[ctr].desc.wH1 = 80;
		pr[ctr].desc.wH2 = 220;
		pr[ctr].desc.wH3 = 600;
		pr[ctr].desc.wH4 = 800;
		pr[ctr].desc.hotel = 1000;

		pr[ctr].desc.price = 200;
		pr[ctr].desc.sellValue = 100;
		pr[ctr].desc.buildCost = 100;
		break;

	case 31:
		pr[ctr].propertyID = GOTOJAIL;
		strcpy(pr[ctr].desc.name, "GOTOJAIL");
		break;
	case 30:
		pr[ctr].propertyID = YELLOW;
		strcpy(pr[ctr].desc.name, "F3");
		pr[ctr].desc.rent = 24;
		pr[ctr].desc.monopolyRent = 48;

		//rent with n houses
		pr[ctr].desc.wH1 = 120;
		pr[ctr].desc.wH2 = 360;
		pr[ctr].desc.wH3 = 850;
		pr[ctr].desc.wH4 = 1025;
		pr[ctr].desc.hotel = 1200;

		pr[ctr].desc.price = 280;
		pr[ctr].desc.sellValue = 140;
		pr[ctr].desc.buildCost = 150;
		break;
	case 29:
		pr[ctr].propertyID = COMPANY;

		strcpy(pr[ctr].desc.name, "MMWD");
		
		pr[ctr].desc.price = 150;
		//rent 4 times the dice || if 2 Utilities owned 10x
		pr[ctr].desc.rent = 4;
		pr[ctr].desc.monopolyRent = 10;
		pr[ctr].desc.sellValue = 100;
		break;
	case 28:
		pr[ctr].propertyID = YELLOW;
		strcpy(pr[ctr].desc.name, "F2");
		pr[ctr].desc.rent = 22;
		pr[ctr].desc.monopolyRent = 44;

		//rent with n houses
		pr[ctr].desc.wH1 = 110;
		pr[ctr].desc.wH2 = 330;
		pr[ctr].desc.wH3 = 800;
		pr[ctr].desc.wH4 = 975;
		pr[ctr].desc.hotel = 1150;

		pr[ctr].desc.price = 260;
		pr[ctr].desc.sellValue = 130;
		pr[ctr].desc.buildCost = 150;
		break;
	case 27:
		pr[ctr].propertyID = YELLOW;
		strcpy(pr[ctr].desc.name, "F1");
		pr[ctr].desc.rent = 22;
		pr[ctr].desc.monopolyRent = 44;

		//rent with n houses
		pr[ctr].desc.wH1 = 110;
		pr[ctr].desc.wH2 = 330;
		pr[ctr].desc.wH3 = 800;
		pr[ctr].desc.wH4 = 975;
		pr[ctr].desc.hotel = 1150;

		pr[ctr].desc.price = 260;
		pr[ctr].desc.sellValue = 130;
		pr[ctr].desc.buildCost = 150;
		break;
	case 26:
		pr[ctr].propertyID = TRAIN;
		strcpy(pr[ctr].desc.name, "CabN");
		//depends the number of trains you owned
		pr[ctr].desc.rent = 25;
		pr[ctr].desc.monopolyRent = 200;
		pr[ctr].desc.price = 200;
		pr[ctr].desc.sellValue = 100;
		break;
	case 25:
		pr[ctr].propertyID = RED;
		strcpy(pr[ctr].desc.name, "E3");
		pr[ctr].desc.rent = 20;
		pr[ctr].desc.monopolyRent = 40;

		//rent with n houses
		pr[ctr].desc.wH1 = 100;
		pr[ctr].desc.wH2 = 300;
		pr[ctr].desc.wH3 = 750;
		pr[ctr].desc.wH4 = 975;
		pr[ctr].desc.hotel = 1100;

		pr[ctr].desc.price = 240;
		pr[ctr].desc.sellValue = 120;
		pr[ctr].desc.buildCost = 150;
		break;
	case 24:
		pr[ctr].propertyID = RED;
		strcpy(pr[ctr].desc.name, "E2");
		pr[ctr].desc.rent = 18;
		pr[ctr].desc.monopolyRent = 36;

		//rent with n houses
		pr[ctr].desc.wH1 = 90;
		pr[ctr].desc.wH2 = 250;
		pr[ctr].desc.wH3 = 700;
		pr[ctr].desc.wH4 = 875;
		pr[ctr].desc.hotel = 1050;

		pr[ctr].desc.price = 220;
		pr[ctr].desc.sellValue = 110;
		pr[ctr].desc.buildCost = 150;
		break;
	case 23:
		pr[ctr].propertyID = CHANCE;
		strcpy(pr[ctr].desc.name, "Chance Box");
		break;
	case 22:
		pr[ctr].propertyID = RED;
		strcpy(pr[ctr].desc.name, "E1");
		pr[ctr].desc.rent = 18;
		pr[ctr].desc.monopolyRent = 36;

		//rent with n houses
		pr[ctr].desc.wH1 = 90;
		pr[ctr].desc.wH2 = 250;
		pr[ctr].desc.wH3 = 700;
		pr[ctr].desc.wH4 = 875;
		pr[ctr].desc.hotel = 1050;

		pr[ctr].desc.price = 220;
		pr[ctr].desc.sellValue = 110;
		pr[ctr].desc.buildCost = 150;
		break;
	case 21:
		pr[ctr].propertyID = FPARK;
		strcpy(pr[ctr].desc.name, "Free Parking");
		break;
	}

}
//Initializes the boxes at the start of the game
void BoxNotOwnedInitialize(property *prB){
	for(int i = PROPSIZE; i >= 0; i--){
		if(prB[i].propertyID >= CHANCE){
			prB[i].status = NOT_AVAILABLE;
		}
		else{
			prB[i].status = UNOWNED;
		}
	}
}
//The displayed box names
void BoxDisplayNames(char arr[][B][B], int row,int col, int ctr, int* bctr){
	char boId[5];
	
//////////////////////Messy format code :p (It's for D1, A1, F1 , G1, etc)
	switch(ctr){
	case 5:case 35:case 11:case 14:case 24:
		*bctr = 1;
		break;
	case 18:case 27:case 26:
		*bctr = 2;
		break;
	case 29:case 28:case 19:
		*bctr = 3;
		break;
	}
	itoa(*bctr, boId, 10);

/////////////////////BOXES/////////////////////////////////
	switch(ctr){
////////FACILITIES BOX || LOGISTICS 
	case 1:
		strcpy(arr[row][col], "<GO");
		break;
	case 5:
		strcpy(arr[row][col], "TAX");
		break;
	case 14:
		strcpy(arr[row][col], "LTAX");
		break;
	case 3:
	case 25:
	case 24:
		strcpy(arr[row][col], "Obox");
		break;
	case 8:
	case 38:
	case 18:
		strcpy(arr[row][col], "Cbox");
		break;
	case 15:
		strcpy(arr[row][col], "PowC");
		break;
	case 32:
		strcpy(arr[row][col], "MMWD");
		break;
///////---------------------////////
	case 40:
		strcpy(arr[row][col], "Park");
		break;
	case 11:
		strcpy(arr[row][col], "JAIL");
		break;
	case 30:
		strcpy(arr[row][col], "GOTO");
		break;

//////TRAINS - North,South,East,West
	case 6:
		strcpy(arr[row][col], "CabS");
		break;
	case 21:
		strcpy(arr[row][col], "CabW");
		break;
	case 35:
		strcpy(arr[row][col], "CabN");
		break;
	case 20:
		strcpy(arr[row][col], "CabE");
		break;
	
/////////---------------------------------////////
/////--------HOUSE PROPERTY BOXES
/////////////HORIZONTAL//////////////////
	case 2:case 4:
		*bctr += 1;
		strcpy(arr[row][col], "A-");
		strcat_s(arr[row][col], boId);
		break;
	case 7:case 9:case 10:
		*bctr += 1;
		strcpy(arr[row][col], "B-");
		strcat_s(arr[row][col], boId);
		break;
	case 39:case 37:case 36:
		*bctr += 1;
		strcpy(arr[row][col], "E-");
		strcat_s(arr[row][col], boId);
		break;
	case 34:case 33:case 31:
		*bctr += 1;
		strcpy(arr[row][col], "F-");
		strcat_s(arr[row][col], boId);
		break;
/////////////VERTICAL///////////////////////
	case 13:case 17:case 19: 	
		strcpy(arr[row][col], "C-");
		strcat_s(arr[row][col], boId);
		break;
	case 23:case 27:case 29:		
		strcpy(arr[row][col], "D-");
		strcat_s(arr[row][col], boId);
		break;	
	case 28:case 26:case 22:		
		strcpy(arr[row][col], "G-");
		strcat_s(arr[row][col], boId);
		break;
	case 16:case 12:		
		strcpy(arr[row][col], "H-");
		strcat_s(arr[row][col], boId);
		break;
	}
	
}

//random generated dice
int diceValue(void){
	int value=0;
	// range of dice 1 to 6
	value = rand() % (MX_DICE - 1 + 1) + 1;

	return value;
}

//all players initialized before the game
void PlayerPos_Initialize(player *p, int row, int col, int deadPl[]){
	float startingMoney = 1500;
	
	for(int i = 0; i < MX_PLAYERS; ++i){
		p[i].pos.row = row;
		p[i].pos.col = col;
	
		p[i].money = startingMoney;
		p[i].netWorth = p[i].money;
		p[i].currBoxId = 1;
		for(int a = 0; a < PROPSIZE; a++){
			p[i].ownedProperty[a].BoolMonopolized = FALSE;
			p[i].ownedProperty[a].pBoxId = NULL;
			p[i].ownedProperty[a].propID = Null;
			p[i].ownedProperty[a].houses = NULL;
			p[i].ownedProperty[a].hotel = NULL;
		}

		//Insert Initializer // Reset
		deadPl[i] = NULL;
	}
}

//updates the board where the player is 
void PlayerDisplay(player *p,property *prB, char arr[][B][B], int curr_player){
	//current position

	int col = p[curr_player].pos.col, row = p[curr_player].pos.row;

	strcpy(arr[row][col], "P");
}

//Calculating the movements of the player
void PlayerMove(char arr[][B][B], player *p, property *prB, int c_player, int dice){
	int totalPos = 0, moveToPos = 0;
	int currPos = p[c_player].currBoxId;
	totalPos = currPos + dice;

	strcpy(arr[ p[c_player].pos.row ][ p[c_player].pos.col ], " ");

	if(totalPos < 11){
		//bottom part	
		p[c_player].pos.row = prB[currPos].posX - 1;
		p[c_player].pos.col = prB[totalPos].posY;
		p[c_player].currBoxId = totalPos;
	}
	else if(totalPos < 21){
		//left part
		moveToPos = (totalPos * 2) - 11;
		p[c_player].pos.row = prB[moveToPos].posX - 1;
		p[c_player].pos.col = prB[moveToPos].posY;
		p[c_player].currBoxId = totalPos;
	}
	else if(totalPos < 31){
		//top part
		moveToPos = totalPos + ( (totalPos - 2) - ( (totalPos - 21) * 3) );

		p[c_player].pos.row = prB[moveToPos].posX - 1;
		p[c_player].pos.col = prB[moveToPos].posY;
		p[c_player].currBoxId = totalPos;
	}
	else if(totalPos <= 40){
		//right part
		moveToPos = 30 - (2 * (totalPos - 31) );
		p[c_player].pos.row = prB[moveToPos].posX - 1;
		p[c_player].pos.col = prB[moveToPos].posY;
		p[c_player].currBoxId = totalPos;
	}
	else{
		//If runs over the lap or GO LINE
		moveToPos = totalPos - 40;
		p[c_player].pos.row = prB[moveToPos].posX - 1;
		p[c_player].pos.col = prB[moveToPos].posY;
		p[c_player].currBoxId = moveToPos;
		p[c_player].money += 200;
		printf("\nYOU RECEIVED $200\n");
	}

	//A condition for GOTO box
	if(prB[moveToPos].propertyID == GOTOJAIL){
			moveToPos = 11;
			printf("\nYou have been moved to JAIL\n");
			p[c_player].pos.row = prB[moveToPos].posX - 1;
			p[c_player].pos.col = prB[moveToPos].posY;
			p[c_player].currBoxId = moveToPos;
		}
}

void BuyProperty(property prB[], player *p, int curr_pl){
	int currProp = p[curr_pl].currBoxId; //current property
	int prbProp = prB[currProp].propBoxId;
	float decreasedValue;
	char choice = NULL;
	if(prB[currProp].status == UNOWNED && (prB[currProp].propertyID >= BROWN && prB[currProp].propertyID <= TRAIN) ){
		printf("\nProperty: %4s", prB[currProp].desc.name);
		printf("\nPrice: \t%.2f", prB[currProp].desc.price);
		printf("\nStarting rent: \t%.2f", prB[currProp].desc.rent);
		printf("\nMonopoly rent: \t%.2f", prB[currProp].desc.monopolyRent);
		if(prB[currProp].propertyID <= BLUE){
		printf("\nRent with 1 house: \t%.2f", prB[currProp].desc.wH1);
		printf("\nRent with 2 house: \t%.2f", prB[currProp].desc.wH2);
		printf("\nRent with 3 house: \t%.2f", prB[currProp].desc.wH3);
		printf("\nRent with 4 house: \t%.2f", prB[currProp].desc.wH4);
		printf("\nRent with a Hotel: \t%.2f", prB[currProp].desc.hotel);
		}
		printf("\nMortgage Value: %.2f", prB[currProp].desc.sellValue);
		printf("\n----------------------------\nDo you want to buy this property?");
	do{
		printf("\n( [Y]es || [N]o )");
		choice = getch();
		switch(toupper(choice)){
		case 'Y':
			prB[currProp].status = OWNED;
			//check available slot
			for(int x = 0; x < PROPSIZE; x++){
				if(p[curr_pl].ownedProperty[x].pBoxId == NULL || p[curr_pl].ownedProperty[x].pBoxId == 0){
					p[curr_pl].ownedProperty[x].pBoxId = prB[currProp].propBoxId;
					p[curr_pl].ownedProperty[x].propID = prB[currProp].propertyID;
					p[curr_pl].ownedProperty[x].houses = 0;
					p[curr_pl].ownedProperty[x].hotel = 0;
					p[curr_pl].ownedProperty[x].BoolMonopolized = FALSE;
					decreasedValue = p[curr_pl].money - prB[currProp].desc.price;
					p[curr_pl].money = decreasedValue;
					break;
				}
			}
			printf("\nYou bought %4s!", prB[currProp].desc.name);
			printf("\nMoney left: %.2f", p[curr_pl].money);
			break;
		case 'N':
			//do nothing || end loop
			break;
		default:
			printf("\nKeyword out of range... try again\n");
			break;
		}
	}while(toupper(choice) != 'N' && toupper(choice) != 'Y');
	//end while
	}
}

//return a value to determine if you monopolized a property or not
int CheckIfMonopolized(player *person, PROPERTY_ID pID, int curr_pl){
	int brownCtr = 0, sblueCtr=0, pinkCtr=0, orangeCtr=0, redCtr=0, yellowCtr=0, greenCtr =0 , blueCtr = 0, utilityCtr = 0, trainCtr = 0;

	switch(pID){
	case BROWN:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				brownCtr++;
			}
		}
		if(brownCtr == 2){
			return TRUE;
		}
		break;
	case SBLUE:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				sblueCtr++;
			}
		}
		if(sblueCtr == 3){
			return TRUE;
		}
		break;
	case PINK:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				pinkCtr++;
			}
		}
		if(pinkCtr == 3){
			return TRUE;
		}
		break;
	case ORANGE:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				orangeCtr++;
			}
		}
		if(orangeCtr == 3){
			return TRUE;
		}
		break;
	case RED:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				redCtr++;
			}
		}
		if(redCtr == 3){
			return TRUE;
		}
		break;
	case YELLOW:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				yellowCtr++;
			}
		}
		if(yellowCtr == 3){
			return TRUE;
		}
		break;
	case GREEN:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				greenCtr++;
			}
		}
		if(greenCtr == 3){
			return TRUE;
		}
		break;
	case BLUE:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				blueCtr++;
			}
		}
		if(blueCtr == 2){
			return TRUE;
		}
		break;
	case COMPANY:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				utilityCtr++;
			}
		}
		if(utilityCtr == 2){
			return TRUE;
		}
		break;
	case TRAIN:
		for(int p = 0; p < PROPSIZE; p++){
			if(person[curr_pl].ownedProperty[p].propID == pID){
				trainCtr++;
			}
		}
		if(trainCtr == 4){
			return TRUE;
		}
		break;
	default:
		return FALSE;
		break;
	}
	
	return FALSE;
}

void PropertySorter(player *p, int curr_pl){
	
	ownProp minTemp;
	
	for(int i = 0; i < PROPSIZE; i++){
		minTemp = p[curr_pl].ownedProperty[i];

		if(minTemp.pBoxId == NULL){
			for(int y = i; y < PROPSIZE; y++){
				if(y != PROPSIZE-1){	
					p[curr_pl].ownedProperty[y] = p[curr_pl].ownedProperty[y+1];
							
					p[curr_pl].ownedProperty[y+1].BoolMonopolized = NULL;
					p[curr_pl].ownedProperty[y+1].propID = Null;
					p[curr_pl].ownedProperty[y+1].pBoxId = NULL;
					p[curr_pl].ownedProperty[y+1].houses = NULL;
					p[curr_pl].ownedProperty[y+1].hotel = NULL;
				}
			}
		}
		for(int x = i+1; x < PROPSIZE; x++){
			
			if( minTemp.propID > p[curr_pl].ownedProperty[x].propID && p[curr_pl].ownedProperty[x].pBoxId != NULL){
				
				p[curr_pl].ownedProperty[i] = p[curr_pl].ownedProperty[x];
				p[curr_pl].ownedProperty[x] = minTemp;
			}
		}
	}

} 

//Display owned properties
void CheckOwnedProperties(player *p, property *prB, int curr_pl){
	//PropertySorter(p, curr_pl);
	int boxId = 0;
	P_ID pID = BROWN;
	printf("\n\nOwned Properties: \n");
	for(int i = 0; i < PROPSIZE; i++){
		boxId = p[curr_pl].ownedProperty[i].pBoxId;
		if(boxId == NULL || boxId == 0){
			printf("\n--END--\n");
			break;
		}
	//assign if you have collected a set of properties
		for(pID; pID <= TRAIN; pID = P_ID(int(pID)+1) ){
			for(int a = 0; a < PROPSIZE; a++){
				if(p[curr_pl].ownedProperty[a].propID == pID){
					p[curr_pl].ownedProperty[a].BoolMonopolized = CheckIfMonopolized(p, pID, curr_pl);
				}
			}
		}

		printf("\n||Property: %4s\t", prB[boxId].desc.name);
		if(p[curr_pl].ownedProperty[i].BoolMonopolized == TRUE)
			printf("Monopolized: TRUE ||\t");
		else
			printf("Monopolized: FALSE||\t");

		printf("Houses: %2d||\t", p[curr_pl].ownedProperty[i].houses);
		printf("Hotel: %2d||\t", p[curr_pl].ownedProperty[i].hotel);


		
	}
}

//duplicate functions w/ each returning value //for pay dues function
int PropStatusChecker(player *p, property *prB, int curr_pl){
	int currProp = p[curr_pl].currBoxId;
	
	
	//check if property is Owned
	if(prB[currProp].status == OWNED && (prB[currProp].propertyID >= BROWN && prB[currProp].propertyID <= TRAIN)){
		for(int i = 1; i < MX_PLAYERS; i++){
			for(int x = 0; x < PROPSIZE; x++){
				if(i != curr_pl){
					if(p[i].ownedProperty[x].pBoxId == currProp){
					
						return TRUE;
					}
				}
			}
			if(i == MX_PLAYERS - 1){//8 PLAYERS MAX
				return FALSE;
			}
		}
	}

return 0;
}
int PropOwnerChkr(player *p, property *prB, int curr_pl){
	int currProp = p[curr_pl].currBoxId;
	
	
	//check if property is Owned
	if(prB[currProp].status == OWNED && prB[currProp].propertyID <= TRAIN){
		for(int i = 1; i < MX_PLAYERS; i++){
			for(int x = 0; x < PROPSIZE; x++){
				if(i != curr_pl){
					if(p[i].ownedProperty[x].pBoxId == currProp){			
						return i;
					}
				}
			}
		}
	}
	return 0;
}
int PropSlotChkr(player *p, property *prB, int curr_pl){
	int currProp = p[curr_pl].currBoxId;
	
	
	//check if property is Owned
	if(prB[currProp].status == OWNED && prB[currProp].propertyID <= TRAIN){
		for(int i = 1; i < MX_PLAYERS; i++){
			for(int x = 0; x < PROPSIZE; x++){
				if(i != curr_pl){
					if(p[i].ownedProperty[x].pBoxId == currProp){			
						return x;
					}
				}
			}
		}
	}
	return 0;
}

//If property is owned, pay the rents
void Pay_Dues(player *p, property *prB, int curr_pl, int dice){
	int propertyOwner = PropOwnerChkr(p, prB, curr_pl);
	int statusCheck = PropStatusChecker(p, prB, curr_pl);
	int propSlot = PropSlotChkr(p, prB, curr_pl);
	int currProp = p[curr_pl].currBoxId;
	int houseStatus = NULL, hotelStatus = NULL;

	houseStatus = p[propertyOwner].ownedProperty[propSlot].houses;
	hotelStatus = p[propertyOwner].ownedProperty[propSlot].hotel;
	if(statusCheck == TRUE){
		if(p[propertyOwner].ownedProperty[propSlot].propID >= BROWN && p[propertyOwner].ownedProperty[propSlot].propID <= BLUE){
			
			if(hotelStatus == 1 && hotelStatus != NULL){
				p[curr_pl].money -= prB[currProp].desc.hotel;
				p[propertyOwner].money += prB[currProp].desc.hotel;
			}
			else if(houseStatus > 0 && houseStatus != NULL){
				switch(houseStatus){
				case 1:
					p[curr_pl].money -= prB[currProp].desc.wH1;
					p[propertyOwner].money += prB[currProp].desc.wH1;
					break;
				case 2:
					p[curr_pl].money -= prB[currProp].desc.wH2;
					p[propertyOwner].money += prB[currProp].desc.wH2; 
					break;
				case 3:
					p[curr_pl].money -= prB[currProp].desc.wH3;
					p[propertyOwner].money += prB[currProp].desc.wH3;
					break;
				case 4:
					p[curr_pl].money -= prB[currProp].desc.wH4;
					p[propertyOwner].money += prB[currProp].desc.wH4;
					break;
				}
			}
			else if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == TRUE){
				p[curr_pl].money -= prB[currProp].desc.monopolyRent;
				p[propertyOwner].money += prB[currProp].desc.monopolyRent;
			}
			else if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == FALSE){
				p[curr_pl].money -= prB[currProp].desc.rent;
				p[propertyOwner].money += prB[currProp].desc.rent;
			}
		}
		else if(p[propertyOwner].ownedProperty[propSlot].propID == COMPANY){
			if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == FALSE){
				p[curr_pl].money -= (prB[currProp].desc.rent * float(dice));
				p[propertyOwner].money += (prB[currProp].desc.rent * float(dice));
			}
			else if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == TRUE){
				p[curr_pl].money -= (prB[currProp].desc.monopolyRent * float(dice));
				p[propertyOwner].money += (prB[currProp].desc.monopolyRent * float(dice));
			}
		}
		else if(p[propertyOwner].ownedProperty[propSlot].propID == TRAIN){
			if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == FALSE){
				p[curr_pl].money -= prB[currProp].desc.rent;
				p[propertyOwner].money += prB[currProp].desc.rent;
			}
			else if(p[propertyOwner].ownedProperty[propSlot].BoolMonopolized == TRUE){
				p[curr_pl].money -= prB[currProp].desc.monopolyRent;
				p[propertyOwner].money += prB[currProp].desc.monopolyRent;
			}
		}
		

		printf("\nYou landed at %4s, it's P%d property", prB[currProp].desc.name, propertyOwner);
		printf("\nPlayer- P%d paid %.2f to Player- P%d", curr_pl, prB[currProp].desc.rent, propertyOwner);
		printf("\nP%d-Money left: %.2f", curr_pl, p[curr_pl].money);

	}
	//false //do nothing
}

//buy house or hotel if monopolized
void buyUpgrade(player *p, property *prB, int curr_pl, int cardBoxId, int cardSlot){
	if(p[curr_pl].ownedProperty[cardSlot].houses != 4){
		p[curr_pl].ownedProperty[cardSlot].houses++;
		p[curr_pl].money -= prB[cardBoxId].desc.buildCost;
		printf("\nYou bought a house!");
	}
	else if(p[curr_pl].ownedProperty[cardSlot].hotel == 0){
		p[curr_pl].ownedProperty[cardSlot].hotel++;
		p[curr_pl].money -= prB[cardBoxId].desc.buildCost;
		printf("\nFinally a Hotel!!");
	}

}
void upgradeProperty(player *p, property *prB, int curr_pl){
	char choice = '\0';
	char cardName[NAMESIZE];
	int cardBoxId = NULL;
	int propSlot = NULL;
	printf("Select a property: ");
	scanf(" %s", cardName);
	
	//search property
	for(int i = 0; i < PROPSIZE; i++){
		if(strncmp(prB[i].desc.name, cardName, NAMESIZE) == 0){
			cardBoxId = prB[i].propBoxId;
		}
	}
	//search in your slots
	for(int x = 0; x < PROPSIZE; x++){
		if(cardBoxId == p[curr_pl].ownedProperty[x].pBoxId){
			propSlot = x;
		}
	}
	fflush(stdin);

	if(cardBoxId != NULL){
		if(p[curr_pl].ownedProperty[propSlot].BoolMonopolized != TRUE && (prB[cardBoxId].propertyID >= BROWN && prB[cardBoxId].propertyID <= BLUE ) ){
			printf("\nYou haven't monopolized its co-properties yet, so upgrading is still not possible");
		}
		else if(prB[cardBoxId].propertyID >= BROWN && prB[cardBoxId].propertyID <= BLUE ){
			if(p[curr_pl].ownedProperty[propSlot].houses != 4){
				printf("\nYou have %d house in this property.", p[curr_pl].ownedProperty[propSlot].houses);
				printf("\nIt costs %.2f to upgrade...\n", prB[cardBoxId].desc.buildCost);
				printf("\nUpgrade? (Press Y): ");
				scanf(" %c", &choice);
				fflush(stdin);
				if(toupper(choice) == 'Y'){
					buyUpgrade(p, prB, curr_pl, cardBoxId, propSlot);
				}
				else{
					printf("\nTransaction canceled...");
				}
			
				}
			else if(p[curr_pl].ownedProperty[propSlot].hotel == 0){
				printf("nYou have 4 houses already, upgrade a hotel now!");
				printf("\nYou have %d hotel in this property.", p[curr_pl].ownedProperty[propSlot].hotel);
				printf("\nIt costs %.2f to upgrade...\n", prB[cardBoxId].desc.buildCost);
				printf("\nUpgrade? (Press Y): ");
				scanf(" %c", &choice);
				fflush(stdin);
				if(toupper(choice) == 'Y'){
				buyUpgrade(p, prB, curr_pl, cardBoxId, propSlot);
				}
			}
			else{
				printf("\nYou can't upgrade this property anymore...");
			}
		}
		else{
			printf("\nYou can't upgrade this property...");
		}
	}
	else{
		printf("\nYou don't have this property");
	}

	

}

//Updates the property status
void BoxOwnedIndicator(player *p, property *prB, char arr[][B][B]){
	int propOwner = NULL;
	int col, row, boxID, actualBoxID;
	char curr_pl[5];

	for(int x = 1; x < MX_PLAYERS; x++){	
		for(int i = 0; i < PROPSIZE; i++){
			boxID = p[x].ownedProperty[i].pBoxId;
			if(prB[boxID].status == OWNED){
				propOwner = x;
				if(boxID < 11){
					col = prB[boxID].posY;
					row = prB[boxID].posX-3;
					strcpy(arr[row][col], "P");
					itoa(propOwner, curr_pl, 10);
					strcat_s(arr[row][col], curr_pl);
				}
				else if(boxID < 21){
					actualBoxID =  (boxID * 2) - 11;
					col = prB[actualBoxID].posY +2;
					if(actualBoxID == 29)
						row = prB[actualBoxID].posX;
					else
						row = prB[actualBoxID].posX -1;

					strcpy(arr[row][col], "P");
					itoa(propOwner, curr_pl, 10);
					strcat_s(arr[row][col], curr_pl);
				}
				else if(boxID < 31){
					actualBoxID =  boxID + ( (boxID - 2) - ( (boxID - 21) * 3) );
					col = prB[actualBoxID].posY;
					row = prB[actualBoxID].posX+2;

					strcpy(arr[row][col], "P");
					itoa(propOwner, curr_pl, 10);
					strcat_s(arr[row][col], curr_pl);
				}
				else if(boxID <= 40){
					actualBoxID =  30 - (2 * (boxID - 31) );
					col = prB[actualBoxID].posY -3;
					if(actualBoxID == 12)
						row = prB[actualBoxID].posX -1;
					else
						row = prB[actualBoxID].posX;

					strcpy(arr[row][col], "P");
					itoa(propOwner, curr_pl, 10);
					strcat_s(arr[row][col], curr_pl);
				}
			}
		}
	}
}
void sellProperty(player *p, property *prB, int curr_pl){
	float sellAmount = NULL;
	char choice = '\0';
	char cardName[NAMESIZE];
	int cardBoxId = NULL, propSlot = NULL, flag = TRUE;
	printf("Select a property: ");
	scanf(" %s", cardName);
	
	//search property
	for(int i = 0; i < PROPSIZE; i++){
		if(strncmp(prB[i].desc.name, cardName, NAMESIZE) == 0){
			cardBoxId = prB[i].propBoxId;
			break;
		}
	}
	//search in your slots
	for(int x = 0; x < PROPSIZE; x++){
		if(cardBoxId == p[curr_pl].ownedProperty[x].pBoxId){
			propSlot = x;
			break;
		}
	}
	fflush(stdin);
	

	while(flag == TRUE && (prB[cardBoxId].propertyID >= BROWN && prB[cardBoxId].propertyID <= TRAIN )){
		printf("\nAre you sure to sell %5s and its upgrades(IF)?", cardName);
		printf("\n( [Y]es | [N]o )");
		choice = getch();
		fflush(stdin);
		switch(toupper(choice)){
		case 'Y':
			if(cardBoxId != NULL ){
				if(p[curr_pl].ownedProperty[propSlot].BoolMonopolized == TRUE ){
					if(p[curr_pl].ownedProperty[propSlot].hotel > 0){
						sellAmount += float(prB[cardBoxId].desc.hotel/2);
					}
					if(p[curr_pl].ownedProperty[propSlot].houses > 0){
						for(int i = 1; i <= p[curr_pl].ownedProperty[propSlot].houses; i++){
							switch(i){
							case 1:
								sellAmount += float(prB[cardBoxId].desc.wH1/2);
								break;
							case 2:
								sellAmount += float(prB[cardBoxId].desc.wH2/2);
								break;
							case 3:
								sellAmount += float(prB[cardBoxId].desc.wH3/2);
								break;
							case 4:
								sellAmount += float(prB[cardBoxId].desc.wH4/2);
								break;
							}
						}
					}
					
					sellAmount += float(prB[cardBoxId].desc.sellValue);
					prB[cardBoxId].status = UNOWNED;
					p[curr_pl].ownedProperty[propSlot].BoolMonopolized = NULL;
					p[curr_pl].ownedProperty[propSlot].propID = Null;
					p[curr_pl].ownedProperty[propSlot].pBoxId = NULL;
					p[curr_pl].ownedProperty[propSlot].houses = NULL;
					p[curr_pl].ownedProperty[propSlot].hotel = NULL;
				}
				else{
					sellAmount += float(prB[cardBoxId].desc.sellValue);
					prB[cardBoxId].status = UNOWNED;
					p[curr_pl].ownedProperty[propSlot].BoolMonopolized = NULL;
					p[curr_pl].ownedProperty[propSlot].propID = Null;
					p[curr_pl].ownedProperty[propSlot].pBoxId = NULL;
					p[curr_pl].ownedProperty[propSlot].houses = NULL;
					p[curr_pl].ownedProperty[propSlot].hotel = NULL;
				
				}

				PropertySorter(p, curr_pl);
				CheckOwnedProperties(p, prB, curr_pl);
				printf("\n%4s was sold for %.2f", cardName, sellAmount);
			}
			else{
				printf("\nYou don't have this property");
			}

			flag = FALSE;
			break;

		case 'N': 
			flag = FALSE;
			printf("\nTransaction canceled...");
			break;
		default:
			//do nothing || loop
			break;
		
		}
	
	
	}

	
}

//Checks the array if current player is stored in surrenderedor defeated list
int checkIfSurrendered(int deadPl[], int curr_pl){
	for(int i = 0; i < MX_PLAYERS; i++){
		if(curr_pl == deadPl[i]){
			return TRUE;
		}

	}

	return FALSE;
}
void surrender(player *p, property *prB, int curr_pl, int *dead_pl){
	char choice = '\0';
	float distAmount = NULL;
	int flag = TRUE;
	printf("\nAre you sure you want to surrender?");
	printf("\n25%% of your netWorth will be added to players.");
	
	while(flag == TRUE){
		printf("\n( [Y]es | [N]o )");
		choice = getch();
		switch(toupper(choice)){
		case 'Y':
			for(int i = 0; i < MX_PLAYERS; i++){
				if(dead_pl[i] == NULL){
					distAmount = p[curr_pl].netWorth * float(0.25);
					dead_pl[i] = curr_pl;
					
					//delete everything
					p[curr_pl].money = NULL;
					p[curr_pl].netWorth = NULL;
					for(int x = 0; x < PROPSIZE; x++){
						prB[p[curr_pl].ownedProperty[x].pBoxId].status = UNOWNED;
						p[curr_pl].ownedProperty[x].propID = Null;
						p[curr_pl].ownedProperty[x].pBoxId = NULL;
						p[curr_pl].ownedProperty[x].houses = NULL;
						p[curr_pl].ownedProperty[x].hotel = NULL;
					}
					
					//distribute money
					for(int y = 0; y < MX_PLAYERS; y++){
						p[y].money += distAmount;
					
					}
					break;
				}
			}

			printf("\nAll players received %.2f", distAmount);
			printf("\nThank you for playing...");
			flag = FALSE;
			break;
		case 'N':
			printf("\nNever give up!");
			break;
			flag = FALSE;
		default:
			//loop
			break;
		
		}
		fflush(stdin);
	}
}

//calculates the netWorth of each player per turn
void netWorthCalc(player *p, property *prB, int curr_pl){
		int boxId = NULL;	
		p[curr_pl].netWorth = p[curr_pl].money;		

		for(int x = 0; x < PROPSIZE; x++){
			boxId = p[curr_pl].ownedProperty[x].pBoxId;
			if(boxId != NULL && boxId > 0){
				if(p[curr_pl].ownedProperty[x].BoolMonopolized == TRUE && (p[curr_pl].ownedProperty[x].propID >= BROWN && p[curr_pl].ownedProperty[x].propID <= BLUE) ){
					p[curr_pl].netWorth += prB[boxId].desc.monopolyRent;
				}
				else{
					p[curr_pl].netWorth += prB[boxId].desc.rent;
				}
				///////////////
				if(p[curr_pl].ownedProperty[x].houses > 0){
					switch(p[curr_pl].ownedProperty[x].houses){
					case 1:
						p[curr_pl].netWorth += prB[boxId].desc.wH1;
						break;
					case 2:
						p[curr_pl].netWorth += prB[boxId].desc.wH2;
						break;
					case 3:
						p[curr_pl].netWorth += prB[boxId].desc.wH3;
						break;
					case 4:
						p[curr_pl].netWorth += prB[boxId].desc.wH4;
						break;
					default:
						//do nothing
						break;
						
					}
				}
				if(p[curr_pl].ownedProperty[x].hotel == 1){
					p[curr_pl].netWorth += prB[boxId].desc.hotel;
				}
			}
		}
		//

}
//scans a winning condition
int scanIFWinner(int curr_pl, int dead_pl[], int mx_plP){
	int deadCtr = 0;

	for(int i = 0; i < MX_PLAYERS; i++){
		if(dead_pl[i] != NULL && dead_pl[i] != curr_pl){
			deadCtr++;
		}
	}

	if(deadCtr == mx_plP - 2){
		return TRUE;
	}
	else
		return FALSE;
}
//Kicks aplayer if bankrupt
void kickPlayer(player *p, property *prB, int dead_pl[], int mx_pl){
	float distAmount = NULL;
	//search a person with negative networth
	for(int x = 1; x < MX_PLAYERS; x++){
		//search dead player array for available slot
		for(int i = 0; i < MX_PLAYERS; i++){
			if(dead_pl[i] == x) //if player is already dead break loop
				break;

			if(p[x].netWorth < 0 && dead_pl[i] == NULL){
				printf("\nPlayer: P%d has now been kicked for being bankrupt.", x);
				distAmount = p[x].netWorth * float(0.25);
				dead_pl[i] = x;
				
				//delete everything
				p[x].money = NULL;
				p[x].netWorth = NULL;
				for(int a = 0; a < PROPSIZE; a++){
					prB[p[x].ownedProperty[a].pBoxId].status = UNOWNED;
					p[x].ownedProperty[a].propID = Null;
					p[x].ownedProperty[a].pBoxId = NULL;
					p[x].ownedProperty[a].houses = NULL;
					p[x].ownedProperty[a].hotel = NULL;
				}
				
				//distribute money
				for(int y = 0; y < MX_PLAYERS; y++){
					p[y].money += distAmount;
				
				}

				printf("\nAll players received %.2f", distAmount);
				printf("\nThank you for playing...");
				getch();
				system("cls");	
				break;
			}
		}

		
	}
}
int WinGame(int curr_pl, int dead_pl[], int mx_plP, player *p, property *prB){
	if(scanIFWinner(curr_pl, dead_pl, mx_plP) == TRUE){
		printf("\nPlayer: P%d has won the game! Congratulations!!", curr_pl);
		printf("\nList of Assets:");
		printf("\nMoney:\t\t%5.2f", p[curr_pl].money);
		printf("\nNetWorth:\t%5.2f", p[curr_pl].netWorth);
		CheckOwnedProperties(p, prB, curr_pl);
		printf("\nPress any key to return to menu...");
		getch();
		system("cls");
		return TRUE;
	}
	else
		return FALSE;
}

void Chance_Community_TAX_Cards(player *p, property *prB, int curr_pl, char arr[][B][B]){
	int currBox = p[curr_pl].currBoxId, propBox = NULL;
	int rngCard= rand() % (6 - 1 + 1) + 1;
	

	for(int x = 0; x < PROPSIZE; x++){
		propBox = prB[x].propBoxId;
		if(currBox == propBox){
			//5 chance cards
			if(prB[x].propertyID == CHANCE){
			switch(rngCard){
			case 1:
			printf("\nYou have won a crossword competition! Collect $100");

				p[curr_pl].money += 100.00;
				printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
				break;
			case 2:
					printf("\nYou got blowned by a tornado! Move 3 steps backwards");
				currBox -= 3;
				//search box
			for(int i = 0; i < PROPSIZE; i++){
					if(currBox == prB[i].propBoxId){
						p[curr_pl].pos.col = prB[i].posX - 1;
						p[curr_pl].pos.row = prB[i].posY;
						p[curr_pl].currBoxId = currBox;
						break;
					}
				}
				
				break;
				case 3:
				printf("\nAdvance to GO and receive $200");
				p[curr_pl].money += 200.00;
				printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
				p[curr_pl].pos.col = prB[1].posX - 1;
				p[curr_pl].pos.row = prB[1].posY;
				p[curr_pl].currBoxId = 1;
				break;
			case 4:
				printf("\nYou got a plane ticket for free! Move 4 steps forward.");
				currBox += 4;
				//search box
				for(int i = 0; i < PROPSIZE; i++){
					if(currBox == prB[i].propBoxId){
						p[curr_pl].pos.col = prB[i].posX - 1;
						p[curr_pl].pos.row = prB[i].posY;
						p[curr_pl].currBoxId = currBox;
						break;
					}
				}
				break;
			case 5:
				printf("\nPay $15 for Poor Tax, it's a Charity!");
				p[curr_pl].money -= 15.00;
				printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
				break;
				}

			getch();
			}
			//5 community box
			else if(prB[x].propertyID == COMM_BOX){
				switch(rngCard){
				case 1:
					printf("\nYou've been jailed for tax evasion");
					propBox = 11;
					printf("\nYou have been moved to JAIL\n");
					p[curr_pl].pos.row = prB[propBox].posX - 1;
					p[curr_pl].pos.col = prB[propBox].posY;
					p[curr_pl].currBoxId = propBox;
					break;
				case 2:
					printf("\nDoctor fees. Pay $50");
					p[curr_pl].money -= 50.00;
					printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
					break;
				case 3:
					printf("\nIncome Tax. Pay $100");
					p[curr_pl].money -= 100.00;
					printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
					break;
				case 4:
					printf("\nWhile sweeping the streets, you found $200");
					p[curr_pl].money += 200.00;
					printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
					break;
				case 5:
					printf("\nPay Life Insurance for $50");
					p[curr_pl].money -= 50.00;
					printf("\nCurrent Money:\t\t%.2f", p[curr_pl].money);
					break;
				}

				getch();
			}
			else if(prB[x].propertyID == TAX){
				switch(rngCard){
				case 1:
					printf("\nTax for this year is $1000!");
					p[curr_pl].money -= 1000.00;
					break;
				case 2:
					printf("\nTax for this year is $300!");
					p[curr_pl].money -= 300.00;
					break;
				case 3:
					printf("\nTax for this year is $400!");
					p[curr_pl].money -= 400.00;
					break;
				case 4:
					printf("\nTax for this year is $450!");
					p[curr_pl].money -= 450.00;
					break;
				case 5:
					printf("\nTax for this year is $500!");
					p[curr_pl].money -= 500.00;
					break;
				
				}
				getch();
			}
			
			system("cls");

			PlayerMove(arr, p, prB, curr_pl, NULL);
			PlayerDisplay(p, prB, arr, curr_pl);
			BoardUpdate(arr, prB, curr_pl);
			BoxOwnedIndicator(p, prB, arr);
			DisplayStatus(NULL, curr_pl, p, prB);
			BoardDisplay(arr);
			
			
			break;

		}
	}

			
}

void ExtraActions(player *p, property *prB, int curr_pl, int deadPl[]){
	int flag = TRUE;
	char choice = NULL;
	do{
		printf("\n(1)\t\tCheck Owned properties");
		printf("\n(2)\t\tUpgrade a property");
		printf("\n(3)\t\tSell a property");
		printf("\n(4)\t\tDeclare surrender");
		printf("\n(Press any key)\t\tDo Nothing\n");
	
		choice = getch();
		fflush(stdin);
		fflush(stdout);
		switch(choice){
			case '1':
				CheckOwnedProperties(p, prB, curr_pl);
				break;
			case '2':
				upgradeProperty(p, prB, curr_pl);
				
				break;
			case '3':
				sellProperty(p, prB, curr_pl);
				break;
			case '4':
				surrender(p, prB, curr_pl, deadPl);
				flag = FALSE;
				break;
			default:
				flag = FALSE;
				break;
		}

		
	}while(flag == TRUE);	
}

void MainGame(player *person, property *prop, int current_Player, int defeatedPlayers[], int MX_playingPlayers, char board[][B][B], int dice){
	int mainFlag = TRUE;
	while(mainFlag == TRUE){	
		current_Player = 1;
		do{
			fflush(stdin);
			netWorthCalc(person, prop, current_Player); //Calculates all netWorth
			kickPlayer(person, prop, defeatedPlayers, MX_playingPlayers); //after calculate, decide who to kick out of the game
			//Skip a dead player
			while(checkIfSurrendered(defeatedPlayers, current_Player) == TRUE ){
				current_Player++;
			}
			if( current_Player > MX_playingPlayers - 1){
				break;
			}
			
			//Win game condition
			if(WinGame(current_Player, defeatedPlayers, MX_playingPlayers, person, prop) == TRUE){
				mainFlag = FALSE;
				break;
			}
			PlayerDisplay(person, prop, board, current_Player);
			
			BoardUpdate(board, prop, current_Player);
			DisplayStatus(dice, current_Player, person, prop);
			BoxOwnedIndicator(person, prop, board);
			printf("\nRoll dice to continue...(Press any key)\n");
			
			BoardDisplay(board);
			getch();
			dice = diceValue();
			system("cls");

///////////////After rolling dice////////////////////
			PlayerMove(board, person, prop, current_Player, dice);
			PlayerDisplay(person, prop, board, current_Player);	
			BoardUpdate(board, prop, current_Player);
			BoxOwnedIndicator(person, prop, board);
			DisplayStatus(dice, current_Player, person, prop);
			BoardDisplay(board);

			//Check if landed on chance || commnity boxes || TAX box
			Chance_Community_TAX_Cards(person, prop, current_Player, board);
			
			//scan or getch at buy()
			BuyProperty(prop, person, current_Player);
			//Pay rents
			Pay_Dues(person, prop, current_Player, dice);
			
			//Sort property based on IDs
			PropertySorter(person, current_Player);
			//Display properties
			CheckOwnedProperties(person, prop, current_Player);
			printf("\nAny other action?\n");
			
			ExtraActions(person, prop, current_Player, defeatedPlayers);
		
			printf("\nPress any key to continue...\n");
			
			getch();
			//end turn of the player
			system("cls");	
			current_Player++;
			dice = 0; //reset
		}while(current_Player < MX_playingPlayers && current_Player != 0 && mainFlag == TRUE);
		fflush(stdin);
		fflush(stdout);
		
	}
}

void monopolyText(){
	printf("\n MMMMMMMM               MMMMMMMM     OOOOOOOOO     NNNNNNNN        NNNNNNNN     OOOOOOOOO     PPPPPPPPPPPPPPPPP        OOOOOOOOO     LLLLLLLLLLL         YYYYYYY       YYYYYYY");
	printf("\n M:::::::M             M:::::::M   OO:::::::::OO   N:::::::N       N::::::N   OO:::::::::OO   P::::::::::::::::P     OO:::::::::OO   L:::::::::L         Y:::::Y       Y:::::Y");
	printf("\n M::::::::M           M::::::::M OO:::::::::::::OO N::::::::N      N::::::N OO:::::::::::::OO P::::::PPPPPP:::::P  OO:::::::::::::OO L:::::::::L         Y:::::Y       Y:::::Y");
	printf("\n M::::::::::M       M::::::::::MO::::::O   O::::::ON::::::::::N    N::::::NO::::::O   O::::::O  P::::P     P:::::PO::::::O   O::::::O  L:::::L           YYY:::::Y   Y:::::YYY");
	printf("\n M:::::::::::M     M:::::::::::MO:::::O     O:::::ON:::::::::::N   N::::::NO:::::O     O:::::O  P::::P     P:::::PO:::::O     O:::::O  L:::::L              Y:::::Y Y:::::Y ");
	printf("\n M:::::::M::::M   M::::M:::::::MO:::::O     O:::::ON:::::::N::::N  N::::::NO:::::O     O:::::O  P::::PPPPPP:::::P O:::::O     O:::::O  L:::::L               Y:::::Y:::::Y    ");
	printf("\n M::::::M M::::M M::::M M::::::MO:::::O     O:::::ON::::::N N::::N N::::::NO:::::O     O:::::O  P:::::::::::::PP  O:::::O     O:::::O  L:::::L                Y:::::::::Y     ");
	printf("\n M::::::M  M::::M::::M  M::::::MO:::::O     O:::::ON::::::N  N::::N:::::::NO:::::O     O:::::O  P::::PPPPPPPPP    O:::::O     O:::::O  L:::::L                 Y:::::::Y      ");
	printf("\n M::::::M   M:::::::M   M::::::MO:::::O     O:::::ON::::::N   N:::::::::::NO:::::O     O:::::O  P::::P            O:::::O     O:::::O  L:::::L                  Y:::::Y       ");
	printf("\n M::::::M    M:::::M    M::::::MO:::::O     O:::::ON::::::N    N::::::::::NO:::::O     O:::::O  P::::P            O:::::O     O:::::O  L:::::L                  Y:::::Y       ");
	printf("\n M::::::M     MMMMM     M::::::MO::::::O   O::::::ON::::::N     N:::::::::NO::::::O   O::::::O  P::::P            O::::::O   O::::::O  L:::::L         LLLLLL   Y:::::Y       ");
	printf("\n M::::::M               M::::::MO:::::::OOO:::::::ON::::::N      N::::::::NO:::::::OOO:::::::OPP::::::PP          O:::::::OOO:::::::OLL:::::::LLLLLLLLL:::::L   Y:::::Y       ");
	printf("\n M::::::M               M::::::M OO:::::::::::::OO N::::::N       N:::::::N OO:::::::::::::OO P::::::::P           OO:::::::::::::OO L::::::::::::::::::::::LYYYY:::::YYYY    ");
	printf("\n M::::::M               M::::::M   OO:::::::::OO   N::::::N        N::::::N   OO:::::::::OO   P::::::::P             OO:::::::::OO   L::::::::::::::::::::::LY:::::::::::Y    ");
	printf("\n MMMMMMMM               MMMMMMMM     OOOOOOOOO     NNNNNNNN         NNNNNNN     OOOOOOOOO     PPPPPPPPPP               OOOOOOOOO     LLLLLLLLLLLLLLLLLLLLLLLLYYYYYYYYYYYYY    ");
	printf("\n\n\n\n");
}
int Menu(){
	int choice = NULL;
	monopolyText();
	
	printf("\n\n(1)Start Game");
	printf("\n\n(2)How to Play");
	printf("\n\n(0)EXIT");

	printf("\n\nSelection: ");
	scanf(" %d", &choice);
	fflush(stdin);
	system("cls");
	return choice;
}
int selectHowManyPlayers(){
	char yesNo = NULL; 
	int nPlayers = NULL;
	monopolyText();
	printf("\n\nThe default number of players are 4, continue?");
	//endless loop
	while(TRUE){
		printf("\n\n( [Y]es | [N]o )");
		yesNo = getch();
		fflush(stdin);
		
		switch(toupper(yesNo)){
		case 'Y':
			system("cls");
			return 4; 
			break;
		case 'N':
			system("cls");
			monopolyText();
			printf("\n\n[The (N) players) should range from 2 to 7 only]");
			while(TRUE){
				printf("\n\nInput the number of Players playing: ");
				scanf(" %d", &nPlayers);
				if(isNumeric(&nPlayers) == TRUE && (nPlayers >= 2 && nPlayers <= 7) ){
					system("cls");
					return nPlayers;
				}
			}

			break;
		}
	}

	
}

void theRules(){
	monopolyText();
	printf("\n\nGOAL");
	printf("\nThe object of the game is to become the wealthiest player through buying, renting and selling property");
	printf("\nEach player is given $1500");

	printf("\n\nGO LINE");
	printf("\nEach time a player's token lands on or passes over GO, whether by throw of the dice or by drawing a card, the Banker pays him/her a $200 salary. ");
	
	printf("\n\nMONOPOLIZING");
	printf("\nWhen you land on property owned by another player, the owner collects rent from you.");
	printf("\nIt is an advantage to collect all properties in a the same group, as the rent will be charged doubled");
	printf("\nIt is even more advantageous to have houses or hotels on properties because rents are much higher than for unimproved properties.");

	printf("\n\nHOUSES & HOTELS");
	printf("\nWhen you own all the properties in a property-group you may buy houses from the Bank and erect them on those properties. ");
	printf("\nWhen you have four houses on each property of a complete property-group, you may buy a hotel from the Bank and erect it on any property of that property-group.");

	printf("\n\nCOMMUNITY | CHANCE | TAX BOXES");
	printf("\nThese boxes are what makes the economy circulate and makes the game more faster to complete");
	printf("\nThese contains random situations that takes or gives money to the player.");
	

	printf("\n\nBANKRUPTCY");
	printf("\nYou are declared Bankrupt, when your Net Worth had reached negative \nand the player will be automatically kicked from the game");
	
	printf("\n\nPress any key to get back to menu...");
	getch();
	system("cls");
}