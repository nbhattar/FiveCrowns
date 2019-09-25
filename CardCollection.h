//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARDCOLLECTION_H
#define FIVECROWNS_CARDCOLLECTION_H

#include <vector>
#include "CardInterface.h"
#include <algorithm>
#include <iostream>

class CardCollection{

public:

    void addFront(CardInterface* card){
        this->collection.insert(collection.begin(), card);
    }



    void addBack(CardInterface* card) {
        this->collection.insert(collection.end(), card);
    }
    CardInterface* getFront(){
        return *collection.begin();
    }

    CardInterface* getBack(){
        return *(collection.begin() + collection.size());
    }

    CardInterface* popFront(){

//        CardInterface * card = *collection.begin();
//        collection.erase(collection.begin());
//        return card;

    CardInterface* card = *(collection.begin());
    collection.erase(collection.begin());

    return card;
    }
    CardInterface * popBack(){
        CardInterface * card = *(collection.begin() + collection.size());
        collection.erase(collection.begin()+ collection.size());
        return card;
    }

    bool isEmpty(){
        return collection.empty() || false;
    }
    int getSize(){
        return collection.size();
    }
    CardInterface*  getCardAt(int position){
        return collection[position];
    }

    CardInterface* popCardAt(int position){
        CardInterface* card = *(collection.begin() + position);
        collection.erase(collection.begin() + position);
        return card;
    }

    CardInterface* popCard(CardInterface * card){
        for (int i=0;i<collection.size();i++){
            if (collection[i] == card){
                CardInterface * temp = collection[i];
                collection.erase(collection.begin() + i);
                return temp;
            }
        }
    }

    void shuffle(){
        std::random_shuffle(collection.begin(), collection.end());
    }



    void collect(CardCollection* cardCollection){
        int size = cardCollection->getSize(); // !!! important to put cardcollection size in a variable otherwise will get error
        for (int i=0;i<size;i++){
            collection.push_back(cardCollection->popFront());
        }
    }
    void transformCards(string face, string wildcard){
        // since Joker is of suit J and has 1 2 3 . Conflicts with regular 3 card. So have to check. Can make Joker start at 0 1 and 2 for easy purposes
        for (auto card: this->collection){
            if (card->getFace() == face && card->getSuit()!="J") card->setFace(wildcard);
        }
    }

    string toString(){
        string output;
        for (auto card: collection){
            output += card->toString() + " ";
            // cout << card->toString() << " ";
        }
        // cout << endl;
        // cout << output;
        return output;
    }
private:
    vector <CardInterface* > collection;
};


#endif //FIVECROWNS_CARDCOLLECTION_H

/*
 * This is a discussion thread
 *
 * How does deck differ from draw pile discard pile and hand?
 * Deck is a class that builds a set or collection of cards. With the help of deck builder, of course.
 * Draw Pile, Discard Pile and hand cannot build cards.
 * Plus, draw pile, discard pile and hand are singleton classes.
 *
 * This card might not have any pure virtual functions. That means this class is not abstract class.
 *
 * Since, this class keeps card interface pointer it cannot return object of class blah type
 *
 * Why do we need virtual shuffle?
 * No, we don't.
 * Because all class implement shuffle functionality why not just declare it once here.
 *
 *
 * Why do we need to give child classes access to fill their own collection?
 * No, we don't;
 * We can set it right here
 *
 * Adding card
 * Add card to the front of the collection :-  addFront
 *
 * Add card to back of the collection :- addBack
 * Add card to certain position */