#pragma once
#include <algorithm>
#include <map>
#include <set>
#include "Card.h"
#include "Combination.h"


namespace Cardistry {

	namespace Utils
	{	
		std::vector<Value> raw_values(std::vector<Card> cards)
		{
			std::vector<Value> raw_values;

			for (auto it = cards.begin(); it != cards.end(); it++)
			{
				raw_values.push_back((*it).get_value());
			}

			return raw_values;
		}

		std::map<Suit, std::vector<Card>> split_by_suit(std::vector<Card>& cards)
		{
			std::map<Suit, std::vector<Card>> split_map = { {Suit::Clubs, {}},
															{Suit::Diamonds, {}},
															{Suit::Hearts, {}},
															{Suit::Spades, {}} };

			for (auto it = cards.begin(); it != cards.end(); it++)
			{
				split_map[it->get_suit()].push_back(*it);
			}

			return split_map;
		}

		std::map<Value, std::vector<Card>> split_by_value(std::vector<Card>& cards)
		{
			std::map<Value, std::vector<Card>> split_map;

			for (int i = Value::Two; i <= Value::Ace; i++)
			{
				split_map[Value(i)] = {};
			}

			for (auto it = cards.begin(); it != cards.end(); it++)
			{
				split_map[it->get_value()].push_back(*it);
			}

			return split_map;
		}

		std::vector<Card> n_highest(std::vector<Card>& cadrs, int n)
		{
			std::vector<Card> sorted = cadrs;
			std::sort(sorted.begin(), sorted.end());

			return std::vector<Card>(sorted.rbegin(), sorted.rbegin() + std::min(n, int(sorted.size())));
		}

		std::vector<Card> n_highest_except(std::vector<Card>& cards, std::vector<Card> except, int n)
		{
			struct CardCmp {
				bool operator() (Card a, Card b) const {
					return a.get_value() * 13 + a.get_suit() < b.get_value() * 13 + b.get_suit();
				}
			};

			std::set<Card, CardCmp> card_set(cards.begin(), cards.end());

			for (auto it : except)
			{
				card_set.erase(it);
			}

			std::vector<Card> sorted = std::vector<Card>(card_set.begin(), card_set.end());
			std::sort(sorted.begin(), sorted.end());

			if (sorted.empty())
			{
				return std::vector<Card>();
			}

			return std::vector<Card>(sorted.rbegin(), sorted.rbegin() + std::min(n, int(sorted.size())));
		}

		std::vector<Card> unique_values(std::vector<Card>& cards)
		{
			if (cards.size() < 2)
			{
				return cards;
			}

			std::vector<Card> unique_cards;
			unique_cards.push_back(cards[0]);

			for (int i = 0; i < cards.size() - 1; i++)
			{
				if (cards[i].get_value() != cards[i + 1].get_value())
				{
					unique_cards.push_back(cards[i + 1]);
				}
			}

			return unique_cards;
		}
	};
}

