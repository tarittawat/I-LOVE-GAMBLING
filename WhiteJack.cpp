#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

// Function to get the value of a card
int getCardValue(const string& card) {
    if (card == "A") return 11; 
    if (card == "K" || card == "Q" || card == "J") return 10;
    return stoi(card); // She integer on my strings till I convert 💦💦💦 🍆🍆🍆
}

//Legalize 54 card-deck ☢️☢️☢️
vector<pair<string, string>> initializeDeck() {
    vector<string> cards = {"1","2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    vector<string> suits = {"Hearts", "Diamonds","Clubs","Spades"};
    vector<pair<string, string>> deck;
       
    // 52-deck ☢️☢️☢️
    for(const string& suit : suits) {
        for(const string& card : cards) {
            deck.emplace_back(card, suit);
        }
    }

    // Add Jonkler 
    deck.emplace_back("Joker","Black");
    deck.emplace_back("Joker","Red");
    return deck;
}
 

//Shuffle 💃💃💃💃
   void shuffleDeck(vector<pair<string, string>>& deck){
        static random_device rd;
        static mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
   }

//Function to deal the card
  pair<string,string> dealCard(vector<pair<string,string>>& deck) {
     if (deck.empty()) {
     cout<< "Your deck is currently empty bruh, We gotta reshoofle this shi\n" ;
     deck = initializeDeck();
     shuffleDeck(deck);
  }
    pair<string, string> card = deck.back();
    deck.pop_back();
    return card;
  }

  


// Function to calculate the hand value
int Handvalue(const vector<pair<string, string>>& hand) {
    int value = 0;
    int aceCount = 0;
    for (const auto& card : hand) {
        value += getCardValue(card.first);
        if (card.first == "A") aceCount++; 
    }
    // Still Water + Ace Value + Those who knows
    while (value > 21 && aceCount > 0) {
        value -= 10;
        aceCount--;
    }
    return value;
}

// Function to display a hand
void displayHand(const vector<pair<string,string>>& hand) {
    for (const auto& card : hand) {
        cout << card.first << " of " << card.second << "  " ;
    }
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // SRAND MY LOVE ❤️❤️❤️

    vector<pair<string,string>> deck = initializeDeck();
    shuffleDeck(deck);

    //I like my wallet drippy bruh 👅👅
    int wallet = 100; 
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        cout << "\nYour wallet: $" << wallet << endl;

        // LET'S GO GAMBLING 💸💸💸💸
        int bet;
        do {
            cout << "Enter your bet (1 - " << wallet << "): ";
            cin >> bet;
            if (bet <= 0 || bet > wallet) {
                cout << "Invalid bet amount.\n";
            }
        } while (bet <= 0 || bet > wallet);

        vector<pair<string,string>> playerHand;
        vector<pair<string,string>> dealerHand;

        // Deal initial cards
        playerHand.push_back(dealCard(deck));
        playerHand.push_back(dealCard(deck));
        dealerHand.push_back(dealCard(deck));
        dealerHand.push_back(dealCard(deck));

        // Player's turn
        bool playerTurn = true;
        while (playerTurn) {
            cout << "\nYour hand: ";
            displayHand(playerHand);
            cout << "Your total: " << Handvalue(playerHand) << endl;

            cout << "Dealer's visible card: " << dealerHand[0].first << endl;

            // 99% of gamblers quit before they win it big
            if (Handvalue(playerHand) == 21) {
                cout << "Blackjack! You win!\n";
                wallet += bet;
                break;
            }
            if (Handvalue(playerHand) > 21) {
                cout << "Bust! Dealer wins.\n";
                wallet -= bet;
                break;
            }

            cout << "Do you want to (h)it or (s)tand? ";
            char choice;
            cin >> choice;

            if (choice == 'h' || choice == 'H') {
                playerHand.push_back(dealCard(deck));
            } else if (choice == 's' || choice == 'S') {
                playerTurn = false;
            } else {
                cout << "Invalid choice. Please enter 'h' or 's'.\n";
            }
        }

        if (Handvalue(playerHand) <= 21) {
            // Dealer's turn
            cout << "\nDealer's hand: ";
            displayHand(dealerHand);
           // Dealer must stand on 17
            while (Handvalue(dealerHand) < 17) {
                dealerHand.push_back(dealCard(deck));
                cout << "Dealer hits...\n";
                displayHand(dealerHand);
            }

            int dealerTotal = Handvalue(dealerHand);
            int playerTotal = Handvalue(playerHand);

            cout << "\nFinal Results:\n";
            cout << "Your hand: ";
            displayHand(playerHand);
            cout << "Your total: " << playerTotal << endl;
            cout << "Dealer's hand: ";
            displayHand(dealerHand);
            cout << "Dealer's total: " << dealerTotal << endl;

            if (dealerTotal > 21 || playerTotal > dealerTotal) {
                cout << "You win!\n";
                wallet += bet;
            } else if (playerTotal == dealerTotal) {
                cout << "It's a tie!\n";
            } else {
                cout << "Dealer wins!\n";
                wallet -= bet;
            }
        }

        if (wallet <= 0) {
            cout << "You're out of money! Game over.\n";
            break;
        }

        cout << "Play another round? (y/n): ";
        cin >> playAgain;
    }

    cout << "\nThanks for playing! Your final wallet: $" << wallet << endl;
    return 0;
}
