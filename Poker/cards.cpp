
#include "cards.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>

std::vector<Card> player1Hand;
std::vector<Card> player2Hand;
std::vector<Card> river;
std::vector<Card> deck;
HandValue player1Value = highCard;
HandValue player2Value = highCard;
int playerMoney = 100;
int tableMoney = 0;

std::string valueString(Value value) {
    switch (value) {
    case two:
        return "two";
    case three:
        return "three";
    case four:
        return "four";
    case five:
        return "five";
    case six:
        return "six";
    case seven:
        return "seven";
    case eight:
        return "eight";
    case nine:
        return "nine";
    case ten:
        return "ten";
    case jack:
        return "jack";
    case queen:
        return "queen";
    case king:
        return "king";
    case ace:
        return "ace";
    }
    return "error";
}

std::string colorString(Color shape) {

    switch (shape) {
    case Color(heart):
        return "heart";
    case Color(clubs):
        return "clubs";
    case Color(diamonds):
        return "diamonds";
    case Color(spades):
        return "spades";
    }
    return "error";
}

Card giveCard() {
    Card topCard = deck.at(0);
    deck.erase(deck.begin());
    return topCard;
}

void creatingDeck()
{
    for (int c = 0; c < 4; c++)
    {
        for (int v = 0; v < 13; v++)
        {
            Card card = { Value(v), Color(c) };
            deck.push_back(card);
        }
    }
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device()()));
}

void draw2CardToPlayers() {
    for (int a = 0; a < 2; a++) {
        player1Hand.push_back(giveCard());
        player2Hand.push_back(giveCard());
    }
}

void draw1CardToRiver() {
    river.push_back(giveCard());
}

void displayCards(int a) {
    std::cout << "player money : " << playerMoney << "\n";
    std::cout << "money on the table : " << tableMoney << "\n";
    std::cout << "\nplayer 1 cards : \n";
    for (int i = 0; i < player1Hand.size(); i++) {
        std::cout << player1Hand[i].toString() << " " << "\n";
    }
    if (a == 1)
    {
        std::cout << "\nplayer 2 cards : \n";
        for (int i = 0; i < player2Hand.size(); i++) {
            std::cout << player2Hand[i].toString() << " " << "\n";
        }
    }
    if (river.size() != 0)
    {
    	std::cout << "\nriver cards : \n";
		for (int i = 0; i < river.size(); i++)
		{
			std::cout << river[i].toString() << " " << "\n";
		}
    }
}

void checkCards()
{
    
    for (int i = 0; i < 5; i++)//add the card from the river to the players
    {
        player1Hand.push_back(river.at(0));
        player2Hand.push_back(river.at(0));
        river.erase(river.begin());
    }

    std::cout << "\nplayer 1 : ";
    if (hasStraightFlush(player1Hand))
    {
        std::cout << "Straight Flush\n";
        player1Value = straightFlush;
    }
    else if (hasFourOfKind(player1Hand))
    {
        std::cout << "Four of a Kind\n";
        player1Value = fourOfKind;
    }
    else if (hasFullHouse(player1Hand))
    {
        std::cout << "Full House\n";
        player1Value = fullHouse;
    }
    else if (hasFlush(player1Hand))
    {
        std::cout << "Flush\n";
        player1Value = flush;
    }
    else if (hasStraight(player1Hand))
    {
        std::cout << "Straight\n";
        player1Value = straight;
    }
    else if (hasThreeOfKind(player1Hand))
    {
        std::cout << "Three of a Kind\n";
        player1Value = threeOfKind;
    }
    else if (hasPair(player1Hand) == 2)
    {
	    std::cout << "Two Pair\n";
        player1Value = twoPair;
    }
    else if (hasPair(player1Hand) == 1)
    {
        std::cout << "Pair\n";
    	player1Value = pair;
    }
    else
    {
        std::cout << "high card\n";
        player1Value = highCard;
    }

    std::cout << "\nplayer 2 : ";
    if (hasStraightFlush(player2Hand))
    {
        std::cout << "Straight Flush\n";
        player2Value = straightFlush;
    }
    else if (hasFourOfKind(player2Hand))
    {
        std::cout << "Four of a Kind\n";
        player2Value = fourOfKind;
    }
    else if (hasFullHouse(player2Hand))
    {
        std::cout << "Full House\n";
        player2Value = fullHouse;
    }
    else if (hasFlush(player2Hand))
    {
        std::cout << "Flush\n";
        player2Value = flush;
    }
    else if (hasStraight(player2Hand))
    {
        std::cout << "Straight\n";
        player2Value = straight;
    }
    else if (hasThreeOfKind(player2Hand))
    {
        std::cout << "Three of a Kind\n";
        player2Value = threeOfKind;
    }
    else if (hasPair(player2Hand) == 2)
    {
        std::cout << "Two Pair\n";
        player2Value = twoPair;
    }
    else if (hasPair(player2Hand) == 1)
    {
        std::cout << "Pair\n";
        player2Value = pair;
    }
    else
    {
        std::cout << "high card\n";
        player2Value = highCard;
    }
}


std::map<Value, int>RankOcurence(const std::vector<Card>& hand)
{
    std::map<Value, int>result;
    for (auto i : hand)
    {
	    if (result.find(i.value) == result.end())
	    {
            result[i.value] = 1;
	    }
        else
        {
            result[i.value]++;
        }
    }
    return result;
}
std::map<Color, int>SuitOcurence(const std::vector<Card>& hand)
{
    std::map<Color, int>result;
    for (auto i : hand)
    {
        if (result.find(i.color) == result.end())
        {
            result[i.color] = 1;
        }
        else
        {
            result[i.color]++;
        }
    }
    return result;
}

bool hasThreeOfKind(const std::vector<Card>& hand)
{
    const std::map<Value, int>occurence = RankOcurence(hand);

    for (std::pair < Value, int> p : occurence)
    {
        if (p.second == 3)
        {
            return true;
        }
    }
    return false;
}
bool hasStraight(std::vector<Card>& hand)
{
    std::sort(hand.begin(), hand.end(), [](Card x, Card y) { return x.value < y.value; });

    int suite = 1;

    for (size_t i = 0; i < hand.size() - 1; i++) {
        if (hand[i + 1].value == hand[i].value + 1) {
            suite++;
            if (suite == 5) {
                return true;
            }
        }
        else {
            suite = 1;
        }
    }
    return false;
}
bool hasFourOfKind(const std::vector<Card>& hand)
{
    const std::map<Value, int>occurence = RankOcurence(hand);

    for (std::pair < Value, int> p : occurence)
    {
        if (p.second == 4)
        {
            return true;
        }
    }
    return false;
}
int hasPair(const std::vector<Card>& hand)
{
    const std::map<Value, int>occurence = RankOcurence(hand);

    for (std::pair < Value, int> p : occurence)
    {
        if (p.second == 2)
        {
	        std::pair<Value, int> u = p;
            for (std::pair < Value, int> p : occurence)
            {
                if (p != u) 
                {
                    if (p.second == 2)
                    {
                        return 2;
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}
bool hasFullHouse(const std::vector<Card>& hand)
{
    const std::map<Value, int>occurence = RankOcurence(hand);

    for (std::pair < Value, int> p : occurence)
    {
        if (p.second == 3)
        {
            std::pair<Value, int> u = p;
            for (std::pair < Value, int> p : occurence)
            {
                if (p != u)
                {
                    if (p.second == 2)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}//triple plus pair
bool hasFlush(const std::vector<Card>& hand)
{
    const std::map<Color, int>occurence = SuitOcurence(hand);

    for (std::pair < Color, int> p : occurence)
    {
        if (p.second == 5)
        {
            return true;
        }
    }
    return false;
}
bool hasStraightFlush(std::vector<Card>& hand)
{
    std::sort(hand.begin(), hand.end(), [](Card x, Card y) { return x.value < y.value; });
    std::vector<Card> handS;
    int suite = 1;

    for (size_t i = 0; i < hand.size() - 1; i++) {
        if (hand[i + 1].value == hand[i].value + 1) {
            suite++;
            handS.push_back(hand[i]);
            if (suite == 5) {
                const std::map<Color, int>occurence = SuitOcurence(handS);
                for (std::pair < Color, int> p : occurence)
                {
                    if (p.second == 5)
                    {
                        return true;
                    }
                }
            }
        }
        else {
            suite = 1;
            handS.clear();
        }
    }
    return false;
}

void resetHands()
{
    player1Hand.clear();
    player2Hand.clear();
    river.clear();
}

void bet()
{
    int moneyBet;
    std::cout << "how much do you want to bet ?\n";
    do
    {
    	std::cin >> moneyBet;
        if(moneyBet<playerMoney+1)
        {
	        break;
        }
        std::cout << "you don't have enough money\n";
    }
    while (true);
    playerMoney = playerMoney - moneyBet;
    tableMoney = tableMoney + moneyBet;
    system("cls");
}

void resultBet()
{
    if (player1Value > player2Value)
    {
        std::cout << "player 1 win\n";
        playerMoney = playerMoney + tableMoney * 2;
        tableMoney = 0;
    }
    else if (player1Value < player2Value)
    {
        std::cout << "player 2 win\n";
        tableMoney = 0;
    }
    else
    {
        std::cout << "split\n";
        playerMoney = playerMoney + tableMoney;
        tableMoney = 0;
    }
}