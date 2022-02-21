#pragma once
#include <ostream>


namespace Cardistry {

	enum Value {
		Two = 2, Three, Four, Five, Six, Seven, Eight,
		Nine, Ten, Jack, Queen, King, Ace
	};

	enum Suit { Clubs = 0, Diamonds, Hearts, Spades };

	class Card
	{

	public:
		Card(Value value, Suit suit)
		{
			_value = value;
			_suit = suit;
		}

		Card(const Card& card)
		{
			_value = card._value;
			_suit = card._suit;
		}

		Card& operator=(const Card& other)
		{
			if (this != &other)
			{
				_value = other._value;
				_suit = other._suit;
			}

			return *this;
		}

		Value get_value()
		{
			return _value;
		}

		Suit get_suit()
		{
			return _suit;
		}

		friend bool operator> (const Card& c1, const Card& c2)
		{
			return c1._value > c2._value;
		}

		friend bool operator< (const Card& c1, const Card& c2)
		{
			return c1._value < c2._value;
		}

		friend bool operator== (const Card& c1, const Card& c2)
		{
			return (c1._value == c2._value) && (c1._suit == c2._suit);
		}

		friend bool operator!= (const Card& c1, const Card& c2)
		{
			return (c1._value != c2._value) || (c1._suit != c2._suit);
		}

	private:
		Value _value;
		Suit _suit;
	};
}