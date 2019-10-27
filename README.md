# OS Assignment

### Links
- [Contribution guidelines for this project](##Cigarette-Smokers-Problem)

## Cigarette Smokers Problem

Four threads are involved: an agent and three smokers. The smokers loop forever, first waiting for
ingredients, then making and smoking cigarettes. The ingredients are tobacco, paper, and matches.
We assume that the agent has an infinite supply of all three ingredients, and each smoker has an
infinite supply of one of the ingredients; that is, one smoker has matches, another has paper, and
the third has tobacco.

The agent repeatedly chooses two different ingredients at random and makes them available to the
smokers. Depending on which ingredients are chosen, the smoker with the complementary
ingredient should pick up both resources and proceed. For example, if the agent puts out tobacco
and paper, the smoker with the matches should pick up both ingredients, make a cigarette, and then
signal the agent. To explain the premise, the agent represents an operating system that allocates
resources, and the smokers represent applications that need resources.

The problem is to make sure that if resources are available that would allow one or more
applications to proceed, those applications should be woken up. Conversely, we want to avoid
waking an application if it cannot proceed.

The restriction imposed on the system is you are not allowed to modify the agent code. If the agent
represents an operating system, it makes sense to assume that you don’t want to modify it every
time a new application comes along. So the abilities of the agent remain as defined in the problem.

## Producer Consumer Problem

In this problem, two processes, one called the producer and the other called the consumer, run concurrently and
share a common buffer. The producer generates items that it must pass to the consumer, who is to consume them.
The producer passes items to the consumer through the buffer. However, the producer must be certain that it does
not deposit an item into the buffer when the buffer is full, and the consumer must not extract an item from an empty
buffer. The two processes also must not access the buffer at the same time, for if the consumer tries to extract an
item from the slot into which the producer is depositing an item, the consumer might get only part of the item. Any
solution to this problem must ensure none of the above three events occur. Because the buffer has a maximum size,
this problem is often called the bounded buffer problem.

## The Barbershop Problem

A barbershop consists of a waiting room with n chairs, and the barber room containing the barber
chair. If there are no customers to be served, the barber goes to sleep. If a customer enters the
barbershop and all chairs are occupied, then the customer leaves the shop. If the barber is busy,
but chairs are available, then the customer sits in one of the free chairs. If the barber is asleep, the
customer wakes up the barber. Write a program to coordinate the barber and the customers.

To make the problem a little more concrete, the following information is added:
- Customer threads should invoke a function named getHairCut.
- If a customer thread arrives when the shop is full, it can invoke balk, which does not return.
- Barber threads should invoke cutHair.
- When the barber invokes cutHair, there should be exactly one thread invoking getHairCut
concurrently
