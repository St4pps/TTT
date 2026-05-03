const cells = document.querySelectorAll('.cell');
const wins = [
  [0,1,2],[3,4,5],[6,7,8],
  [0,3,6],[1,4,7],[2,5,8],
  [0,4,8],[2,4,6]
];

let board = Array(9).fill('');
let currentPlayer = 'X';
let gameOver = false;

function checkWinner() {
  for (const [a, b, c] of wins) {
    if (board[a] && board[a] === board[b] && board[a] === board[c]) {
      return [a, b, c];
    }
  }
  return null;
}

cells.forEach((cell, index) => {
  cell.textContent = '';

  cell.addEventListener('click', () => {
    if (gameOver || board[index]) return;

    board[index] = currentPlayer;
    cell.textContent = currentPlayer;
    cell.disabled = true;

    const winCombo = checkWinner();
    if (winCombo) {
      winCombo.forEach(i => cells[i].style.backgroundColor = 'gold');
      alert(`Player ${currentPlayer} wins!`);
      gameOver = true;
    } else if (board.every(v => v)) {
      alert("It's a draw!");
      gameOver = true;
    } else {
      currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
    }
  });
});

document.getElementById('restart').addEventListener('click', () => {
  board = Array(9).fill('');
  currentPlayer = 'X';
  gameOver = false;
  cells.forEach(cell => {
    cell.textContent = '';
    cell.disabled = false;
    cell.style.backgroundColor = '';
  });
});
