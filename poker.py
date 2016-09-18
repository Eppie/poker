import random
import array
import sys

stake = 100
ante = 10
var = ""


class Card():
    suit = ""
    suit_number = 0
    rank = ""
    rank_number = 0
    name = ""


def generate_suit(card):
    suit = random.randint(1, 4)
    card.suit_number = suit
    if suit == 1:
        card.suit = 'of Clubs'
    elif suit == 2:
        card.suit = 'of Spades'
    elif suit == 3:
        card.suit = 'of Hearts'
    elif suit == 4:
        card.suit = 'of Diamonds'


def generate_rank(card):
    rank = random.randint(2, 14)
    card.rank_number = rank
    if rank >= 2 and rank <= 10:
        card.rank = str(rank) + ' '
    elif rank == 11:
        card.rank = 'Jack '
    elif rank == 12:
        card.rank = 'Queen '
    elif rank == 13:
        card.rank = 'King '
    elif rank == 14:
        card.rank = 'Ace '


def generate_name(card):
    card.name = card.rank + card.suit


def generate_card():
    card = Card()
    generate_suit(card)
    generate_rank(card)
    generate_name(card)
    return card


class Hand():
    card1 = Card()
    card2 = Card()
    card3 = Card()
    score = 0


def generate_hand():
    hand = Hand()
    while cards_equal(hand.card1, hand.card2) or cards_equal(hand.card2, hand.card3) or cards_equal(hand.card1, hand.card3):
        hand.card1 = generate_card()
        hand.card2 = generate_card()
        hand.card3 = generate_card()
    return hand


def rank_equal(card1, card2):
    if card1.rank == card2.rank:
        return True
    else:
        return False


def suit_equal(card1, card2):
    if card1.suit == card2.suit:
        return True
    else:
        return False


def cards_equal(card1, card2):
    if card1.suit == card2.suit and card1.rank == card2.rank:
        return True
    else:
        return False


def score(hand):
    score = 0
    bonus = 0

    ranks = [hand.card1.rank_number, hand.card2.rank_number, hand.card3.rank_number]
    ranks.sort(reverse=True)

    straightflush = False
    three = False
    straight = False
    flush = False
    pair = False

    if rank_equal(hand.card1, hand.card2) or rank_equal(hand.card2, hand.card3) or rank_equal(hand.card1, hand.card3):
        pair = True

    if suit_equal(hand.card1, hand.card2) and suit_equal(hand.card2, hand.card3):
        flush = True

    if ranks[0] == (ranks[1] + 1) == (ranks[2] + 2):
        straight = True

    if straight and flush:
        straightflush = True

    if rank_equal(hand.card1, hand.card2) and rank_equal(hand.card2, hand.card3):
        three = True

    if pair:
        bonus = 3000
    if flush:
        bonus = 4000
    if straight:
        bonus = 5000
    if three:
        bonus = 6000
    if straightflush:
        bonus = 7000

    score = (ranks[0] * 225) + (ranks[1] * 15) + (ranks[2]) + bonus

    return score


def player_win(phand, dhand):
    phandscore = score(phand)
    dhandscore = score(dhand)
    if phandscore >= dhandscore:
        return True
    else:
        return False


def dealer_play(hand):
    if score(hand) < 2732:
        return False
    else:
        return True


def print_hand(hand):
    print(hand.card1.name)
    print(hand.card2.name)
    print(hand.card3.name)
    print('Score: ' + str(score(hand)) + '\n')


def playorfold():
    global var
    var = raw_input("Play or fold? (p/f): ")
    if var != "p" and var != "f":
        playorfold()


def playorquit():
    global var
    var = raw_input("Continue playing? (y/n): ")
    if var == "y":
        return
    elif var == "n":
        print('Goodbye!')
        sys.exit(0)
    else:
        playorquit()


def main():
    global stake

    if (stake / ante) > 2:
        playorquit()

    if stake <= 0:
        print('YOU ARE THE WEAKEST LINK. GOODBYE.')
        sys.exit(0)

    phand = generate_hand()
    dhand = generate_hand()

    print('Here\'s your hand:')
    print_hand(phand)

    playorfold()

    if var == "p":
        if dealer_play(dhand):
            if player_win(phand, dhand):
                print('Congratulations! You won!')
                stake = stake + (ante * 2)
                print('Your stake is now: ' + str(stake))
            else:
                print('Sorry, you lost. Loser.')
                stake = stake - (ante * 2)
                print('Your stake is now: ' + str(stake))
        else:
            print('The dealer folds. Congratulations!')
            stake = stake + ante
            print('Your stake is now: ' + str(stake))

    if var == "f":
        print('You folded like the coward you are.')
        stake = stake - ante
        print('Your stake is now: ' + str(stake))

    print('Dealer\'s hand was:\n')
    print_hand(dhand)
    main()

print('You know how to use the program, dummy.')
print('Your stake is : ' + str(stake))
main()
