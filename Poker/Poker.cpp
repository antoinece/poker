// Poker.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include "cards.h"


int main()
{
    bool replay = true;
    do
    {
	    creatingDeck();

    	draw2CardToPlayers();
    	std::cout << "round 1 :\n";
    	displayCards(0);
        bet();
    	draw1CardToRiver();
    	draw1CardToRiver();
    	draw1CardToRiver();
    	std::cout << "\nround 2 :\n";
    	displayCards(0);
        bet();
    	draw1CardToRiver();
    	std::cout << "\nround 3 :\n";
    	displayCards(0);
        bet();
    	draw1CardToRiver();
    	std::cout << "\nfinal round :\n";
    	displayCards(1);

        checkCards();
        resultBet();

        char play;
    	std::cout << "\ndo you want to keep continue playing \ntype 'n' for no or 'y' for yes\n";
    	std::cin >> play;
        system("cls");
        if (play == 'n')
        {
            replay = false;
        }
        else
        {
            resetHands();
        }
        if (playerMoney == 0)
        {
            std::cout << "you loose \n";
            break;
        }
    } while (replay == true);
	std::cout << "your money : " << playerMoney;
    std::cout << "\nthanks for playing\n";
}
//std::map to compare