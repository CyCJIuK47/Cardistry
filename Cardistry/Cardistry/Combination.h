#pragma once
#include <vector>
#include "Card.h"


namespace Cardistry {

	class Combination
	{

	public:
		enum Rank {
			HighCard, OnePair, TwoPair, ThreeOfaKind, Straight, Flush,
			FullHouse, FourOfaKind, StraightFlush, RoyalFlush
		};

		Combination(Rank rank, std::vector<Card>& cards, std::vector<Card>& kickers)
		{
			_rank = rank;
			_cards = cards;
			_kickers = kickers;
		}

		Combination(const Combination& combination)
		{
			_rank = combination._rank;
			_cards = combination._cards;
			_kickers = combination._kickers;
		}

		Combination& operator=(const Combination& other)
		{
			if (this != &other)
			{
				_rank = other._rank;
				_cards = other._cards;
				_kickers = other._kickers;
			}

			return *this;
		}

		Rank get_rank()
		{
			return _rank;
		}

		std::vector<Card> get_cards()
		{
			return _cards;
		}

		std::vector<Card> get_kickers()
		{
			return _kickers;
		}

		friend bool operator< (const Combination& comb1, const Combination& comb2)
		{
			if (comb1._rank != comb2._rank)
			{
				return comb1._rank < comb2._rank;
			}
			else
			{
				return comb1._kickers < comb2._kickers;
			}
		}

		friend bool operator== (const Combination& comb1, const Combination& comb2)
		{
			return (comb1._rank == comb2._rank) && (comb1._kickers == comb2._kickers);
		}

	private:
		Rank _rank;
		std::vector<Card> _cards;
		std::vector<Card> _kickers;
	};
}
