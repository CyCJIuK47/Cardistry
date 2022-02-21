#include "pch.h"
#include "CppUnitTest.h"

#include "Cardistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CardistryTests
{
	TEST_CLASS(CombinationBuilderTest)
	{
	public:

		TEST_METHOD(buildTest1)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::HighCard);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Ace, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::HighCard);

			std::vector<Card> cards2({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Five, Suit::Diamonds),
				Card(Value::Four, Suit::Spades),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Jack, Suit::Hearts)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::HighCard);
		}

		TEST_METHOD(buildTest2)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::OnePair);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Jack, Suit::Clubs),
				Card(Value::King, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::OnePair);
		}

		TEST_METHOD(buildTest3)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::TwoPair);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Jack, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::TwoPair);
		}

		TEST_METHOD(buildTest4)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::ThreeOfaKind);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::ThreeOfaKind);
		}

		TEST_METHOD(buildTest5)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Four, Suit::Spades),
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts),
				Card(Value::Five, Suit::Spades)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::Straight);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::Straight);

			std::vector<Card> cards2({
				Card(Value::Ace, Suit::Clubs),
				Card(Value::Queen, Suit::Spades),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Clubs),
				Card(Value::Four, Suit::Hearts)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::Straight);
		}

		TEST_METHOD(buildTest6)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Four, Suit::Clubs),
				Card(Value::Ace, Suit::Clubs),
				Card(Value::Two, Suit::Clubs),
				Card(Value::Jack, Suit::Clubs)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::Flush);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Spades),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Nine, Suit::Spades),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Two, Suit::Spades)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::Flush);

			std::vector<Card> cards2({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Four, Suit::Diamonds)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::Flush);

			std::vector<Card> cards3({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Four, Suit::Diamonds),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination3 = combBuilder.build(cards3);
			Assert::IsTrue(combination3.get_rank() == Combination::Rank::Flush);
		}

		TEST_METHOD(buildTest7)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Three, Suit::Spades),
				Card(Value::Two, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::FullHouse);

			std::vector<Card> cards1({
				Card(Value::Jack, Suit::Spades),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Nine, Suit::Spades),
				Card(Value::Nine, Suit::Clubs),
				Card(Value::Nine, Suit::Hearts),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Seven, Suit::Spades)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::FullHouse);

			std::vector<Card> cards2({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Ace, Suit::Hearts),
				Card(Value::Ace, Suit::Spades),
				Card(Value::King, Suit::Spades),
				Card(Value::King, Suit::Diamonds),
				Card(Value::King, Suit::Clubs)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::FullHouse);
		}

		TEST_METHOD(buildTest8)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Three, Suit::Spades),
				Card(Value::Three, Suit::Hearts),
				Card(Value::Two, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::FourOfaKind);

			std::vector<Card> cards1({
				Card(Value::Jack, Suit::Spades),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Nine, Suit::Spades),
				Card(Value::Nine, Suit::Clubs),
				Card(Value::Nine, Suit::Hearts),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Seven, Suit::Spades)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::FourOfaKind);

			std::vector<Card> cards2({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Ace, Suit::Hearts),
				Card(Value::Ace, Suit::Spades),
				Card(Value::Ace, Suit::Clubs),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::FourOfaKind);
		}

		TEST_METHOD(buildTest9)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Four, Suit::Clubs),
				Card(Value::Ace, Suit::Clubs),
				Card(Value::Two, Suit::Clubs),
				Card(Value::Five, Suit::Clubs)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::StraightFlush);

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Ten, Suit::Diamonds),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::StraightFlush);

			std::vector<Card> cards2({
				Card(Value::Nine, Suit::Spades),
				Card(Value::Queen, Suit::Spades),
				Card(Value::King, Suit::Spades),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Four, Suit::Hearts)
				});

			Combination combination2 = combBuilder.build(cards2);
			Assert::IsTrue(combination2.get_rank() == Combination::Rank::StraightFlush);
		}

		TEST_METHOD(buildTest10)
		{
			using namespace Cardistry;

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards({
				Card(Value::King, Suit::Clubs),
				Card(Value::Ten, Suit::Clubs),
				Card(Value::Ace, Suit::Clubs),
				Card(Value::Jack, Suit::Clubs),
				Card(Value::Queen, Suit::Clubs),
				Card(Value::Seven, Suit::Clubs),
				Card(Value::Seven, Suit::Hearts)
				});

			Combination combination = combBuilder.build(cards);
			Assert::IsTrue(combination.get_rank() == Combination::Rank::RoyalFlush);

			std::vector<Card> cards1({
				Card(Value::King, Suit::Hearts),
				Card(Value::Ten, Suit::Hearts),
				Card(Value::Ace, Suit::Hearts),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Queen, Suit::Hearts),
				Card(Value::Eight, Suit::Hearts),
				Card(Value::Nine, Suit::Hearts)
				});

			Combination combination1 = combBuilder.build(cards1);
			Assert::IsTrue(combination1.get_rank() == Combination::Rank::RoyalFlush);
		}
	};

	TEST_CLASS(LookupTableTest)
	{
	public:

		TEST_METHOD(evaluateTest1)
		{
			using namespace Cardistry;

			LookupTable lookupTable = LookupTable();
			lookupTable.init();

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades)
				});

			std::vector<Card> cards2({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades)
				});

			Combination combination1 = combBuilder.build(cards1);
			Combination combination2 = combBuilder.build(cards2);

			Assert::IsTrue((combination1 < combination2)
				&& (lookupTable.evaluate(cards1) < lookupTable.evaluate(cards2)));


			std::vector<Card> cards3({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			std::vector<Card> cards4({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Spades),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Two, Suit::Hearts)
				});

			Combination combination3 = combBuilder.build(cards3);
			Combination combination4 = combBuilder.build(cards4);

			Assert::IsTrue((combination3 < combination4)
				&& (lookupTable.evaluate(cards3) < lookupTable.evaluate(cards4)));
		}

		TEST_METHOD(evaluateTest2)
		{
			using namespace Cardistry;

			LookupTable lookupTable = LookupTable();
			lookupTable.init();

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			std::vector<Card> cards2({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Three, Suit::Spades),
				Card(Value::Two, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Combination combination2 = combBuilder.build(cards2);

			Assert::IsTrue((combination1 < combination2)
				&& (lookupTable.evaluate(cards1) < lookupTable.evaluate(cards2)));


			std::vector<Card> cards3({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			std::vector<Card> cards4({
				Card(Value::Jack, Suit::Spades),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Nine, Suit::Spades),
				Card(Value::Nine, Suit::Clubs),
				Card(Value::Nine, Suit::Hearts),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Seven, Suit::Spades)
				});

			Combination combination3 = combBuilder.build(cards3);
			Combination combination4 = combBuilder.build(cards4);

			Assert::IsTrue((combination3 < combination4)
				&& (lookupTable.evaluate(cards3) < lookupTable.evaluate(cards4)));
		}

		TEST_METHOD(evaluateTest3)
		{
			using namespace Cardistry;

			LookupTable lookupTable = LookupTable();
			lookupTable.init();

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Three, Suit::Spades),
				Card(Value::Two, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			std::vector<Card> cards2({
				Card(Value::Jack, Suit::Spades),
				Card(Value::Jack, Suit::Hearts),
				Card(Value::Nine, Suit::Spades),
				Card(Value::Nine, Suit::Clubs),
				Card(Value::Nine, Suit::Hearts),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Seven, Suit::Spades)
				});

			Combination combination1 = combBuilder.build(cards1);
			Combination combination2 = combBuilder.build(cards2);

			Assert::IsTrue((combination1 < combination2)
				&& (lookupTable.evaluate(cards1) < lookupTable.evaluate(cards2)));


			std::vector<Card> cards3({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Four, Suit::Diamonds)
				});

			std::vector<Card> cards4({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Ace, Suit::Hearts),
				Card(Value::Ace, Suit::Spades),
				Card(Value::Ace, Suit::Clubs),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds)
				});

			Combination combination3 = combBuilder.build(cards3);
			Combination combination4 = combBuilder.build(cards4);

			Assert::IsTrue((combination3 < combination4)
				&& (lookupTable.evaluate(cards3) < lookupTable.evaluate(cards4)));
		}

		TEST_METHOD(evaluateTest4)
		{
			using namespace Cardistry;

			LookupTable lookupTable = LookupTable();
			lookupTable.init();

			CombinationBuilder combBuilder = CombinationBuilder();

			std::vector<Card> cards1({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Two, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Jack, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			std::vector<Card> cards2({
				Card(Value::Three, Suit::Clubs),
				Card(Value::Jack, Suit::Spades),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Eight, Suit::Spades),
				Card(Value::Eight, Suit::Clubs),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination1 = combBuilder.build(cards1);
			Combination combination2 = combBuilder.build(cards2);

			Assert::IsTrue((combination1 < combination2)
				&& (lookupTable.evaluate(cards1) < lookupTable.evaluate(cards2)));


			std::vector<Card> cards3({
				Card(Value::Ace, Suit::Diamonds),
				Card(Value::Queen, Suit::Diamonds),
				Card(Value::King, Suit::Diamonds),
				Card(Value::Ten, Suit::Spades),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Four, Suit::Diamonds)
				});

			std::vector<Card> cards4({
				Card(Value::Three, Suit::Diamonds),
				Card(Value::Jack, Suit::Diamonds),
				Card(Value::Nine, Suit::Diamonds),
				Card(Value::Ten, Suit::Diamonds),
				Card(Value::Eight, Suit::Diamonds),
				Card(Value::Seven, Suit::Diamonds),
				Card(Value::Two, Suit::Diamonds)
				});

			Combination combination3 = combBuilder.build(cards3);
			Combination combination4 = combBuilder.build(cards4);

			Assert::IsTrue((combination3 < combination4)
				&& (lookupTable.evaluate(cards3) < lookupTable.evaluate(cards4)));
		}
	};
}
