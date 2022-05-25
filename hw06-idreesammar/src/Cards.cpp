#include "Cards.h"

#include <random>
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(ITPVector<Card>& deck)
{
	// first add five cards to your hand (mHand)
	for (int i = 0; i < 5; i++)
	{
		Card c = deck.back(); // the card to be added is at the top (back) of the deck
		mHand.push_back(c); // now add the card to your hand
		deck.pop_back(); // will remove this card from the deck vector
	}

	// now sort your hand
	sortHand(); // will do selection sort on your hand
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
	std::string bestHand = ""; // will describe best type of hand the player has

	// return the best type of hand player has
	if (hasStraight() && hasFlush())	// straight flush
	{
		bestHand = "straight flush";
	}
	else if (hasFourOfAKind())		// four of a kind
	{
		bestHand = "four of a kind";
	}
	else if (hasFullHouse())			// full house
	{
		bestHand = "full house";
	}
	else if (hasFlush())				// flush
	{
		bestHand = "flush";
	}
	else if (hasStraight())			// straight
	{
		bestHand = "straight";
	}
	else if (hasThreeOfAKind())		// three of a kind
	{
		bestHand = "three of a kind";
	}
	else if (hasTwoPairs())			// two pairs
	{
		bestHand = "two pairs";
	}
	else if (hasPair())				// one pair
	{
		bestHand = "pair";
	}
	else							// high card (if nothing else above)
	{
		bestHand = "high card";
	}

	return bestHand;
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
	bool hasStraight = false; // boolean outcome of the function
	int straightCounter = 0; // how many times current card rank is one less than next card rank (needs to be 4 to have a straight)

	// need to check and see if each subsequent card is one rank greater than the card before it
	for (int i = 0; i < mHand.size() - 1; i++)  // loop should only iterate 4 times
	{
		if (mHand[i].mRank == mHand[i + 1].mRank - 1)
		{
			straightCounter++;  // add one count since current card rank is one less than next card rank
		}
	}

	// now check if counter = 4
	if (straightCounter == 4)
	{
		hasStraight = true;
	}

	return hasStraight;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
	bool hasFlush = false; // boolean outcome of the function
	int matchCounter = 0; // holds number of card suits that match

	// need to check if suit of each card is the same
	for (int i = 0; i < mHand.size() - 1; i++) // will iterate 4 times
	{
		if (mHand[i].mSuit == mHand[i + 1].mSuit)
		{
			matchCounter++;  // add one since current 2 consecutive cards have same suit
		}
	}

	// check if all cards had same suit (counter = 4)
	if (matchCounter == 4)
	{
		hasFlush = true;
	}

	return hasFlush;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
	bool hasFourKind; // bool outcome of function

	// first check first 4 cards
	if ((mHand[0].mRank == mHand[1].mRank) && (mHand[1].mRank == mHand[2].mRank) && (mHand[2].mRank == mHand[3].mRank))
	{
		hasFourKind = true;
	}
	// else check last 4 cards
	else if ((mHand[1].mRank == mHand[2].mRank) && (mHand[2].mRank == mHand[3].mRank) && (mHand[3].mRank == mHand[4].mRank))
	{
		hasFourKind = true;
	}
	// otherwise no 4 of a kind
	else
	{
		hasFourKind = false;
	}

	return hasFourKind;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
	bool hasFullHouse; // bool outcome of function

	// first check first 3 cards and last 2 cards (e.g. xxxyy)
	if ((mHand[0].mRank == mHand[1].mRank) && (mHand[1].mRank == mHand[2].mRank) && (mHand[3].mRank == mHand[4].mRank))
	{
		hasFullHouse = true;
	}
	// else check first 2 cards and last 3 cards (e.g. xxyyy)
	else if ((mHand[0].mRank == mHand[1].mRank) && (mHand[2].mRank == mHand[3].mRank) && (mHand[3].mRank == mHand[4].mRank))
	{
		hasFullHouse = true;
	}
	// otherwise no full house 
	else
	{
		hasFullHouse = false;
	}

	return hasFullHouse;
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
	bool has3Kind; // bool outcome of function

	// first check xxxyz
	if ((mHand[0].mRank == mHand[1].mRank) && (mHand[1].mRank == mHand[2].mRank) && (mHand[3].mRank != mHand[4].mRank))
	{
		has3Kind = true;
	}
	// else check xyyyz
	else if ((mHand[1].mRank == mHand[2].mRank) && (mHand[2].mRank == mHand[3].mRank) && (mHand[0].mRank != mHand[4].mRank))
	{
		has3Kind = true;
	}
	// else check xyzzz
	else if ((mHand[2].mRank == mHand[3].mRank) && (mHand[3].mRank == mHand[4].mRank) && (mHand[0].mRank != mHand[1].mRank))
	{
		has3Kind = true;
	}
	// otherwise no 3 of a kind
	else
	{
		has3Kind = false;
	}

	return has3Kind;
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
	bool has2Pairs; // bool outcome of function

	// first check xxyyz (make sure remaining card is kicker)
	if ((mHand[0].mRank == mHand[1].mRank) && (mHand[2].mRank == mHand[3].mRank) && (mHand[3].mRank != mHand[4].mRank))
	{
		has2Pairs = true;
	}
	// else check xyyzz (make sure remaining card is kicker)
	else if ((mHand[1].mRank == mHand[2].mRank) && (mHand[3].mRank == mHand[4].mRank) && (mHand[0].mRank != mHand[1].mRank))
	{
		has2Pairs = true;
	}
	// else check xxyzz (make sure remaining card is kicker)
	else if ((mHand[0].mRank == mHand[1].mRank) && (mHand[3].mRank == mHand[4].mRank) && (mHand[2].mRank != mHand[1].mRank)
		&& (mHand[2].mRank != mHand[3].mRank))
	{
		has2Pairs = true;
	}
	// otherwise no 2 pairs
	else
	{
		has2Pairs = false;
	}

	return has2Pairs;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
	bool hasPair; // bool outcome of function

	// first check aabcd (make sure remaining 3 cards are kickers)
	if ((mHand[0].mRank == mHand[1].mRank) && (mHand[1].mRank != mHand[2].mRank) && (mHand[2].mRank != mHand[3].mRank)
		&& (mHand[3].mRank != mHand[4].mRank))
	{
		hasPair = true;
	}
	// else check abbcd (make sure remaining 3 cards are kickers)
	else if ((mHand[1].mRank == mHand[2].mRank) && (mHand[0].mRank != mHand[1].mRank) && (mHand[2].mRank != mHand[3].mRank)
		&& (mHand[3].mRank != mHand[4].mRank))
	{
		hasPair = true;
	}
	// else check abccd (make sure remaining 3 cards are kickers)
	else if ((mHand[2].mRank == mHand[3].mRank) && (mHand[0].mRank != mHand[1].mRank) && (mHand[1].mRank != mHand[2].mRank)
		&& (mHand[3].mRank != mHand[4].mRank))
	{
		hasPair = true;
	}
	// else check abcdd (make sure remaining 3 cards are kickers)
	else if ((mHand[3].mRank == mHand[4].mRank) && (mHand[0].mRank != mHand[1].mRank) && (mHand[1].mRank != mHand[2].mRank)
		&& (mHand[2].mRank != mHand[3].mRank))
	{
		hasPair = true;
	}
	// otherwise no pair
	else
	{
		hasPair = false;
	}

	return hasPair;
}

void PokerHand::sortHand()
{
	// will conduct selection sort for poker hand (note: Card operators already defined below)
	for (int i = 0; i < mHand.size(); i++)
	{
		int smallIndex = i; // holds the index of smallest value (all values before i already sorted)
		for (int j = i + 1; j < mHand.size(); j++) // check all index values beyond i (which is currently index holding smallest)
		{
			if (mHand[j] < mHand[smallIndex]) // check if current index holds a smaller value
			{
				smallIndex = j; // the new index of the smallest value
			}
		}

		// now swap the minimum element into correct position
		Card temp = mHand[smallIndex];
		mHand[smallIndex] = mHand[i];
		mHand[i] = temp;
	}
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(ITPVector<Card>& deck)
{
	// create a SuitVector to hold all Suit enum values
	ITPVector<Suit> suitVector(4);
	suitVector.push_back(CLUBS);
	suitVector.push_back(DIAMONDS);
	suitVector.push_back(HEARTS);
	suitVector.push_back(SPADES);

	// create and fill the vector with the standard 52 cards (Note: J = 11, Q =12, K = 13, A = 14)
	for (int i = 2; i <= 14; i++)  // for each of the ranks
	{
		for (int j = 0; j < suitVector.size(); j++) // for each suit
		{
			Card c = Card(i, suitVector[j]); // create the card of current rank and suit
			deck.push_back(c); // now add the card to the deck
		}
	}

	// now shuffle the deck (using the code from the pdf instructions)
	std::sort(&deck[0], &deck[0] + deck.size());
	std::random_shuffle(&deck[0], &deck[0] + deck.size());
}

// I ADDED THIS FUNCTION!!!
// Function: << operator for Suit
// Purpose: Outputs the name of the card's suit
// Input: ostream and suit
// Returns: ostream, with suit name output to it
std::ostream& operator<<(std::ostream& os, const Suit& suit)
{
	switch (suit)
	{
	case CLUBS:
		os << "Clubs";
		break;
	case DIAMONDS:
		os << "Diamonds";
		break;
	case HEARTS:
		os << "Hearts";
		break;
	case SPADES:
		os << "Spades";
		break;
	}

	return os; // return the stream
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// will output card info in following format (e.g. Rank of Suit)
	if (card.mRank == 11)  // for jack
	{
		os << "Jack of " << card.mSuit;
	}

	else if (card.mRank == 12)  // for queen
	{
		os << "Queen of " << card.mSuit;
	}

	else if (card.mRank == 13)  // for king
	{
		os << "King of " << card.mSuit;
	}

	else if (card.mRank == 14)  // for jack
	{
		os << "Ace of " << card.mSuit;
	}

	else  // not a face card or ace
	{
		os << card.mRank << " of " << card.mSuit;
	}

	// return the stream
	return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
	bool result; // indicates outcome of the less than comparison

	// first compare the ranks
	if (left.mRank < right.mRank)
	{
		result = true;
	}
	// if rank of left is equal to right, check suit
	else if (left.mRank == right.mRank)
	{
		if (left.mSuit < right.mSuit)
		{
			result = true;
		}
		else  // left suit is greater than right
		{
			result = false;
		}
	}
	// otherwise, the left rank was larger than the right
	else
	{
		result = false;
	}

	return result; // return the outcome
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
	bool result; // indicates outcome of the greater than comparison

	// first compare the ranks
	if (left.mRank > right.mRank)
	{
		result = true;
	}
	// if rank of left is equal to right, check suit
	else if (left.mRank == right.mRank)
	{
		if (left.mSuit > right.mSuit)
		{
			result = true;
		}
		else  // left suit is less than right
		{
			result = false;
		}
	}
	// otherwise, the left rank was smaller than the right
	else
	{
		result = false;
	}

	return result; // return the outcome
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
	os << "{ "; // starting brace of hand output

	// loop through hand and display each card
	for (int i = 0; i < hand.mHand.size(); i++)
	{
		os << hand.mHand[i]; // output the card info

		if (i == hand.mHand.size() - 1) // last card in hand
		{
			os << " }"; // no comma needed but add the ending brace
		}
		else	// not the last card in hand 
		{
			os << ", "; // comma needed
		}
	}

	// return the stream
	return os;
}
