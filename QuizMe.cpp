#include "QuizMe.h"
#include <iostream>
#include <fstream>
using namespace std;

QuizMe::QuizMe() {

    head = NULL;
    current = NULL;

}

QuizMe::~QuizMe() {


}

void QuizMe::buildSample() {

    string sampleKey = "What is the meaning of life?";
    string sampleDefinition = "42";

    FlashCard *card = new FlashCard;
    card -> key = sampleKey;
    card -> definition = sampleDefinition;
    card -> next = NULL;
    head = card;

}

void QuizMe::addCard(string key, string definition) {

    current = head;

    if(current != NULL) {

        while(current -> next != NULL) {

            current = current -> next;

        }

    }

    FlashCard *card = new FlashCard;
    card -> key = key;
    card -> definition = definition;
    card -> next = NULL;
    current -> next = card;
    card -> previous = current;

}

void QuizMe::printAll() {

    current = head;

    while(current != NULL) {

        cout << current -> key << " " << current -> definition << endl;
        current = current -> next;

    }

}

void QuizMe::uploadCards() {

    current = head -> next;

    ofstream file;
    file.open ("quizcards.txt");

    while(current != NULL) {

        file << current -> key;
        file << ",";
        file << current -> definition << "\n";
        current = current -> next;

    }

    file.close();

}

void QuizMe::deleteCard(string key) {

	bool found = false;
	FlashCard *del = new FlashCard;
	FlashCard *search = new FlashCard;
	search = head;

	// find the flashCard to delete
	while (!found && search != NULL) {
		if (search->key == key) {
			found = true;
		}
		else {
			search = search->next;
		}
	}

	if (found) {
		// if the deleted node is a head
		if (search == head) {
			del = head;
			head = head->next;
			head->previous = NULL;
			delete del;
		}
		// if the deleted node is a head
		else if (search->next == NULL) {
			search->previous->next = NULL;
			delete search;
		}
		// otherwise just rearrange the pointers.
		else {
			search->previous->next = search->next;
			search->next->previous = search->previous;
			delete search;
		}
	}
	else {
		cout << "The card: " << key << " does not exist" << endl;
	}
}

void QuizMe::deleteAll() {

	FlashCard *temp = new FlashCard;

	while(head != NULL) {

		temp = head;
		head = head->next;
		cout << "Deleting card: " << temp->key << endl;
		delete temp;

	}

    ofstream ofs;
    ofs.open("quizcards.txt", ofstream::out | ofstream::trunc);
    ofs.close();

}

void QuizMe::quiz() {

    current = head;
    int right = 0;
    int wrong = 0;

    while(current != NULL) {

        string answer = "";
        cout << current -> key << endl;
        cin.ignore();
        getline(cin, answer);

        if(answer != current -> definition) {

            cout << "WRONG ANSWER!" << endl;
            wrong++;

        } else {

            cout << "CORRECT!" << endl;
            right++;

        }

        current = current -> next;

    }

    cout << "You got " << right << " right and " << wrong << " wrong." << endl;

}
