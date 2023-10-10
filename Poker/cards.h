#pragma once
#include <map>
#include <string>
#include <vector>


enum Value
{
    two = 0,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace = 12,
};
enum Color
{
    heart = 0,
    clubs,
    diamonds,
    spades,
};
enum HandValue
{
    highCard,
    pair,
    twoPair,
    threeOfKind,
    straight,
    flush,
    fullHouse,
    fourOfKind,
    straightFlush
};

std::string valueString(Value value);
std::string colorString(Color shape);

struct Card
{
    Value value;
    Color color;
    std::string toString()
    {
        return valueString(value) + " of " + colorString(color);
    }
};

extern std::vector<Card> player1Hand;
extern std::vector<Card> player2Hand;
extern std::vector<Card> river;
extern std::vector<Card> deck;
extern HandValue player1Value;
extern HandValue player2Value;
extern int playerMoney;
extern int tableMoney;

Card giveCard();
void creatingDeck();
void draw2CardToPlayers();
void draw1CardToRiver();
void displayCards(int);
void checkCards();
void resetHands();
void bet();
void resultBet();

std::map<Value, int>RankOcurence(const std::vector<Card>& hand);
std::map<Color, int>SuitOcurence(const std::vector<Card>& hand);


int hasPair(const std::vector<Card>& hand);
bool hasThreeOfKind(const std::vector<Card>& hand);
bool hasStraight(std::vector<Card>& hand);
bool hasFlush(const std::vector<Card>& hand);
bool hasFullHouse(const std::vector<Card>& hand);
bool hasFourOfKind(const std::vector<Card>& hand);
bool hasStraightFlush(std::vector<Card>& hand);