#include <stdlib.h>
#include <stdio.h>
#include <set>
#include "tchar.h"
const int ARRAY_SIZE = 52;
class Card {
public:
    Card() {}
    void SetCardName(const char* cardName) {
        mCardName = (char*) malloc(strlen(cardName));
        mCardName = cardName;
    }
    const char* const GetCardName() const {
        return mCardName;
    }
    ~Card() {}
private:
    const char* mCardName;
};

const char *CardList[] = {"AD", "KD", "QD", "JD", "10D", "9D", "8D", "7D", "6D", "5D",
"4D", "3D", "2D","AH", "KH", "QH", "JH", "10H", "9H", "8H", "7H", "6H", "5H",
"4H", "3H", "2H","AS", "KS", "QS", "JS", "10S", "9S", "8S", "7S", "6S", "5S",
"4S", "3S", "2S", "JK", "AC", "KC", "QC", "JC", "10C", "9C", "8C", "7C", "6C",
"5C", "4C", "3C", "2C"};

Card StartingCardList[ARRAY_SIZE];
Card EndingCardList[ARRAY_SIZE];
void PrintCardList(Card* cardslist);
int _tmain(int argc, _TCHAR* argv[]) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        StartingCardList[i].SetCardName(CardList[i]);
    }

    std::set<size_t> usedIndices;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        size_t t;
        do {
            t = rand() % 52;

        } while (usedIndices.find(t) != usedIndices.end());
        usedIndices.emplace(t);
        EndingCardList[i].SetCardName(CardList[t]);
    }
    PrintCardList(StartingCardList);
    printf("\n");
    PrintCardList(EndingCardList);
    //Print the new shuffled array HERE!
    return 0;
}
void PrintCardList(Card* cardslist) {
    printf("CardList\n");
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        printf(cardslist[i].GetCardName());
        printf("\n");
    }
}