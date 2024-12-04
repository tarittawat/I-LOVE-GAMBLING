#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// She classes my privates till I get ignored
class CardCounter {
private:
    int runningCount; 
    int totalCards;   
    int decksRemaining; 

public:
    CardCounter(int decks) : runningCount(0), totalCards(0), decksRemaining(decks) {}

    // Updates the running count based on card value
    void updateCount(const string& card) {
        if (card == "2" || card == "3" || card == "4" || card == "5" || card == "6") {
            runningCount++;
        } else if (card == "10" || card == "J" || card == "Q" || card == "K" || card == "A") {
            runningCount--;
        }
        totalCards++;
        updateDecksRemaining();
    }

    // Estimates remaining decks based on total cards seen
    void updateDecksRemaining() {
        decksRemaining = 6 - (totalCards / 52); 
    }

    // Returns the current running count
    int getRunningCount() const {
        return runningCount;
    }

    // Calculates and returns the true count
    double getTrueCount() const {
        return (decksRemaining > 0) ? static_cast<double>(runningCount) / decksRemaining : runningCount;
    }
};

// Main 
int main() {
    cout << "Welcome to the Card Counter!\n";
    cout << "Enter the number of decks in play: ";
    int decks;
    cin >> decks;

    CardCounter counter(decks);

    cout << "\nEnter cards as they appear (e.g., 2, 10, J, Q, K, A).\n";
    cout << "Type 'end' to stop the program.\n";

    string card;
    while (true) {
        cout << "Enter card: ";
        cin >> card;

        if (card == "end") {
            break;
        }

        if (card == "2" || card == "3" || card == "4" || card == "5" || card == "6" || 
            card == "7" || card == "8" || card == "9" || card == "10" || 
            card == "J" || card == "Q" || card == "K" || card == "A") {
            counter.updateCount(card);
            cout << "Running Count: " << counter.getRunningCount() << "\n";
            cout << "True Count: " << fixed << setprecision(2) << counter.getTrueCount() << "\n";
        } else {
            cout << "Invalid card input. Try again.\n";
        }
    }

    cout << "\nFinal Running Count: " << counter.getRunningCount() << "\n";
    cout << "Final True Count: " << fixed << setprecision(2) << counter.getTrueCount() << "\n";
    cout << "Thank you for using the Card Counter. Good luck!\n";

    return 0;
}
