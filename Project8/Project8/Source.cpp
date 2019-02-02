#include <iostream>
#include <cstring>
#include <ctime>
#include <limits>
struct Card {                                            // This struct will be used to create cards in the game
  char m_suit[10];
  char m_name[10];
  int m_value;

};
struct Player {                                          //This struct will be either the player or the card dealer
  float wallet = 500;
  int bet = 0;
  int m_handTotal;
  int m_cardIndex = 0;
  int m_handIndex = -1;
  Card m_hand[11];
};
Card CardDraw(Card *_deck, int &_TopOfDeck)				// This function uses the deck of cards after its generated and then another value which keeps track of what card is the current top of deck 
{
  return _deck[_TopOfDeck++];                         // each time this function occurs the top of the deck counter is increased 
                                                      //this assigns a value that goes from 1 to 52 to each card after 
}														//its generated, in the order its generated and then to be assigned to the cards within the player hand. 
                            //This is done because Arrays are static meaning that we cant delete the card (from the Deck) after its assigned to the player's card
                            //so instead we keep track of the cards and make sure that every new card the player/dealer receives is a new one from the deck order
Card CardDraw(Card *_deck, int &_TopOfDeck);
int UpdateHandTotal(Player* _current);
void init_deck(Card(&_deck)[52]);
void card_display(Card& _card);
void shuffle(Card _deck[]);
void cardDrawer(Card* _deck, Player &_player, int _TopOfDeck);
void card_display(Card &_card);
void init_deck(Card(&_deck)[52]);
void Pre_Start();
void start();
int main() {
  Pre_Start();
}
float LoopPreventer(int &x)
{
  while (!(std::cin >> x))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input.  Try again: ";

  }
  return x;
}
void init_deck(Card(&_deck)[52])
{
  for (int suit = 0; suit < 52; suit += 13)
  {
    for (int card = 0; card < 13; card++)
    {
      if (card > 9) { _deck[suit + card].m_value = 10; }
      else { _deck[suit + card].m_value = card + 1; }
      if (suit == 0) { strcpy_s(_deck[suit + card].m_suit, "Diamonds"); }
      if (suit == 13) { strcpy_s(_deck[suit + card].m_suit, "Hearts"); }
      if (suit == 26) { strcpy_s(_deck[suit + card].m_suit, "Clubs"); }
      if (suit == 39) { strcpy_s(_deck[suit + card].m_suit, "Spades"); }
      switch (card)
      {
      case 0: {strcpy_s(_deck[suit + card].m_name, "Ace"); break; }
      case 1: {strcpy_s(_deck[suit + card].m_name, "Two"); break; }
      case 2: {strcpy_s(_deck[suit + card].m_name, "Three"); break; }
      case 3: {strcpy_s(_deck[suit + card].m_name, "Four"); break; }
      case 4: {strcpy_s(_deck[suit + card].m_name, "Five"); break; }
      case 5: {strcpy_s(_deck[suit + card].m_name, "Six"); break; }
      case 6: {strcpy_s(_deck[suit + card].m_name, "Seven"); break; }
      case 7: {strcpy_s(_deck[suit + card].m_name, "Eight"); break; }
      case 8: {strcpy_s(_deck[suit + card].m_name, "Nine"); break; }
      case 9: {strcpy_s(_deck[suit + card].m_name, "Ten"); break; }
      case 10: {strcpy_s(_deck[suit + card].m_name, "Jack"); break; }
      case 11: {strcpy_s(_deck[suit + card].m_name, "Queen"); break; }
      case 12: {strcpy_s(_deck[suit + card].m_name, "King"); break; }
      }
    }
  }
}
int UpdateHandTotal(Player* _player)
{
  int total = 0;
  for (int i = 0; i < _player->m_cardIndex; i++)
  {
    total = _player->m_hand[i].m_value + total;
  }
  return total;
}
void card_display(Card &_card)
{

  std::cout << _card.m_name << " of " << _card.m_suit << ". Value : " << _card.m_value << std::endl;

}
void shuffle(Card _deck[])
{
  Card tmp = { 0 };
  int rnd = 0;
  for (int i = 0; i < 52; i++)
  {
    tmp = _deck[i];
    rnd = rand() % 52;
    _deck[i] = _deck[rnd];
    _deck[rnd] = tmp;
  }
}
void cardDrawer(Card* _deck, Player &_player, int _tod)				//This function runs to generate a card from the top of deck into the player's hand(or dealers). The way it does this is my assigning
{
  (_player.m_hand[_player.m_cardIndex++]) = CardDraw(_deck, _tod);				//When the function runs it takes into account whats the current card in the player's(or dealer) hand using the index which increases every time the function runs
  _player.m_handIndex++;
  _player.m_handTotal = UpdateHandTotal(&_player);							//We increase the index so that we can move from one card array to another within the hand. We assign that array to have the same value as the current top card of the deck
}																				//The new total value of your cards is stored in this integer which will be done to compare later on
void Pre_Start()																//This function is to create a menu
{
  bool Pre_Game_Starter = true;
  int input = 0;
  while (Pre_Game_Starter)
  {
    std::cout << "Welcome to my game of Blackjack" << std::endl;
    std::cout << "To start the game press 1" << std::endl;
    std::cout << "To check the rules press 2" << std::endl;
    std::cout << "To quit the game press 3" << std::endl;

    /*	while (!(std::cin >> input))
    {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input.  Try again: ";
    } */
    LoopPreventer(input);												//Function takes in the player input but prevents them from breaking the game when they enter
    switch (input)
    {

      {
    case 1:
    {
      std::cout << "The game is about to begin" << std::endl;
      start();

      break;
    }
    {
    case 2:
    {
      std::cout << "Rules" << std::endl;
      break;
    }
    case 3:
    {
      std::cout << "Goodbye" << std::endl;
      Pre_Game_Starter = false;
      break;
    }
    default:
    {
      std::cout << "Invalid Input" << std::endl;
      break;
    }

    }
      }
    }
  }
}
void start()
{
  bool  Start_Game = true;
  bool  Main_Game = false;
  bool GameBet = true;
  bool turn = true;
  bool Dealer_turn = true;
  Card myDeck[52] = { 0 };
  int top_of_deck = 0;
  bool draw = true;
  int input = 0;
  Player player;
  Player dealer;
  init_deck(myDeck);	//KEY
  std::cout << std::endl << "Initialized Deck" << std::endl;


  while (Start_Game)
  {
    while (GameBet)
    {
      std::cout << "Your Available Money is: " << player.wallet << ".How much would you like to bet?" << std::endl;
      std::cin.clear();
      LoopPreventer(player.bet);
      if (player.bet <= 0)
      {
        std::cout << "Amount is too low try again" << std::endl;
      }
      else if (player.bet < player.wallet && player.bet >0)
      {
        player.wallet = player.wallet - player.bet;
        std::cout << "You have bet:  " << player.bet << ". You have this much remaining in your Wallet: " << player.wallet << std::endl;
        Main_Game = true;
        GameBet = false;
      }
      else if (player.bet == player.wallet && player.bet > 0)
      {
        player.wallet = player.wallet - player.bet;
        std::cout << "You have bet:  " << player.bet << ". You have this much remaining in your Wallet: " << player.wallet << std::endl;
        Main_Game = true;
        GameBet = false;
      }
      else if (player.bet > player.wallet)
      {
        std::cout << "Amount is too high try again" << std::endl;
      }
    
    }
    //Player hand gets created
    srand(time(NULL));
    shuffle(myDeck);
    turn = true;
    Dealer_turn = true;
    for (int i = 0; i < 52; i++)
    {
      if (myDeck[i].m_value == 1)
      {
        //	std::cout << "value set to 11";
        myDeck[i].m_value = 11;
      }
    }
    std::cout << std::endl << "Deck Shuffled" << std::endl;
    //for (int i = 0; i < 52; i++) { card_display(myDeck[i]); }

    std::cout << "These are your cards: " << std::endl;

    cardDrawer(myDeck, player, top_of_deck++);
    card_display(player.m_hand[player.m_handIndex]);
    cardDrawer(myDeck, player, top_of_deck++);
    card_display(player.m_hand[player.m_handIndex]);
    std::cout << "Your Total Card Value: " << player.m_handTotal << std::endl;
    std::cout << "These are the opponent cards: " << std::endl;
    cardDrawer(myDeck, dealer, top_of_deck++);
    card_display(dealer.m_hand[dealer.m_handIndex]);
    cardDrawer(myDeck, dealer, top_of_deck++);
    std::cout << "This card is hidden until the dealer's turn" << std::endl;
    if (player.m_handTotal == 21 && dealer.m_handTotal != 21)
    {
      std::cout << "Automatic Victory " << std::endl;
      player.wallet = player.wallet + (player.bet * 2);
      dealer.m_cardIndex = 0;
      dealer.m_handIndex = -1;
      dealer.m_handTotal = 0;
      player.m_cardIndex = 0;
      player.m_handIndex = -1;
      player.m_handTotal = 0;
      top_of_deck = 0;
      GameBet = true;
      turn = false;
    }
    while (turn)
    {
      std::cout << "Would you like to hit(1) or stand(2)?" << std::endl;
      std::cin >> input;
      switch (input)
      {
      case 1:
      {
        cardDrawer(myDeck, player, top_of_deck++);
        std::cout << "You drew:" << std::endl;
        //Ace condition

        card_display(player.m_hand[player.m_handIndex]);
        std::cout << "Your Total Cards Value: " << player.m_handTotal << std::endl;
        if (player.m_handTotal > 21)
        {
          std::cout << "Your total hand value is over 21 you bust" << std::endl;
          dealer.m_cardIndex = 0;
          dealer.m_handIndex = -1;
          dealer.m_handTotal = 0;
          player.m_cardIndex = 0;
          player.m_handIndex = -1;
          player.m_handTotal = 0;
          player.bet = 0;
         top_of_deck = 0;
          GameBet = true;
          turn = false;
          player.bet = 0;
          Dealer_turn = false;
          turn = false;
          GameBet = true;
          if (player.bet == 0 && player.wallet == 0)
          {
            std::cout << "You Have run out of money" << std::endl;
            std::cout << "Returning to main menu" << std::endl;
            std::system("pause");
            std::system("CLS");
            
          }
        }
        break;
        turn = false;
      }
      case 2:
      {
        std::cout << "Dealer will show their card now it is" << std::endl;
        card_display(dealer.m_hand[dealer.m_handIndex]);
        std::cout << "Dealer Total Card Value: " << dealer.m_handTotal << std::endl;
        while (Dealer_turn)
        {
          if (dealer.m_handTotal < 17)
          {
            std::cout << "Dealer has less than 17 total card value he must draw" << std::endl;
            cardDrawer(myDeck, dealer, top_of_deck++);
            card_display(dealer.m_hand[dealer.m_handIndex]);
            std::cout << "Dealer Total Card Value: " << dealer.m_handTotal << std::endl;
          }
           if (dealer.m_handTotal > 16 && dealer.m_handTotal < 22)
          {
            std::cout << "Dealer has a total value of 17 or more he can't draw anymore" << std::endl;
            Dealer_turn = false;
          }
           if (dealer.m_handTotal > 21)
          {
            std::cout << "Dealer busted" << std::endl;
            std::cout << "You win" << std::endl;
            player.wallet = player.wallet + (player.bet * 2);
            dealer.m_cardIndex = 0;
            dealer.m_handIndex = -1;
            dealer.m_handTotal = 0;
            player.m_cardIndex = 0;
            player.m_handIndex = -1;
            player.m_handTotal = 0;
            top_of_deck = 0;
            Dealer_turn = false;
            turn = false;
            GameBet = true;
          }
        }
     if (dealer.m_handTotal == player.m_handTotal && dealer.m_handTotal>0 && player.m_handTotal>0)
    {
      std::cout << "Its a draw!!! Your bet has been returned to your wallet!" << std::endl;
      player.wallet = player.wallet + player.bet;
      dealer.m_cardIndex = 0;
      dealer.m_handIndex = -1;
      dealer.m_handTotal = 0;
      player.m_cardIndex = 0;
      player.m_handIndex = -1;
      player.m_handTotal = 0;
      top_of_deck = 0;

      Dealer_turn = false;
      GameBet = true;
      turn = false;
      break;
    }
     else  if (dealer.m_handTotal > player.m_handTotal && dealer.m_handTotal < 22)
        {
          std::cout << "Dealer wins" << std::endl;
          dealer.m_cardIndex = 0;
          dealer.m_handIndex = -1;
          dealer.m_handTotal = 0;
          player.m_cardIndex = 0;
          player.m_handIndex = -1;
          player.m_handTotal = 0;
          top_of_deck = 0;
          player.bet = 0;
          Dealer_turn = false;
          turn = false;
          GameBet = true;
          if (player.bet == 0 && player.wallet == 0)
          {
            std::cout << "You Have run out of money" << std::endl;
            std::cout << "Returning to main menu" << std::endl;
            std::system("pause");
              std::system("CLS");
            
            Start_Game = false;
          }
        }

        else if (dealer.m_handTotal < player.m_handTotal && player.m_handTotal < 22)
        {
          std::cout << "You win" << std::endl;
          player.wallet = player.wallet + (player.bet * 2);
          dealer.m_cardIndex = 0;
          dealer.m_handIndex = -1;
          dealer.m_handTotal = 0;
          player.m_cardIndex = 0;
          player.m_handIndex = -1;
          player.m_handTotal = 0;
          top_of_deck = 0;
          Dealer_turn = false;
          turn = false;
          GameBet = true;
        }

        break;
        turn = false;
      }

      default:
      {
        std::cout << "Inccorrect Input.Try Again" << std::endl;
      }
      }
    }
  }


}

