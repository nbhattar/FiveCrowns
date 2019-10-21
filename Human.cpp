//
// Created by nbhat on 9/15/2019.
//

#include "Human.h"
#include "DiscardPile.h"
#include "DrawPile.h"


void Human::play() {
    // Note: This is UI code
	cout << " I am human " << endl;
	cout << " My name is " << *(this->name) << endl;
    showDrawAndDiscardPile();
    showHand();
    int option;
    cout << "1. Save the game" << endl;
    cout << "2. Make a move" << endl;
    cout << "3. Ask for help" << endl;
    cout << "4. Quit the game" << endl;

    cout << "Enter option : " ;
    cin >> option;

    switch (option){
        case 1:
            cout << "Saving the game" << endl;
            break;
        case 2:
            askToChooseCardFromDrawPileOrDiscardPile();
            break;
        case 3:
            cout << "Asking for help" << endl;
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            exit(EXIT_FAILURE); // might need to change this later

    }

}
bool Human::playGame() {
	// Note: This is UI code
	cout << " I am human " << endl;
	cout << " My name is " << *(this->name) << endl;
	showDrawAndDiscardPile();
	showHand();
	int option;
	cout << "1. Save the game" << endl;
	cout << "2. Make a move" << endl;
	cout << "3. Ask for help" << endl;
	cout << "4. Quit the game" << endl;

	cout << "Enter option : ";
	cin >> option;

	switch (option) {
	case 1: {
		cout << "Saving the game" << endl;
		exit(EXIT_SUCCESS);
	}
		  break;
	case 2: {
		bool flag = moveHelper(); // flag true means user wants to go out
		if (flag) return true;
	}
		break;
	case 3: {
		cout << "Asking for help" << endl;
	}
		break;
	case 4: {
		exit(EXIT_SUCCESS);
	}
		  break;
	default:
		exit(EXIT_FAILURE); // might need to change this later

	}
}

bool Human::moveHelper() {
	int option;
	cout << "1. Get card from DrawPile" << endl;
	cout << "2. Get card from DiscardPile" << endl;
	cout << "3. Go out " << endl;

	do {
		cin.clear();
		cin.ignore(numeric_limits < streamsize>::max(), '\n');
		cout << "Enter option (e.g 1) : ";
		cin >> option;
	} while ((option <= 0) || (option >= 4));
	switch (option) {
	case 1:
		hand->addFront(DrawPile::getInstance()->popFront());
		break;
	case 2:
		hand->addFront(DiscardPile::getInstance()->popFront());
		break;
	case 3:
		return true;
	default:
		break; // need to change this later
	}
	showDrawAndDiscardPile();
	showHand();

	// if hastoGoOUt is set false then show this option
	// otherwise show throw card and go out


	cout << "1. Throw card" << endl;
	cout << "2. Throw card and Go Out " << endl;
	do {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Selection options (e.g 1 or 2) : ";
		cin >> option;

	} while ((option <= 0) || (option >= 3));

	switch (option) {
	case 1:
		throwCardAtIndex();
		break;
	case 2:
		throwCardAtIndex();
		return true;
	default:
		exit(EXIT_FAILURE);
	}
}


void Human::askToChooseCardFromDrawPileOrDiscardPile() {

    int option;
    cout << "1. Get card from DrawPile" << endl;
    cout << "2. Get card from DiscardPile" << endl;
	cout << "3. Go out " << endl;
	
	do {
		cin.clear();
		cin.ignore(numeric_limits < streamsize>::max(), '\n');
		cout << "Enter option (e.g 1) : ";
		cin >> option;
	} while ((option <= 0) || (option >= 4));
    switch (option){
        case 1:
            hand->addFront(DrawPile::getInstance()->popFront());
            break;
        case 2:
            hand->addFront(DiscardPile::getInstance()->popFront());
            break;
		case 3:
			if (!goOut()) {
				askToChooseCardFromDrawPileOrDiscardPile();
			}
			return;
        default:
            break; // need to change this later
    }
    showDrawAndDiscardPile();
    showHand();

	// if hastoGoOUt is set false then show this option
	// otherwise show throw card and go out

	
	cout << "1. Throw card" << endl;
	cout << "2. Throw card and Go Out " << endl;
	do {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Selection options (e.g 1 or 2) : ";
		cin >> option;
		
	} while ((option <= 0) || (option >= 3));

	switch (option) {
	case 1:
		throwCard();
		break;
	case 2:
		throwCard();
		goOut();
		break;
	default:
		exit(EXIT_FAILURE);
	}
	

}
bool Human::goOut() {
	int score;
	vector<vector<CardInterface*>> cardsArgmnt;
	bool wasGoOutSuccessful = iGoOut->tryGoOut(hand, score, cardsArgmnt);
	cout << "was Go out successful : " << wasGoOutSuccessful << endl;
	if (wasGoOutSuccessful) {
		this->score = score;
		cout << "Score : " << score << endl;
		cout << "Cards Arrangement : ";
		printCardsArrgmnt(cardsArgmnt);
		cout << endl;
		return true;
	}
	else {
		cout << "Going out not possible " << endl;
		return false;
	}
}

void Human::throwCard() {
	bool flag = false;
	while (true) {
		cin.clear();
		cin.ignore();
		string card;
		cout << "1. Enter the card that you want to throw: " << endl;
		
		getline(cin, card); // validate input here 
		// since if card is empty match function will throw error
		for (int i = 0; i < hand->getSize(); i++) {
			if (hand->getCardAt(i)->match(card)) {
				DiscardPile::getInstance()->addFront(hand->popCardAt(i));
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
}
void Human::throwCardAtIndex() {
	int index = -1;
	do {
		cin.clear();
		cin.ignore();
		
		cout << "1. Enter the index of card that you want to throw: " << endl;

		cin >> index;
	} while (index<0 && index>=hand->getSize());
	DiscardPile::getInstance()->addFront(hand->popCardAt(index));
}

