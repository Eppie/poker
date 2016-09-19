/*
 * =====================================================================================
 *
 *       Filename:  poker.cpp
 *
 *    Description:  Calculating poker odds
 *
 *        Version:  1.0
 *        Created:  09/17/2016 06:20:09 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Andrew Epstein
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "card.hpp"

using namespace std;

vector<Card> generateDeck() {
	vector<Card> deck;

	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 13; ++j ) {
			deck.push_back( Card( static_cast<Suit>( i ), static_cast<Rank>( j ) ) );
		}
	}

	return deck;
}

// find next k-combination
void next_combination( uint64_t &x ) {
	uint64_t u = x & -x;
	uint64_t v = u + x;

	x = v + ( ( ( v ^ x ) / u ) >> 2 );
}

int main() {
	srand( unsigned( time( 0 ) ) );

	auto deck = generateDeck();
	//random_shuffle( deck.begin(), deck.end() );

	//int i = 0;
	//vector<Card> hand = { deck[i], deck[i + 1], deck[i + 2], deck[i + 3], deck[i + 4] };

	vector<Card> hand;
	hand.push_back( deck.back() );
	deck.pop_back();
	hand.push_back( deck.back() );
	deck.pop_back();

	//int deckScore = score( hand );

	//cout << deckScore << endl;

	//for( auto && card : hand ) {
		//cout << card << endl;
	//}

	vector<Card> newHand = hand;

	int n = 50; // number of cards remaining in deck
	int k = 3; // number of cards to draw from deck

	uint64_t x = ( 1 << k ) - 1;
	uint8_t idx[k];
	int best = 0;

	while( x <= 4362862139015168 ) {
		uint64_t m = x;
		uint8_t *dst = idx;

		for( int i = 0; i < n; ++i ) {
			*dst = i;
			dst += m & 1;
			m >>= 1;
		}

		for( int i = 0; i < k; ++i ) {
			newHand.push_back( deck[idx[i]] );
		}

		int deckScore = score( newHand );
		
		if( deckScore > best ) {
			for( auto && card : newHand ) {
				cout << card << ", ";
			}

			best = deckScore;
			cout << deckScore << endl;
		}
		next_combination( x );
		newHand = hand;
	}

	return 0;
}

