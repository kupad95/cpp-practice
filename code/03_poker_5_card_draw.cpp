#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>
#include <thread>
using namespace std;

enum Suit { Hearts, Diamonds, Clubs, Spades };

class Card {
    public:
        int rank;
        Suit suit;

        Card(int r = 1, Suit s = Suit::Hearts) : rank(r), suit(s) {}

        std::string toString() const {
        std::string rankName = getRankName(rank);
        std::string suitName = getSuitName(suit);
        return rankName + " of " + suitName;
    }
    private:
        std::string getRankName(int rank) const {
        switch (rank) {
            case 1: return "Ace";
            case 2: return "2";
            case 3: return "3";
            case 4: return "4";
            case 5: return "5";
            case 6: return "6";
            case 7: return "7";
            case 8: return "8";
            case 9: return "9";
            case 10: return "10";
            case 11: return "Jack";
            case 12: return "Queen";
            case 13: return "King";
            default: return "Invalid";
            }
        }
        std::string getSuitName(Suit suit) const {
        switch (suit) {
                case Suit::Hearts: return "Hearts";
                case Suit::Diamonds: return "Diamonds";
                case Suit::Spades: return "Spades";
                case Suit::Clubs: return "Clubs";
                default: return "Invalid";
            }
        }
};

class Deck {
    public:
        Deck() {
            for (int r = 1; r <= 13; ++r) {
                for (int s = 0; s < 4; ++s) {
                    cards.push_back(Card(r, static_cast<Suit>(s)));
                }
            }
        }

        void shuffle() {
            // Use a random number generator to shuffle the cards
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(cards.begin(), cards.end(), g);
        }

        Card drawCard() {
            Card drawnCard = cards.back();
            cards.pop_back();
            return drawnCard;
        }

        void printDeck() {
        for (const Card& card : cards) {
            std::cout << card.toString() << std::endl;
        }
    }

    private:
        std::vector<Card> cards;
};

class Communal {
    public:
        std::vector<Card> communalCards;
        int minBet;
        int totalBet;

    Communal() : minBet(0), totalBet(0) {}

    void resetCommunal() {
        communalCards.clear();
        minBet = 10;
        totalBet = 0;
    }
};

class Player {
    public:
    int playerId;
    int chipStack;
    std::string playerName;
    std::vector<Card> hand;

    Player(int id = 0, int chips = 0) : playerId(id), chipStack(chips) {}

    void printHand() const {
        std::cout << playerName << "'s hand:" << std::endl;
        for (const Card& card : hand) {
            std::cout << card.toString() << std::endl;
        }
        std::cout << std::endl;
    }

    // Method to allow the player to bet an integer amount
    bool bet(int amount, Communal& communal) {
        // Check if the bet amount is within the valid range
        if (amount < communal.minBet || amount > chipStack) {
            return false; // Bet amount is invalid
        }

        // Update the player's chipStack
        chipStack -= amount;

        // Update the communal minBet if the bet amount is greater
        if (amount > communal.minBet) {
            communal.minBet = amount;
        }

        // Print the bet amount
        std::cout << playerName << " bets " << amount << std::endl;
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        return true; // Bet successful
    }

    // Method for AI players to make bets
    bool aiBet(Communal& communal) {
        int minPossibleBet = communal.minBet;
        int maxPossibleBet = chipStack;

        // Check if AI can make a bet
        if (minPossibleBet > maxPossibleBet) {
            return false; // AI cannot make a bet
        }

        // Generate a random bet amount within the valid range
        int betAmount = minPossibleBet + rand() % (maxPossibleBet - minPossibleBet + 1);

        // Call the bet method with the generated bet amount
        return bet(betAmount, communal);
    }

    virtual ~Player() {}
};

class UserPlayer : public Player {
public:
    UserPlayer(const std::string& name, int id = 0, int chips = 0) : Player(id, chips) {
        playerName = name; // Set a specific name for the user
    }
};

class AIPlayer : public Player {
    public:
        AIPlayer(int id = 0, int chips = 0) : Player(id, chips) {

        // Set random name for AI player
        static std::vector<std::string> playerNames;
        playerNames.push_back("Andy");
        playerNames.push_back("Bob");
        playerNames.push_back("Charlie");
        playerNames.push_back("Dinesh");
        playerNames.push_back("Erika");
        playerNames.push_back("Frankie");

        if (!playerNames.empty()) {
            int randomIndex = rand() % playerNames.size();
            playerName = playerNames[randomIndex];
            playerNames.erase(playerNames.begin() + randomIndex);
        } else {
            playerName = "NoName";
        }
        }
};

struct PlayerHand {
    std::vector<Card> handCards;
    bool handStatus;
    int potInvested;

    PlayerHand() : handStatus(true), potInvested(0) {}

    void resetHand() {
        handCards.clear();
        handStatus = true;
        potInvested = 0;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int numPlayers = 4;
    std::vector<Player*> players;
    Deck deck;
    PlayerHand playerHands[numPlayers];
    Communal communal;

    cout << "Welcome to Texas Hold'Em Poker." << endl;
    cout << endl;

    string userPlayerName = "";
    cout << "Please enter your name: ";
    cin >> userPlayerName;

    UserPlayer user(userPlayerName, 1, 1000);
    players.push_back(&user);

    // Initialize AI players with 1000 chips
    for (int i = 1; i <= numPlayers; ++i) {
        AIPlayer* ai = new AIPlayer(i, 1000);
        players.push_back(ai);
    }

    // Print the names of all players
    cout << "The players in the game are: ";
    cout << endl;
    for (Player* player : players) {
        cout << player->playerName << " (" << player->chipStack << " chips) ";
        cout << endl;
    }
    cout << endl;

    // ####### Betting rounds and gameplay logic here. ########

    // Shuffle the deck
    deck.shuffle();

    // Deal five cards to each player
    for (Player* player : players) {
        player->hand.push_back(deck.drawCard());
        player->hand.push_back(deck.drawCard());
        player->hand.push_back(deck.drawCard());
        player->hand.push_back(deck.drawCard());
        player->hand.push_back(deck.drawCard());
    }

    // Print the hand of the UserPlayer
    for (Player* player : players) {
        if (UserPlayer* userPlayer = dynamic_cast<UserPlayer*>(player)) {
            userPlayer->printHand();
        }
    }

    while (true) {
    int activePlayers = 0;

    // Prompt the user for a bet amount
    int betAmount;
    std::cout << "Enter your bet amount: ";
    std::cin >> betAmount;

    // Call the bet method on the Player object
    bool betResult = user.bet(betAmount, communal);

    // Check the result of the bet
    if (betResult) {
        std::cout << "Bet successful!" << std::endl;
        std::cout << "Updated chipStack: " << user.chipStack << std::endl;
        std::cout << "Updated minBet: " << communal.minBet << std::endl;
        std::cout << std::endl;
        activePlayers++;
    } else {
        std::cout << "Invalid bet amount." << std::endl;
    }

    // Bets for AI Players
    for (Player* player : players) {
        if (player != &user) { // Exclude the userPlayer
            bool aiBetResult = player->aiBet(communal);

            if (aiBetResult) {
                std::cout << player->playerName << "'s bet successful!" << std::endl;
                std::cout << player->playerName << ": " << player->chipStack << std::endl;
                std::cout << "Updated minBet: " << communal.minBet << std::endl;
                std::cout << std::endl;
                activePlayers++;
            } else {
                std::cout << player->playerName << " cannot make a bet." << std::endl;
            }
        }
    }

    // Check if there are at least two active players
    if (activePlayers < 2) {
        break; // Exit the loop
    }

    }

    return 0;
}
