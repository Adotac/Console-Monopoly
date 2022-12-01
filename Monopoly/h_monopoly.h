#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MX_DICE 7
#define MX_PLAYERS 8 //MAX PLAYERS ARE 7, I DISREGARD ELEMENT 0
#define B 34 //34 x 34 board size as each box contains 3 spaces for 11 x 11 (+1 for extra space)
#define PROPSIZE 40 //total boxes in a board
#define NAMESIZE 20


#ifndef def_monopoly
#define definitions

typedef enum PROPERTY_ID P_ID;
enum PROPERTY_ID{BROWN = 1, SBLUE, PINK, ORANGE, RED, YELLOW, GREEN, BLUE, 
			//////Non-house properties || Logistic properties || facilities
			
			COMPANY,
			TRAIN,
			CHANCE = 15, COMM_BOX,
			GO = 20, JAIL, FPARK, GOTOJAIL,
			TAX = 25,
			Null = NULL};

enum CARDSTATUS {OWNED = 0, UNOWNED = 1, NOT_AVAILABLE = 2};

typedef struct CARD Card;
struct CARD{
		float rent;
		float monopolyRent;
		//if not utility||rent with number of houses and HOTEL
		float wH1, wH2, wH3, wH4, hotel; //each wH represents the 4 houses
		float price;
		float sellValue;
		//price to build a house each
		float buildCost;

		char name[NAMESIZE];
};
typedef struct PROPERTIES property;
struct PROPERTIES{
	CARDSTATUS status;
	enum PROPERTY_ID propertyID;
	int propBoxId;
	int posX;
	int posY;	
	Card desc;
	
};



typedef struct PLAYERS player;
typedef struct OwnedP ownProp;
struct OwnedP{
		int BoolMonopolized;
		enum PROPERTY_ID propID;
		int pBoxId;
		int houses;
		int hotel;
	};
struct PLAYERS{
	float money;
	float netWorth;
	int currBoxId;
	ownProp ownedProperty[PROPSIZE];
	struct Pos{
		int row, col;
	}pos;
};


int isNumeric(const int*);

void DisplayStatus(int , int , player *p , property *prB);

void PlayerPos_Initialize(player *p, int,int, int[]);


void BoardUpdate(char[][B][B], property*, int);

void BoardDisplay(char[][B][B]);

void BoxNotOwnedInitialize(property*);

void BoxDisplayNames(char[][B][B], int,int, int, int*);

void BoxProperties(property*, int, int, int);


void PlayerDisplay(player*, property*, char[][B][B], int);

void PlayerMove(char[][B][B], player*, property*, int,int);

int diceValue(void);


void BuyProperty(property*, player*, int);


void PropertySorter(player*, int);

int CheckIfMonopolized(player*, PROPERTY_ID, int);

void CheckOwnedProperties(player*, property*, int);


int PropOwnerChkr(player*, property*, int);

int PropSlotChkr(player*, property*, int);

int PropStatusChecker(player*, property*, int);

void Pay_Dues(player*, property*, int, int);


void buyUpgrade(player*, property*, int, int, int);

void upgradeProperty(player* , property* , int);


void BoxOwnedIndicator(player*, property*, char[][B][B]);


int checkIfSurrendered(int[], int);

void surrender(player*, property*, int, int*);


void netWorthCalc(player*, property*, int);


int scanIFWinner(int, int[], int);

void kickPlayer(player*, property*, int[], int);

int WinGame(int, int[], int, player*, property*);


void ExtraActions(player*, property*, int, int[]);


void MainGame(player *, property*, int, int [], int, char[][B][B], int);

void monopolyText();

void theRules();

int Menu();

int selectHowManyPlayers();

void Chance_Community_TAX_Cards(player*, property*, int, char[][B][B]);
#endif