# Noodle Shop

_Due Monday, August 10th, before midnight Pacific Time._




## Your Assignment

- Write a class that simulates running a noodle shop.
- You must serve all the customers whose orders you accept.
- You must make at least enough money to pay for your rent and ingredients.
- You can use anything from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.


## Your Day

Your day starts at eight in the morning, and is divided into minutes. You accept
orders until  eight in the evening,  and you keep your kitchen  open until eight
thirty to handle any orders that came in right before eight.

Every minute, the framework code will call two functions on your shop:

- First it will call  `orders(minute, orderlist)`  to let you know about any new
  orders coming in. Return a list of all the orders you choose to accept. If you
  want to reject an order you must do it here: there's no way to cancel an order
  that you previously accepted.

- Then it will call `action(minute)` to ask what you want in that minute. Return
  a new  `Action`  describing what you choose to do.  Your available actions are
  described in the Making Noodles section, below.

The `orders()` function  will be still called between eight and eight thirty PM,
but there will never be any new orders during this time.


## Making Noodles

To make noodles, all you need is a pot and ingredients! You have the ingredients
to make any number of meals, but you have a limited number of pots.  In order to
make money, you'll need to manage your pots carefully.  The actions you can take
all relate to your pots:

- Take the **cook** action to start a batch of noodles in a clean pot. Each type
  of noodle has a  _cook time_  and a  _batch size_.  The cook time  is how many
  minutes the noodle needs to cook, and the batch size is how many servings will
  be available once cooking is finished.

- Take the  **serve**  action to take noodles out of pots and  give them to your
  customers.  This is how  you get paid!  You can serve  any number of customers
  with a single serve action.

- Take the  **clean**  action to clean a pot.  If there are any noodles still in
  the pot, they will be discarded.  All your pots are initially clean.

- If you don't want to do any of these things, you can take no action.


## Getting Paid

Customers pay when they get their noodles.  If they don't have to wait very long
they'll give you a tip:

- Customers who get their noodles the same minute they order them will give you
  a one dollar (100 cent) tip.
- The tip decreases by ten cents per minute until it reaches zero. Customers who
  wait ten to fifteen minutes will pay for their noodles, but won't tip.
- Customers who wait more than fifteen minutes get their noodles free.


## Invalid Actions

- You can never use more pots than you have.
- You can't cook noodles in a dirty pot.
- You can't serve anyone stale noodles.
- You can't serve anyone undercooked noodles.
- You can't serve anyone the wrong type of noodle.
- You must fulfill orders for the same type of noodle in the order they came in.
- You must fulfill every order you accept exactly once.


## Extra Credit

To get full credit,  don't perform  any invalid actions,  fulfill all the orders
you accept,  and make enough money to pay for  your rent and any ingredients you
use.  To get extra credit,  make as much money as you can!  The best  submission
will get 10 extra points, the next best will get 9, and so on.
