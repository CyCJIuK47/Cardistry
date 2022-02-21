#pragma once
#include "Card.h"
#include "Combination.h"
#include "Utils.h"
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <map>


namespace Cardistry {

	class CombinationBuilder
	{

	public:
		CombinationBuilder()
		{

		}

		Combination build(std::vector<Card>& cards)
		{
			typedef std::vector<Card>(CombinationBuilder::* method_p)(std::vector<Card>&);

			std::vector<Combination::Rank> comb_ranks = { Combination::Rank::RoyalFlush,
																		Combination::Rank::StraightFlush,
																		Combination::Rank::FourOfaKind,
																		Combination::Rank::FullHouse,
																		Combination::Rank::Flush,
																		Combination::Rank::Straight,
																		Combination::Rank::ThreeOfaKind,
																		Combination::Rank::TwoPair,
																		Combination::Rank::OnePair,
																		Combination::Rank::HighCard };

			std::vector<method_p> comb_methods = { &CombinationBuilder::_is_royal_flush,
															  &CombinationBuilder::_is_straight_flush,
															  &CombinationBuilder::_is_four_of_a_kind,
															  &CombinationBuilder::_is_full_house,
															  &CombinationBuilder::_is_flush,
															  &CombinationBuilder::_is_straight,
															  &CombinationBuilder::_is_tree_of_a_kind,
															  &CombinationBuilder::_is_two_pair,
															  &CombinationBuilder::_is_one_pair,
															  &CombinationBuilder::_is_high_card };

			for (int i = 0; i < comb_methods.size(); i++)
			{
				std::vector<Card> possible_comb = (*this.*comb_methods[i])(cards);

				if (!possible_comb.empty())
				{
					return Combination(comb_ranks[i], cards, possible_comb);
				}
			}
		}

	private:

		std::vector<Card> _is_royal_flush(std::vector<Card>& cards)
		{
			std::vector<Card> kickers = _is_straight_flush(cards);

			if (!kickers.empty() && kickers.begin()->get_value() == Value::Ace
				&& kickers.rbegin()->get_value() == Value::Ten)
			{
				return kickers;
			}
			return std::vector<Card>();
		}

		std::vector<Card> _is_straight_flush(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;

			std::map<Suit, std::vector<Card>> split_map = Utils::split_by_suit(cards);

			for (auto it : split_map)
			{
				if (it.second.size() >= 5)
				{
					kickers = _is_straight(it.second);

					if (!kickers.empty())
					{
						return kickers;
					}
				}
			}
			return kickers;
		}

		std::vector<Card> _is_flush(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;

			std::map<Suit, std::vector<Card>> split_map = Utils::split_by_suit(cards);

			for (auto it : split_map)
			{
				if (it.second.size() >= 5)
				{
					return Utils::n_heighest(it.second, 5);
				}
			}
			return kickers;
		}

		std::vector<Card> _is_straight(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;

			std::vector<Card> _cards(Utils::unique_values(cards));

			if (_cards.size() < 5)
			{
				return kickers;
			}

			std::sort(_cards.begin(), _cards.end(), std::greater<Card>());

			for (auto it = _cards.begin(); it != _cards.end() - 4; it++)
			{
				if ((it->get_value() - (it + 4)->get_value()) == 4)
				{
					kickers.insert(kickers.end(), it, it + 5);
					return kickers;
				}
			}

			// check A2345 case
			if ((_cards.rbegin() + 3)->get_value() - _cards.rbegin()->get_value() == 3
				&& _cards.begin()->get_value() == Value::Ace && _cards.rbegin()->get_value() == Value::Two)
			{
				kickers.push_back(*_cards.begin());
				kickers.insert(kickers.end(), (_cards.end() - 4), _cards.end());
			}

			return kickers;
		}

		std::vector<Card> _is_full_house(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;
			std::map<Value, std::vector<Card>> split_map = Utils::split_by_value(cards);

			for (int i = Value::Ace; i >= Value::Two; i--)
			{
				if (split_map[Value(i)].size() == 3)
				{

					for (int j = Value::Ace; j >= Value::Two; j--)
					{
						if (Value(j) != Value(i) && split_map[Value(j)].size() >= 2)
						{
							kickers.insert(kickers.end(), split_map[Value(i)].begin(), split_map[Value(i)].end());
							kickers.insert(kickers.end(), split_map[Value(j)].begin(), split_map[Value(j)].end());

							return kickers;
						}
					}
				}
			}

			return kickers;
		}

		std::vector<Card> _is_four_of_a_kind(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;
			std::map<Value, std::vector<Card>> split_map = Utils::split_by_value(cards);

			for (int i = Value::Ace; i >= Value::Two; i--)
			{
				if (split_map[Value(i)].size() == 4)
				{
					kickers.insert(kickers.end(), split_map[Value(i)].begin(), split_map[Value(i)].end());
					break;
				}
			}

			if (!kickers.empty())
			{
				std::vector<Card> rest_kickers = Utils::n_heighest_except(cards, kickers, 1);
				kickers.insert(kickers.end(), rest_kickers.begin(), rest_kickers.end());
			}

			return kickers;
		}

		std::vector<Card> _is_tree_of_a_kind(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;
			std::map<Value, std::vector<Card>> split_map = Utils::split_by_value(cards);

			for (int i = Value::Ace; i >= Value::Two; i--)
			{
				if (split_map[Value(i)].size() == 3)
				{
					kickers.insert(kickers.end(), split_map[Value(i)].begin(), split_map[Value(i)].end());
					break;
				}
			}

			if (!kickers.empty())
			{
				std::vector<Card> rest_kickers = Utils::n_heighest_except(cards, kickers, 2);
				kickers.insert(kickers.end(), rest_kickers.begin(), rest_kickers.end());
			}

			return kickers;
		}

		std::vector<Card> _is_one_pair(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;
			std::map<Value, std::vector<Card>> split_map = Utils::split_by_value(cards);

			for (int i = Value::Ace; i >= Value::Two; i--)
			{
				if (split_map[Value(i)].size() == 2)
				{
					kickers.insert(kickers.end(), split_map[Value(i)].begin(), split_map[Value(i)].end());
					break;
				}
			}

			if (!kickers.empty())
			{
				std::vector<Card> rest_kickers = Utils::n_heighest_except(cards, kickers, 3);
				kickers.insert(kickers.end(), rest_kickers.begin(), rest_kickers.end());
			}

			return kickers;
		}

		std::vector<Card> _is_two_pair(std::vector<Card>& cards)
		{
			std::vector<Card> kickers;
			std::map<Value, std::vector<Card>> split_map = Utils::split_by_value(cards);

			for (int i = Value::Ace; i >= Value::Two; i--)
			{
				if (split_map[Value(i)].size() == 2)
				{

					for (int j = Value::Ace; j >= Value::Two; j--)
					{
						if (Value(j) != Value(i) && split_map[Value(j)].size() == 2)
						{
							kickers.insert(kickers.end(), split_map[Value(i)].begin(), split_map[Value(i)].end());
							kickers.insert(kickers.end(), split_map[Value(j)].begin(), split_map[Value(j)].end());

							std::vector<Card> rest_kickers = Utils::n_heighest_except(cards, kickers, 3);
							kickers.insert(kickers.end(), rest_kickers.begin(), rest_kickers.end());

							return kickers;
						}
					}
				}
			}

			return kickers;
		}

		std::vector<Card> _is_high_card(std::vector<Card>& cards)
		{
			std::vector<Card> kickers(cards.begin(), cards.begin() + (std::min(5, int(cards.size()))));
			return kickers;
		}
	};
}

