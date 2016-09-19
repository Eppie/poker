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

//#define DEBUG_OUT(x) cout << x << endl
#define DEBUG_OUT(x)

using namespace std;

enum class Suit : int {
	spades,
	clubs,
	diamonds,
	hearts,
	First = spades,
	Last = hearts
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
	static vector<string> suitMap = { "♠", "♣", "♦", "♥" };
	static vector<string> rankMap = { "Jack", "Queen", "King", "Ace" };
	int rank = static_cast<int>( card.getRank() ) + 2;
	int suit = static_cast<int>( card.getSuit() );

	if( rank > 10 ) {
		os << rankMap[rank - 11];
	} else {
		os << rank;
	}

	os << suitMap[suit];
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

bool hasStraight( vector<int> counts ) {
	for( int i = 0; i <= 8; ++i ) {
		if( counts[i] == 1 && counts[i + 1] == 1 && counts[i + 2] == 1 && counts[i + 3] == 1 && counts[i + 4] == 1 ) {
			return true;
		}
	}

	return false;
}

bool hasRoyalFlush( vector<Card> cards, vector<int> counts ) {
	if( !hasFlush( cards ) ) {
		return false;
	}

	if( counts[8] == 1 && counts[9] == 1 && counts[10] == 1 && counts[11] == 1 && counts[12] == 1 ) {
		return true;
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

int score( vector<Card> hand ) {
	int result = 0;
	auto counts = rankCounts( hand );

	// Count the number of pairs, three of a kind, etc. E.g. if there are two pairs, countsHist[2] == 2.
	vector<int> countsHist( 5, 0 );

	for( auto && count : counts ) {
		countsHist[count]++;
	}

	int baseScore = getBaseScore( counts );
	bool flush = hasFlush( hand );
	bool straight = hasStraight( counts );

	// royal flush
	if( hasRoyalFlush( hand, counts ) ) {
		DEBUG_OUT( "Royal Flush" );
		result = 9;
	} else if( straight && flush ) { // straight flush
		DEBUG_OUT( "Straight Flush" );
		result = 8;
	} else if( countsHist[4] == 1 ) { // four of a kind
		DEBUG_OUT( "Four of a Kind" );
		result = 7;
	} else if( countsHist[3] == 1 && countsHist[2] == 1 ) { // full house
		DEBUG_OUT( "Full House" );
		result = 6;
	} else if( flush ) { // flush
		DEBUG_OUT( "Flush" );
		result = 5;
	} else if( straight ) { // straight
		DEBUG_OUT( "Straight" );
		result = 4;
	} else if( countsHist[3] == 1 ) { // three of a kind
		DEBUG_OUT( "Three of a Kind" );
		result = 3;
	} else if( countsHist[2] == 2 ) { // two pairs
		DEBUG_OUT( "Two Pairs" );
		result = 2;
	} else if( countsHist[2] == 1 ) { // one pair
		DEBUG_OUT( "Pair" );
		result = 1;
	}

	return result << 20 | baseScore;
}
