# Orderbook
![Test](https://github.com/jordan12sam/Orderbook/actions/workflows/test.yml/badge.svg)

An efficient c++ implementation of a limit order book (LOB). Functionality is kept simple, supporting just limit orders, cancellations and executions. Orders arer matched based on price time priority.

The bid & ask book are stored as min & max heaps respectively, sortyed by price, with each price limit in the heap represented as a doubly linked list of orders sorted by timestamp. This is computationally benificial compared to storing the orders directly in the heap with a price time priority, since insertions and removals within the heap happen in logarithmic time, whereas a double linked list is constant.

Limits and volumes are kept in hashmaps with price as the key, and orders are kept with an ID key.

This offers very favourable time complexity for key operations:

- Getting the top priority order from the heap is O(1)
- Getting the volume at a price point is O(1)
- Adding an order to an existing limit is O(1)
- Removing any but the last order from a limit is O(1)
- Adding the first order to a limit is O(logn)
- Removing the last order from a limit is O(logn)

Where n is the number of discrete limits in the heap.

## Build & Run

Clone the repo to your local machine:
```
git clone https://github.com/jordan12sam/Orderbook.git
```
Run the build script:
```
./build.ps1
```
And run the application executable:
```
./orderbook-app.exe
```
Run unit tests:
```
./orderbook-test.exe
```
