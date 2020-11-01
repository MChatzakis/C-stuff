Name: Manos Chatzakis
Mail: csd4238@csd.uoc.gr

Compile using "make" or compile and run using "make run".

The "take_away" program simulates a simple take away procedure following the CoVid-19 regulations, using threads and semaphores.

The core idea is:

1) When a costumer arrives outside of the restaurant, he notifies the chef.
2) When the chef is available he calls the waiting customer inside.
3) The customer proceeds and gives the order to the chef, and he waits inside.
4) When the meal is ready, chef call the corresponding customer and gives him his food.
5) The chef waits for the customer to leave, and then calls the next customer inside.

The aforementioned tactic is executed for all the customers.

Note: When there are no active customers waiting outside, the chef is scrolling on facebook.

Using the above algorithm, POSIX threads and semaphores, we achieve the following:

-At any time, there is a probability that many customers are waiting outside, but always one
customer is inside the restaurant.
-Chef always waits for the previous customer to get outside to proceed to the next one.
-No matter how many customers are outside waiting for food, the chef achieves to serve them all.
-When there are no other customers, chef is scrolling on his facebook feed.
