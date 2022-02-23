# Cardistry

## Content
- [Card](#card)
- [Combination](#combination)
- [CombinationBuilder](#combinationbuilder)
- [LookupTable](#lookuptable)
- [Utils](#utils)


## Card
This class is used for storing cards. To create Card object use `Value` and `Suit` enums.

*Example of creating K:clubs::*
```
Card card = Card(Value::King, Suit::Clubs)
```
### Value
Content of `Value` enum:
```
enum Value {
  Two = 2, Three, Four, Five, Six, Seven, Eight,
  Nine, Ten, Jack, Queen, King, Ace
};
```
### Suit
Content of `Suit` enum:
```
enum Suit { Clubs = 0, Diamonds, Hearts, Spades };
```

## Combination
This class is used for storing combinations. You cant create `Combination` object on your own. Use [`CombinationBuilder`](#combinationbuilder) for this purpose.


After creating of `Combination` object you can access its properties.

*Rank of combination*.
> All available ranks see in `Combination::Rank` enum.
```
Combination::Rank rank = combination.get_rank()
```
*Five cards or fewer that involved in combination building*.
```
std::vector<Card> kickers = combination.get_kickers()
```
*All cards passed to* `CombinationBuilder.build()`.
```
std::vector<Card> all_cards = combination.get_cards()
```

Content of `Combination::Rank` enum:

```
enum Rank {
  HighCard, OnePair, TwoPair, ThreeOfaKind, Straight, Flush,
  FullHouse, FourOfaKind, StraightFlush, RoyalFlush
};
```

## CombinationBuilder
This class is used for creating `Combination` objects with only one method `build()`.

*Example of creating Combination:*
```
std::vector<Card> cards({
Card(Value::Ace, Suit::Diamonds),
Card(Value::Queen, Suit::Diamonds),
Card(Value::King, Suit::Diamonds),
Card(Value::Ten, Suit::Diamonds),
Card(Value::Jack, Suit::Diamonds),
Card(Value::Two, Suit::Spades),
Card(Value::Two, Suit::Clubs),
});

CombinationBuilder combBuilder = CombinationBuilder();
Combination combination = combBuilder.build(cards);
```

## LookupTable
This class is used for evaluating poker hands on the run without creating `Combination` objects.

### `evaluate()`
The result of the evaluation is the relative strength of the combination.

> Note that you need to init LookupTable before evaluation.

*Example of evaluation:*
```
std::vector<Card> cards({
Card(Value::Ace, Suit::Diamonds),
Card(Value::Queen, Suit::Diamonds),
Card(Value::King, Suit::Diamonds),
Card(Value::Ten, Suit::Diamonds),
Card(Value::Jack, Suit::Diamonds),
});

LookupTable lookupTable = LookupTable();
lookupTable.init()

lookupTable.evaluate(cards)
```

### `init()`
Takes dumpfile path as a parameter to init `LookupTable` or (if no path) generates dump on its own. A dumpfile is needed for fast hand evaluation. 

## Utils

### `raw_values()`
*Parameters*: vector of cards.

*Return*: vector with `Value` of each card.

### `split_by_suit()`
*Parameters*: vector of cards.

*Return*: split cards by `Suit` packed into `std::map`.

### `split_by_value()`
*Parameters*: vector of cards.

*Return*: split cards by `Value` packed into `std::map`.

### `n_highest()`
*Parameters*: vector of cards, number `n` of cards needed.

*Return*: `n` highest cards in descending order.

### `n_highest_except()`
*Parameters*: vector of cards, vector of excepted cards, number `n` of cards needed.

*Return*: `n` highest cards without excepted cards in descending order.

### `unique_values()`
*Parametrs*: vector of cards.

*Returns*: vector of cards with first unique values.