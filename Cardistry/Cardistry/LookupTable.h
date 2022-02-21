#pragma once
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <map>
#include <vector>
#include "Card.h"
#include "Combination.h"
#include "Utils.h"


namespace Cardistry {

	class LookupTable
	{
	public:
		LookupTable()
		{
			
		}

		void init(std::string dump_file = "lookup_dump.txt")
		{
			bool isLoaded = _load_table(dump_file);
			if (!isLoaded)
			{
				_generate_table();
				_dump_table();
			}
		}

		int evaluate(std::vector<Card> cards)
		{
			std::sort(cards.begin(), cards.end(), std::greater<Card>());

			long long hash = _values_to_hash(Utils::raw_values(cards));
			int power = _find(hash);

			std::map<Suit, std::vector<Card>> split_map = Utils::split_by_suit(cards);

			for (auto it = split_map.begin(); it != split_map.end(); it++)
			{
				long long s_hash = -1 * _values_to_hash(Utils::raw_values(cards));
				power = std::max(power, _find(s_hash));
			}

			return power;
		}

		int evaluate(Combination comb)
		{
			return evaluate(comb.get_cards());
		}

		std::vector<int> evaluate(std::vector<std::vector<Card>> n_cards)
		{
			std::vector<int> powers;
			for (auto it = n_cards.begin(); it != n_cards.end(); it++)
			{
				powers.push_back(evaluate(*it));
			}

			return powers;
		}

		std::vector<int> evaluate(std::vector<Combination> n_combs)
		{
			std::vector<int> powers;
			for (auto it = n_combs.begin(); it != n_combs.end(); it++)
			{
				powers.push_back(evaluate(it->get_cards()));
			}

			return powers;
		}

	private:

		void _dump_table(std::string dump_file = "lookup_dump.txt")
		{
			std::ofstream dump_stream;
			dump_stream.open(dump_file);

			for (const auto& it : _table)
			{
				dump_stream << it.first << ' ' << it.second << std::endl;
			}

			dump_stream.close();
		}

		bool _load_table(std::string dump_file = "lookup_dump.txt")
		{
			std::ifstream dump_stream;
			dump_stream.open(dump_file);

			if (!dump_stream)
			{
				return false;
			}

			int power;
			long long hash;

			while (dump_stream >> hash, dump_stream >> power)
			{
				_table[hash] = power;
			}

			return true;
		}

		void _generate_table()
		{
			int cards_remain[15];
			std::fill_n(cards_remain, 15, 4);

			std::vector<Value> current_comb;

			std::vector<std::vector<Value>> vcombs;
			std::vector<std::vector<Value>> scombs;

			_generate_vcombs(cards_remain, Value::Ace, current_comb, vcombs);
			_generate_scombs(Value::Ace, current_comb, scombs);

			std::vector<std::tuple<Combination::Rank, std::vector<Value>, std::vector<Value>>> vcomb_ranks;
			std::vector<std::tuple<Combination::Rank, std::vector<Value>, std::vector<Value>>> scomb_ranks;

			for (auto comb : vcombs)
			{
				vcomb_ranks.push_back(_match_value_sensetive(comb));
			}

			for (auto comb: scombs)
			{
				scomb_ranks.push_back(_match_suit_sensetive(comb));
			}

			std::vector<std::tuple<Combination::Rank, std::vector<Value>, std::vector<Value>>> all_combs;
			all_combs.insert(all_combs.end(), vcomb_ranks.begin(), vcomb_ranks.end());
			all_combs.insert(all_combs.end(), scomb_ranks.begin(), scomb_ranks.end());

			std::sort(all_combs.begin(), all_combs.end());
			
			std::vector<int> powers({ 1 });
			int current_power = 0;

			for (auto it = all_combs.begin(); it != (all_combs.end() - 1); it++)
			{
				if (std::get<0>(*it) != std::get<0>(*(it + 1)) || std::get<1>(*it) != std::get<1>(*(it + 1)))
				{
					current_power++;
				}

				powers.push_back(current_power);
			}

			for (int i = 0; i < all_combs.size(); i++)
			{
				long long hash = _values_to_hash(std::get<0>(all_combs[i]), std::get<2>(all_combs[i]));
				_table[hash] = powers[i];
			}
		}

		// generates all value-sensitive combinations (0-7 length)
		void _generate_vcombs(int* cards_remain, Value current_card, std::vector<Value>& current_comb,
			std::vector<std::vector<Value>>& all_combs)
		{

			all_combs.push_back(current_comb);
			if (current_comb.size() == 7)
			{
				return;
			}

			for (int i = current_card; i >= Value::Two; i--)
			{
				if (cards_remain[i] != 0)
				{
					// pick a card
					cards_remain[i]--;
					current_comb.push_back(Value(i));
					_generate_vcombs(cards_remain, Value(i), current_comb, all_combs);
					// return card to the deck
					cards_remain[i]++;
					current_comb.pop_back();
				}
			}

		}

		// generates all suit-sensitive combinations (0-7 length)
		void _generate_scombs(Value current_card, std::vector<Value>& current_comb,
			std::vector<std::vector<Value>>& all_combs)
		{
			all_combs.push_back(current_comb);

			if (current_comb.size() == 7)
			{
				return;
			}

			for (int i = current_card - 1; i >= Value::Two; i--)
			{
				current_comb.push_back(Value(i));
				_generate_scombs(Value(i), current_comb, all_combs);
				current_comb.pop_back();
			}
		}

		std::tuple<Combination::Rank, std::vector<Value>, std::vector<Value>> _match_suit_sensetive(std::vector<Value>& cards)
		{
			if (cards.empty())
			{
				return std::make_tuple(Combination::Rank::HighCard, std::vector<Value>(), cards);
			}

			typedef std::vector<Value>(LookupTable::* method_p)(std::vector<Value>&);

			std::vector<Combination::Rank> suit_sensetive_comb_ranks = { Combination::Rank::RoyalFlush,
																		Combination::Rank::StraightFlush,
																		Combination::Rank::Flush,
																		Combination::Rank::HighCard };

			std::vector<method_p> suit_sensetive_methods = { &LookupTable::_is_royal_flush,
															  &LookupTable::_is_straight_flush,
															  &LookupTable::_is_flush,
															  &LookupTable::_is_high_card };

			for (int i = 0; i < suit_sensetive_methods.size(); i++)
			{
				std::vector<Value> possible_comb = (*this.*suit_sensetive_methods[i])(cards);

				if (!possible_comb.empty())
				{
					return std::make_tuple(suit_sensetive_comb_ranks[i], possible_comb, cards);
				}
			}

		}

		std::tuple<Combination::Rank, std::vector<Value>, std::vector<Value>> _match_value_sensetive(std::vector<Value>& cards)
		{
			if (cards.empty())
			{
				return std::make_tuple(Combination::Rank::HighCard, std::vector<Value>(), cards);
			}

			typedef std::vector<Value>(LookupTable::* method_p)(std::vector<Value>&);

			std::vector<Combination::Rank> value_sensetive_comb_ranks = { Combination::Rank::FourOfaKind,
																		Combination::Rank::FullHouse,
																		Combination::Rank::Straight,
																		Combination::Rank::ThreeOfaKind,
																		Combination::Rank::TwoPair,
																		Combination::Rank::OnePair,
																		Combination::Rank::HighCard };

			std::vector<method_p> value_sensetive_methods = { &LookupTable::_is_four_of_a_kind,
															  &LookupTable::_is_full_house,
															  &LookupTable::_is_straight,
															  &LookupTable::_is_tree_of_a_kind,
															  &LookupTable::_is_two_pair,
															  &LookupTable::_is_one_pair,
															  &LookupTable::_is_high_card };

			for (int i = 0; i < value_sensetive_methods.size(); i++)
			{
				std::vector<Value> possible_comb = (*this.*value_sensetive_methods[i])(cards);

				if (!possible_comb.empty())
				{
					return std::make_tuple(value_sensetive_comb_ranks[i], possible_comb, cards);
				}
			}
		}

		long long _values_to_hash(std::vector<Value> cards)
		{
			long long hash = 0;

			std::sort(cards.begin(), cards.end(), std::greater<Value>());

			for (auto it = cards.begin(); it != cards.end(); it++)
			{
				hash *= 100;
				hash += *it;
			}

			return hash;
		}

		long long _values_to_hash(Combination::Rank rank, std::vector<Value> cards)
		{
			std::sort(cards.begin(), cards.end(), std::greater<Value>());
			long long hash = _values_to_hash(cards);

			if (rank == Combination::RoyalFlush || rank == Combination::StraightFlush || rank == Combination::Flush)
			{
				hash *= -1;
			}

			return hash;
		}

		int _find(long long hash)
		{
			std::map<long long, int>::iterator it = _table.find(hash);

			if (it != _table.end())
			{
				return it->second;
			}

			return -1;
		}

		std::vector<Value> _is_royal_flush(std::vector<Value>& cards)
		{
			std::vector<Value> kickers = _is_straight(cards);
			if (!kickers.empty() && *kickers.begin() == Value::Ace && *kickers.rbegin() == Value::Two)
			{
				return kickers;
			}
			return std::vector<Value>();
		}

		std::vector<Value> _is_straight_flush(std::vector<Value>& cards)
		{
			std::vector<Value> kickers = _is_straight(cards);
			return kickers;
		}

		std::vector<Value> _is_flush(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;
			if (cards.size() >= 5)
			{
				kickers = _is_high_card(cards);
			}
			return kickers;
		}

		std::vector<Value> _is_straight(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<Value> _cards(cards);
			_cards.erase(std::unique(_cards.begin(), _cards.end()), _cards.end());

			if (_cards.size() < 5)
			{
				return kickers;
			}

			for (int i = 0; i < _cards.size() - 4; i++)
			{
				if ((_cards[i] - _cards[i + 4]) == 4)
				{
					for (int j = i; j < i + 5; j++)
					{
						kickers.push_back(_cards[j]);
					}
					return kickers;
				}
			}

			// A2345 case
			if (_cards[_cards.size() - 4] - _cards[_cards.size() - 1] == 3
				&& _cards[0] == Value::Ace && _cards[_cards.size() - 1] == Value::Two)
			{
				kickers.push_back(Value::Ace);
				for (int i = _cards.size() - 4; i < _cards.size(); i++)
				{
					kickers.push_back(_cards[i]);
				}
			}

			return kickers;
		}

		std::vector<Value> _is_four_of_a_kind(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<int> cards_count(15);

			for (auto i : cards)
			{
				cards_count[i]++;
			}

			for (int base = Value::Ace; base >= Value::Two; --base)
			{
				if (cards_count[base] == 4)
				{
					std::fill_n(std::back_inserter(kickers), 4, Value(base));

					for (int kicker = Value::Ace; kicker >= Value::Two; --kicker)
					{
						if (kicker != base && kickers.size() < 5)
						{
							kickers.push_back(Value(kicker));
						}
					}

					return kickers;
				}
			}

			return kickers;
		}

		std::vector<Value> _is_tree_of_a_kind(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<int> cards_count(15);

			for (auto i : cards)
			{
				cards_count[i]++;
			}

			for (int base = Value::Ace; base >= Value::Two; --base)
			{
				if (cards_count[base] == 3)
				{
					std::fill_n(std::back_inserter(kickers), 3, Value(base));

					for (int kicker = Value::Ace; kicker >= Value::Two; --kicker)
					{
						if (kicker != base && kickers.size() < 5)
						{
							kickers.push_back(Value(kicker));
						}
					}

					return kickers;
				}
			}

			return kickers;
		}

		std::vector<Value> _is_one_pair(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<int> cards_count(15);

			for (auto i : cards)
			{
				cards_count[i]++;
			}

			for (int base = Value::Ace; base >= Value::Two; --base)
			{
				if (cards_count[base] == 2)
				{
					std::fill_n(std::back_inserter(kickers), 2, Value(base));

					for (int kicker = Value::Ace; kicker >= Value::Two; --kicker)
					{
						if (kicker != base && kickers.size() < 5)
						{
							kickers.push_back(Value(kicker));
						}
					}

					return kickers;
				}
			}

			return kickers;
		}

		std::vector<Value> _is_two_pair(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<int> cards_count(15);

			for (auto i : cards)
			{
				cards_count[i]++;
			}

			for (int base1 = Value::Ace; base1 >= Value::Two; --base1)
			{
				if (cards_count[base1] == 2)
				{
					for (int base2 = Value::Ace; base2 >= Value::Two; --base2)
					{
						if (cards_count[base2] == 2 && base1 != base2)
						{
							std::fill_n(std::back_inserter(kickers), 2, Value(base1));
							std::fill_n(std::back_inserter(kickers), 2, Value(base2));


							for (int kicker = Value::Ace; kicker >= Value::Two; --kicker)
							{
								if (kicker != base1 && kicker != base2 && kickers.size() < 5)
								{
									kickers.push_back(Value(kicker));
								}
							}

							return kickers;
						}
					}
				}
			}

			return kickers;
		}

		std::vector<Value> _is_full_house(std::vector<Value>& cards)
		{
			std::vector<Value> kickers;

			std::vector<int> cards_count(15);

			for (auto i : cards)
			{
				cards_count[i]++;
			}

			for (int base1 = Value::Ace; base1 >= Value::Two; --base1)
			{
				if (cards_count[base1] == 3)
				{
					for (int base2 = Value::Ace; base2 >= Value::Two; --base2)
					{
						if (cards_count[base2] >= 2 && base1 != base2)
						{
							std::fill_n(std::back_inserter(kickers), 3, Value(base1));
							std::fill_n(std::back_inserter(kickers), 2, Value(base2));

							return kickers;
						}
					}
				}
			}

			return kickers;
		}

		std::vector<Value> _is_high_card(std::vector<Value>& cards)
		{
			std::vector<Value> kickers(cards.begin(), cards.begin() + (std::min(5, int(cards.size()))));
			return kickers;
		}

	private:
		std::map<long long, int> _table;
	};
}