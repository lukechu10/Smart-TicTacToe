# Smart TicTacToe:

## What does it do?

Smart TicTacToe adds a function to your Node.js app that returns the best move possible for the computer in a TicTacToe game. It is impossible to loose with this algorithm.

## Methods:
>`bestMove(<gameBoard type = array[9]>` : Returns the position that has the highest chance of winning (*See figures under ## Examples*)<br>**Note**: Computer is always `O` support to change has not yet been released.

## Examples:

Smart TictacToe is really simple to use:
```javascript
var tictactoe = require('smart-tictactoe');<br>
console.log(tictactoe.bestMove(o   xxo x);<br>
```
___
This logs `4` in the console because `tictactoe.bestMove()` returns the best location for the computer if the scenario was:

  O  |  _  |  _
-----|-----|-----
**_**|**X**|**X**
**O**|**_**   |**X**

Which is `3` to prevent `X` from winning because the TicTacToe board is stored as a array:
  0  |  1  |  2
-----|-----|-----
 `3` |**4**|**5**
**6**|**7**|**8**

## Installation

You can install Smart-TicTacToe like any other npm module:
```
npm install smart-tictactoe
```
Smart-TicTacToe does not require any external dependencies.