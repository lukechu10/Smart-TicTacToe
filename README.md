# Smart TicTacToe:

## What does it do?

Smart TicTacToe adds a function to your Node.js app that returns the best move possible for the computer in a TicTacToe game. It is impossible to loose with this algorithm.

## Methods:
>`bestMove(<gameBoard (type is a string with a length of 9 characters)>` : Returns the position that has the highest chance of winning (*See figures under ## Examples*)<br>**Note**: Computer is always `O` support to change has not yet been released.

>`conversionTest(<String to test>)` : For testing purposes only.

>`checkWin(<gameBoard>)` : Returns if someone won or not. If no one wins, it returns an empty string.
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

## What's New in this Update:

+ Added method `bestMoveDebug`

## Installation:

You can install Smart-TicTacToe like any other npm module:
```
npm install smart-tictactoe
```

Or, if you want to install it globally:
```
npm install -g smart-tictactoe
```

Smart-TicTacToe requires node-gyp to compile source.

## License:

Copyright (c) 2018 Luke Chu <[lukechu10@gmail.com](mailto:lukechu10@gmail.com)>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
