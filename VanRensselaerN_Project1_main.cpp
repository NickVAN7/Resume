#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// This is a playing card class 
// A Card has two characteristics; Face and Suit
// Face is a int from 1 to 13
// Suit is a char from 1 to 4 -- represents Clubs, Diamonds, Hearts, and Spades
class Card {
public:
	Card();
	int getFace();
	char getSuit();
	void setCard(int, char);
	void displayCard();

	friend class Deck;
	friend class Hand;

private:
	int faceValue;
	char suit[1];
};

// Card constructor -- initializes a card with a suit and a value between 1 and 13
Card::Card() {
	int randNum = rand() % 13 + 1;
	if (randNum <= 13) {
		faceValue = randNum;
	}
	int randNum2 = rand() % 5 + 1;
	if (randNum2 == 1) { suit[1] = { 'C' }; }
	else if (randNum2 == 2) { suit[1] = { 'D' }; }
	else if (randNum2 == 3) { suit[1] = { 'H' }; }
	else if (randNum2 == 4) { suit[1] = { 'S' }; }
}
 
// Method to set a card value with the faceValue and suitValue
void Card::setCard(int newFace, char newSuit) {
	faceValue = newFace;
	suit[1] = newSuit;
}

// getter method for returning new faceValue
int Card::getFace() {
	return faceValue;
}

// getter method for returning new faceValue 
char Card::getSuit() {
	return suit[1];
}

// Method for displaying a string value of the card using the faceValue and suitValue
// Converts the numerical faceValue into their appopriate names
// This is specifically for 1 (Ace), 11 (Jack), 12 (Queen), and 13 (King). 
// It also converts the char values to the full names
void Card::displayCard() {
	if (faceValue == 1) {
		cout << "Ace of ";
	}
	else if (faceValue == 11) {
		cout << "Jack of ";
	}
	else if (faceValue == 12) {
		cout << "Queen of ";
	}
	else if (faceValue == 13) {
		cout << "King of ";
	}
	else {
		cout << faceValue << " of ";
	}

	if (suit[1] == 'C') {
		cout << "Clubs";
	}
	else if (suit[1] == 'D') {
		cout << "Diamonds";
	}
	else if (suit[1] == 'H') {
		cout << "Hearts";
	}
	else if (suit[1] == 'S') {
		cout << "Spades";
	}
	cout << endl;
}

//-------------------------------------------------------------------------------------
 

// This is a class to create a deck of cards
// A deck consists of 52 cards 
// This gives you 13 cards for each suit value 
class Deck {
public:
	Deck();
	void createNewDeck();
	Card drawCard();
	void shuffle();
	bool isEmpty();
	//void reset();		// Not able to get this to work correctly  
	int isTopCard();
	int topCard;

	friend class Hand;

private:
	// setting constants for Deck values
	static const int maxCards = 52;
	static const int numSuits = 4;
	static const int cardsPer = 13;

	Card deck[maxCards];
	Card deckCopy[maxCards];
};

// This method forms a deck  
// It fills the 'deck' with each of 13 faceValues for each suit
Deck::Deck(){
	char suitVals[numSuits] = { 'C', 'D', 'H', 'S' };
	int cardSub = 0;
	for (int suitSub = 0; suitSub < numSuits; suitSub++) {
		for (int faceVal = 1; faceVal <= cardsPer; faceVal++) {
			deck[cardSub].setCard(faceVal, suitVals[suitSub]);
			cardSub++;
		}
	}
	topCard = -1;
	// deckCopy[cardSub] = deck[cardSub];
}

// This method is used to create a second, copy deck
// It may not be needed...
void Deck::createNewDeck() {
	char suitVals[numSuits] = { 'C', 'D', 'H', 'S' };
	int cardSub = 0;
	for (int suitSub = 0; suitSub < numSuits; suitSub++) {
		for (int faceVal = 1; faceVal <= cardsPer; faceVal++) {
			deckCopy[cardSub].setCard(faceVal, suitVals[suitSub]);
			cardSub++;
		}
	}
	topCard = -1;
}

// This method draws a Card from the top of the deck 
Card Deck::drawCard() {
	topCard++;
	return deck[topCard];
}

// This method shuffles the deck of cards 
// It uses the rand() % 52 to randomly assign cards to the deck 
void Deck::shuffle() {
	for (int i = 0; i < maxCards; i++) {
		int j = rand() % maxCards;
		Card temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}


//void Deck::reset() {
//	deck[maxCards] = deckCopy[maxCards];
//}

// This tests if the deck is empty 
bool Deck::isEmpty() {
	return topCard + 1 == maxCards;
}

// This returns the topCard of the deck
int Deck::isTopCard() {
	return topCard; 
}

//-------------------------------------------------------------------------------------

// initializing state values for hands
const int ROYALFLUSH = 9;
const int STRAIGHTFLUSH = 8;
const int FOUROFAKIND = 7;
const int FULLHOUSE = 6;
const int FLUSH = 5;
const int STRAIGHT = 4;
const int THREEOFAKIND = 3;
const int TWOPAIR = 2;
const int JACKSORBETTER = 1;
const int NONE = 0;

// This class forms a hand of cards, a hand consists of 5 randomly drawn cards
// This class also contains the state finding methods -> finds the appropriate state for each hand
// Based on the state, the payout is found 
// (This could probably be done in the next class, but it was easier to implement here)
class Hand {
public:
	Hand();
	void drawHand();
	void sortByFace();
	void sortBySuit();

	bool isRoyalFlush();
	bool isStraightFlush();
	bool isFourOfAKind();
	bool isFullHouse();
	bool isFlush();
	bool isStraight();
	bool isThreeOfAKind();
	bool isTwoPair();
	bool isJacksOrBetter();

	void setState();
	int getState();
	void printState();

	void setPayout(int bet);
	int getPayout();

	void switchCard();

	int state;

	friend class gameInterface;

private:
	Deck deck;
	Card hand[5] = {};
	int payout = 0;
};

// Default constructor for the Hand Class
Hand::Hand() {

}

// Method to draw a Hand 
// It takes a deck of cards, shuffles it and draws 5 cards from the top
// This could also be done in the constructor class
void Hand::drawHand() {
	int x = rand() % 10;
	for (int i = 0; i < x; i++) {
		deck.shuffle();
	}

	for (int i = 0; i < 5; i++) {
		Card c = deck.drawCard();
		c.displayCard();
		hand[i] = c;
	}
}

// This method sorts cards by their face value
// This is used for a few of the state finding methods 
void Hand::sortByFace() {
	for (int i = 0; i < 5; i++) {
		int minPos = i;
		for (int j = i + 1; j < 5; j++) {
			if (hand[j].getFace() < hand[minPos].getFace()) {
				minPos = j;
			}
		}
		Card temp = hand[i];
		hand[i] = hand[minPos];
		hand[minPos] = temp;
	}
}

// This method sorts cards by their suit value
// This is used for a few of the state finding methods
void Hand::sortBySuit() {
	for (int i = 0; i < 5; i++) {
		int minPos = i;
		for (int j = i + 1; j < 5; j++) {
			if (hand[j].getSuit() < hand[minPos].getSuit()) {
				minPos = j;
			}
		}
		Card temp = hand[i];
		hand[i] = hand[minPos];
		hand[minPos] = temp;
	}
}

// Method to find Royal Flush state
// A Royal Flush is defined as 10, Jack, Queen, King, and Ace of one suit
bool Hand::isRoyalFlush() {
	sortByFace();

	bool case1 = hand[0].getFace() == 1 && 
		hand[1].getFace() == 10 && 
		hand[2].getFace() == 11 && 
		hand[3].getFace() == 12 && 
		hand[4].getFace() == 13;
	bool case2 = hand[0].getSuit() + 1 == hand[1].getSuit() &&
		hand[1].getSuit() + 1 == hand[2].getSuit() &&
		hand[2].getSuit() + 1 == hand[3].getSuit() &&
		hand[3].getSuit() + 1 == hand[4].getSuit();

	return (case1 && case2);
}

// Method to find a Straight Flush state
// A Straight flush is defined as an increasing adjacent Face values of one suit
bool Hand::isStraightFlush() {
	if (isRoyalFlush()) { return false; }
	sortByFace();

	bool case1 = hand[0].getFace() + 1 == hand[1].getFace() && 
		hand[1].getFace() + 1 == hand[2].getFace() && 
		hand[2].getFace() + 1 == hand[3].getFace() && 
		hand[3].getFace() + 1 == hand[4].getFace();
	bool case2 = hand[0].getSuit() + 1 == hand[1].getSuit() && 
		hand[1].getSuit() + 1 == hand[2].getSuit() && 
		hand[2].getSuit() + 1 == hand[3].getSuit() && 
		hand[3].getSuit() + 1 == hand[4].getSuit();

	return (case1 && case2);
}

// Method to find a Four of a Kind state
// A Four of a Kind is defined as matching number cards of all 4 suits
bool Hand::isFourOfAKind() {
	sortByFace();

	bool case1 = hand[0].getFace() == hand[1].getFace() &&
		hand[1].getFace() == hand[2].getFace() &&
		hand[2].getFace() == hand[3].getFace();
	bool case2 = hand[1].getFace() == hand[2].getFace() &&
		hand[2].getFace() == hand[3].getFace() &&
		hand[3].getFace() == hand[4].getFace();

	return (case1 || case2);
}


// Method to find a Full House state
// A Full House is defined as two cards of one face value and three of another face value
bool Hand::isFullHouse() {
	sortByFace();

	bool case1 = hand[0].getFace() == hand[1].getFace() && 
		hand[1].getFace() == hand[2].getFace() && 
		hand[3].getFace() == hand[4].getFace();
	bool case2 = hand[0].getFace() == hand[1].getFace() && 
		hand[2].getFace() == hand[3].getFace() && 
		hand[3].getFace() == hand[4].getFace();

	return (case1 || case2);
}

// Method to find a Flush state
// A Flush is defined as 5 cards of one suit 
bool Hand::isFlush() {
	if (isRoyalFlush() || isStraightFlush()) { return false; }
	
	bool case1 = hand[0].getSuit() == hand[1].getSuit() && 
		hand[1].getSuit() == hand[2].getSuit() && 
		hand[2].getSuit() == hand[3].getSuit() && 
		hand[3].getSuit() == hand[4].getSuit();

	return case1;
}

// Method to find a Straight state
// A Straight is defined as increasing adjacent numbers of any suit 
bool Hand::isStraight() {
	if (isRoyalFlush() || isStraightFlush()) { return false; }

	bool case1 = hand[0].getFace() + 1 == hand[1].getFace() && 
		hand[1].getFace() + 1 == hand[2].getFace() && 
		hand[2].getFace() + 1 == hand[3].getFace() && 
		hand[3].getFace() + 1 == hand[4].getFace();

	return case1;
}

// Method to find a Three of a Kind state
// Three of a kind is defined as three cards of one face value
bool Hand::isThreeOfAKind() {
	if (isFourOfAKind() || isFullHouse()) {return false;}

	bool case1 = hand[0].getFace() == hand[1].getFace() && hand[1].getFace() == hand[2].getFace();
	bool case2 = hand[1].getFace() == hand[2].getFace() && hand[2].getFace() == hand[3].getFace();
	bool case3 = hand[2].getFace() == hand[3].getFace() && hand[3].getFace() == hand[4].getFace();

	return (case1 || case2 || case3);
}

// Method to find Two Pair
// Two pair is defined as two pairs of two different face values
bool Hand::isTwoPair() {
	if (isFourOfAKind() || isFullHouse() || isThreeOfAKind()) { return false; }

	bool case1 = hand[0].getFace() == hand[1].getFace() && hand[2].getFace() == hand[3].getFace();
	bool case2 = hand[0].getFace() == hand[1].getFace() && hand[3].getFace() == hand[4].getFace();
	bool case3 = hand[1].getFace() == hand[2].getFace() && hand[3].getFace() == hand[4].getFace();

	return (case1 || case2 || case3);
}

// Method to find a pair of Jacks of better
// Finds a pair of Jacks, Queens, Kings, or Aces.
bool Hand::isJacksOrBetter() {
	if (isFourOfAKind() || isFullHouse() || isThreeOfAKind() || isTwoPair()) { return false; }

	bool case1 = hand[0].getFace() == hand[1].getFace() && (hand[0].getFace() >= 11 || hand[0].getFace() == 1);
	bool case2 = hand[1].getFace() == hand[2].getFace() && (hand[1].getFace() >= 11 || hand[1].getFace() == 1);
	bool case3 = hand[2].getFace() == hand[3].getFace() && (hand[2].getFace() >= 11 || hand[2].getFace() == 1);
	bool case4 = hand[3].getFace() == hand[4].getFace() && (hand[3].getFace() >= 11 || hand[3].getFace() == 1);

	return (case1 || case2 || case3 || case4);
}


// Function to switch Cards when prompted
// Each card can only be swwitched out once. 
// If player attempts to switch a card more than once, program ends.
void Hand::switchCard() {
	cout << "\nWould you like to switch any cards? " << endl;
	cout << "Note: you can only switch each card once. Do not try to switch a card more than once." << endl;
	cout << "Use '1', '2', '3', '4', '5', or 'N' (For no)." << endl;
	int num;
	bool firstCardSwitched = false;
	bool secondCardSwitched = false;
	bool thirdCardSwitched = false;
	bool fourthCardSwitched = false;
	bool fifthCardSwitched = false;

	while (true) {
		if (!(cin >> num)) {
			cout << "Okay, no cards will be switched." << endl;
			cin.clear();
			cin.ignore(255, '\n');
			break;
		}
		else if (num == 1 && firstCardSwitched == false) {
			cout << "Switching the first card, your new card is: " << endl;
			hand[0] = deck.drawCard();
			hand[0].displayCard();
			firstCardSwitched = true;
			continue;
		}
		else if (num == 2 && secondCardSwitched == false) {
			cout << "Switching the second card, your new card is: " << endl;
			hand[1] = deck.drawCard();
			hand[1].displayCard();
			secondCardSwitched = true;
			continue;
		}
		else if (num == 3 && thirdCardSwitched == false) {
			cout << "Switching the third card, your new card is: " << endl;
			hand[2] = deck.drawCard();
			hand[2].displayCard();
			thirdCardSwitched = true;
			continue;
		}
		else if (num == 4 && fourthCardSwitched == false) {
			cout << "Switching the fourth card, your new card is: " << endl;
			hand[3] = deck.drawCard();
			hand[3].displayCard();
			fourthCardSwitched = true;
			continue;
		}
		else if (num == 5 && fifthCardSwitched == false) {
			cout << "Switching the fifth card, your new card is: " << endl;
			hand[4] = deck.drawCard();
			hand[4].displayCard();
			fifthCardSwitched = true;
			continue;
		}
		else {
			cout << "Invalid input. Please try again!" << endl;
			cin.clear();
			cin.ignore();
			continue;
		}
		break;
	}
	
	// prints new hand after cards are switched
	cout << "\nYour hand is: " << endl;
		for (int i = 0; i < 5; i++) {
			hand[i].displayCard();
		}
}

// Method to set state of hand.
// Tests if the hand satisfies a state, and sets it equal to that value
// If the hand satisfies none of the states, it sets state equal to NONE
void Hand::setState() {
	if (isRoyalFlush()) { state = ROYALFLUSH; }
	else if (isStraightFlush()) { state = STRAIGHTFLUSH; }
	else if (isFourOfAKind()) { state = FOUROFAKIND; }
	else if (isFullHouse()) { state = FULLHOUSE; }
	else if (isFlush()) { state = FLUSH; }
	else if (isStraight()) { state = STRAIGHT; }
	else if (isThreeOfAKind()) { state = THREEOFAKIND; }
	else if (isTwoPair()) { state = TWOPAIR; }
	else if (isJacksOrBetter()) { state = JACKSORBETTER; }
	else { state = NONE; }
}

// Returns state from setState() method
int Hand::getState() {
	return state;
}

// Method to set payout amount
// Sets payout amount based on the bet amount and given return values
// Note: could have done this as part of setState() method
void Hand::setPayout(int bet) {
	if (isRoyalFlush()) { payout = 250 * bet; }
	else if (isStraightFlush()) { payout = 50 * bet; }
	else if (isFourOfAKind()) { payout = 25 * bet; }
	else if (isFullHouse()) { payout = 9 * bet; }
	else if (isFlush()) { payout = 6 * bet; }
	else if (isStraight()) { payout = 4 * bet; }
	else if (isThreeOfAKind()) { payout = 3 * bet; }
	else if (isTwoPair()) { payout = 2 * bet; }
	else if (isJacksOrBetter()) { payout =  bet; }
	else { payout = 0; }
}

// Returns payout from setPayout method
int Hand::getPayout() {
	return payout;
}

// Method to print a string value for the state of the hand
// Prints Payout amount for each state value
// Note: Could have done this as part of setState() method too 
void Hand::printState() {
	if (state == ROYALFLUSH) {
		cout << "\nYou drew a Royal Flush! This pays 250 to 1.\n" << endl;
	}
	else if (state == STRAIGHTFLUSH) {
		cout << "\nYou drew a Straight Flush! This pays 50 to 1.\n" << endl;
	}
	else if (state == FOUROFAKIND) {
		cout << "\nYou drew Four of A Kind! This pays 25 to 1.\n" << endl;
	}
	else if (state == FULLHOUSE) {
		cout << "\nYou drew a Full House! This pays 9 to 1.\n" << endl;
	}
	else if (state == FLUSH) {
		cout << "\nYou drew a Flush! This pays 6 to 1.\n" << endl;
	}
	else if (state == STRAIGHT) {
		cout << "\nYou drew a Straight! This pays 4 to 1.\n" << endl;
	}
	else if (state == THREEOFAKIND) {
		cout << "\nYou drew Three of A Kind! This pays 3 to 1.\n" << endl;
	}
	else if (state == TWOPAIR) {
		cout << "\nYou drew Two Pair! This pays 2 to 1.\n" << endl;
	}
	else if (state == JACKSORBETTER) {
		cout << "\nYou drew a pair of Jacks or Better. This pays 1 to 1.\n" << endl;
	}
	else {
	cout << "\nYou did not draw a winning hand. Please Play again.\n" << endl;
	}
}

//-------------------------------------------------------------------------------------

// Class for game interface of the virtual poker game
// Displays game menus and keeps track of bankrolls and bets
class gameInterface {
public:
	gameInterface();
	void getInput();
	int depositCoins(int);
	void getDeposit();
	void getUserBet();
	void setBet(int);
	int getBet();
	void displayMenu();
	void executeMain();
	void playGame();

protected:
	int bet;

private:
	int bankroll;
	int deposit;
	int menuChoice = 0;
	Hand mainHand;
};

// This is the constructor for the gameInterface class
// For new game, initializes bankroll to 0 
gameInterface::gameInterface() {
	bankroll = 0;
}

// Method to get user input for displayMenu method
void gameInterface::getInput() {
	cin >> menuChoice;
}

// Method to deposit coins into bankroll. 
// The bankroll is where the bet coins come from
// Number of coins can be any integer
int gameInterface::depositCoins(int coins) {
	bankroll = bankroll + coins;
	return bankroll;
}

// Method to get user input for deposit amount (to bankroll)
void gameInterface::getDeposit() {
	cin >> deposit;
}

// Method to get user input for Bet amount
void gameInterface::getUserBet() {
	cin >> bet;
}

// Method to set the bet amount 
// Bet amount is inputed from user in getUserBet() method
// Subtracts bet from bankroll to get new bankroll 
void gameInterface::setBet(int curBet) {
	bet = curBet;
	bankroll = bankroll - bet;
}

// Getter method for setBet()
int gameInterface::getBet() {
	return bet;
}

// Method for displaying menu of game
// Gives menu options for beginning of game as well as after each hand.
void gameInterface::displayMenu() {
	string choices1[] = { "1 - Play Game",
						"2 - Add Coins to Bankroll",
						"9 - Quit Game" };

	//cout << "\nWelcome to the Virtual Poker game. Directions are below: " << endl;
	cout << "Your current Bankroll is: " << bankroll << " coins." << endl;

	if (bankroll == 0) { "Please add coins to bankroll."; }

	cout << "\nWhat would you like to do? " << endl;
	for (int i = 0; i < 3; i++) {
		cout << choices1[i] << endl;
	}
}

// Method to run main parts of the game, this is what is run over and over in the playGame() method
// This method creates the deck and hand,
// Gets bet amount from player (and checks if the bet is 'legal' or not),
// Draws a random hand,
// Finds the state of the hand using getState()
// And finds the payout to the player
void gameInterface::executeMain() {

	bool running = true;

	Deck mainDeck;
	Hand mainHand;

	int numIn;

	if (bankroll == 0) {
		cout << "Your bankroll is 0. Please enter coins to your bankroll." << endl;
		cout << "How many coins would you like to add?" << endl;
		cin >> numIn;
		getDeposit();
		depositCoins(numIn);
	}
	else {
		cout << "Place a bet, input a number from 1 to 5" << endl;
		getUserBet();
	}

	if (bet == 0 || bet > 5) {
		cout << "Bet amout must be in between 1 and 5." << endl;
		cout << "Input another number, this time between 1 and 5." << endl;
		getUserBet();
	}

	if (bet > bankroll) {
		cout << "\nYou tried to bet more than you have in your bankroll." << endl;
		cout << "Your bankroll is: " << bankroll << endl;
		cout << "Please enter a number between 1 and " << bankroll << endl;
		getUserBet();
	}

	bet = getBet();

	cout << "Thank you, your bet is: " << bet << endl;

	cout << "\n Your hand is: " << endl;
	mainHand.drawHand();

	mainHand.switchCard();

	mainHand.setState();
	mainHand.getState();
	mainHand.printState();
	mainHand.setPayout(bet);

	
	int pay = mainHand.getPayout();
	cout << "Your payout was: " << pay << endl;
	bankroll = bankroll - bet + pay;
	cout << "Your new bankroll is: " << bankroll << endl;
}

// Method to run game altogether
// Contains all necessary methods and rules to play the virtual poker game
// Uses the executeMain() method to drive the actual game
// This contains the quitting ability based on the user input 
void gameInterface::playGame() {
	cout << "Welcome to the Virtual Poker game. " << endl;
	bool running = true;

	while (menuChoice != 9) {
		displayMenu();
		getInput();
		switch (menuChoice)
		{
		case 1: {
			executeMain();
			break;
		}
		case 2: {
			cout << "How many coins would you like to deposit? " << endl;
			getDeposit();
			depositCoins(deposit);
			break;
		}
		case 9: {cout << "Game ending. Thanks for playing!" << endl;
			break;
		}
		}
	}
}

//-------------------------------------------------------------------------------------

// Main function for game
// Initializes a game and plays the game
// Everything else is contained in the classes
int main() {
	srand(time(0));
	gameInterface game;

	game.playGame();
	
	return 0;
}

// This poker program is not perfect.
// There are still a few inconsistencies while drawing a hand. 
// But, the game itself runs well for the most part.