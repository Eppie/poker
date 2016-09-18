/*
 * =====================================================================================
 *
 *       Filename:  card.hpp
 *
 *    Description:  Class to represent a card
 *
 *        Version:  1.0
 *        Created:  09/17/2016 06:26:34 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Andrew Epstein
 *
 * =====================================================================================
 */

#pragma once

#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

enum class Suit : int {
	spades,
	clubs,
	diamonds,
	hearts
};

enum class Rank : int {
	two,
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
	ace
};

class Card {
private:
	Suit suit;
	Rank rank;
public:
	Card( Suit suit, Rank rank ) : suit( suit ), rank( rank ) {}

	Suit getSuit() const {
		return suit;
	};

	Rank getRank() const {
		return rank;
	};

	bool operator==( const Card &other ) const {
		return suit == other.suit && rank == other.rank;
	}

	bool operator<( const Card &other ) const {
		return rank < other.rank;
	}
};

ostream &operator<<( ostream &os, const Card &card ) {
	os << static_cast<int>( card.getRank() ) << static_cast<int>( card.getSuit() );
	return os;
}

bool allSameSuit( const vector<Card> &cards ) {
	auto firstSuit = cards[0].getSuit();

	for( auto && card : cards ) {
		if( firstSuit != card.getSuit() ) {
			return false;
		}
	}

	return true;
}

bool allSameRank( const vector<Card> &cards ) {
	auto firstRank = cards[0].getRank();

	for( auto && card : cards ) {
		if( firstRank != card.getRank() ) {
			return false;
		}
	}

	return true;
}

bool hasFlush( const vector<Card> &cards ) {
	if( cards.size() < 5 ) {
		return false;
	} else if( cards.size() == 5 ) {
		return allSameSuit( cards );
	} else {
		cout << "hand has more than 5 cards!!!" << endl;
		return false;
	}
}

vector<int> rankCounts( vector<Card> cards ) {
	vector<int> counts( 13, 0 );

	for( auto && card : cards ) {
		counts[static_cast<int>( card.getRank() )]++;
	}

	return counts;
}

int hasStraight( vector<int> counts ) {
	for( int i = 0; i <= 8; ++i ) {
		if( counts[i] == 1 && counts[i + 1] == 1 && counts[i + 2] == 1 && counts[i + 3] == 1 && counts[i + 4] == 1 ) {
			return true;
		}
	}

	return false;
}

int getBaseScore( vector<int> ranks ) {
	int result = 0;

	// Iterate from more occurrences to fewer (four of a kind, three of a kind, pair, etc)
	for( int i = 4; i > 0; --i ) {
		// Iterate from ace down to two
		for( int j = 12; j >= 0; --j ) {
			// If there are i occurrences of card with rank j in the hand
			if( ranks[j] == i ) {
				// Shift j into the lower 4 bits i times.
				for( int k = 0; k < i; ++k ) {
					result = result << 4 | j;
				}
			}
		}
	}

	return result;
}
