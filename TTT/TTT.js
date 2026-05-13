// get cells from HTML:
const cells = document.querySelectorAll('.cell');

// game state:
let myPlayer = 0;
let myTurn = false;
let gameOver = false;

// connect to the bridge via WebSocket:
const ws = new WebSocket("ws://127.0.0.1:6789");

// runs when connected to bridge:
ws.onopen = () => {
    console.log("Connected to bridge");
};
// runs if bridge connection drops:
ws.onclose = () => {
    alert("Disconnected from server");
};
// runs when messages arrive from the bridge:
ws.onmessage = (event) => {
    const msg = event.data;
// player detection:
    if (myPlayer === 0) {
        if (msg.includes("Player 1")) myPlayer = 1;
        else if (msg.includes("Player 2")) myPlayer = 2;
    }
// update board:
    if (msg.startsWith("MOVE:")) {
        const parts = msg.split(":");
        const pos = parseInt(parts[1]) - 1;
        const player = parseInt(parts[2]);
        cells[pos].textContent = player === 1 ? "X" : "O";
        cells[pos].disabled = true;
    }
// allow input:
    if (msg.includes("Enter number")) {
        myTurn = true;
    }
// disallow input:
    if (msg.includes("Waiting")) {
        myTurn = false;
    }
// move is invalid, reallow input:
    if (msg.includes("Invalid")) {
        myTurn = true;
        alert("That spot is taken, try again");
    }
// a player won, end game:
    if (msg.includes("VICTORY")) {
        gameOver = true;
        myTurn = false;
        alert(msg.trim());
    }
// draw, end game:
    if (msg.includes("draw")) {
        gameOver = true;
        myTurn = false;
        alert("Game is a draw!");
    }
};
// clicker handler for each cell:
cells.forEach((cell, index) => {
    cell.textContent = index + 1;
    cell.addEventListener('click', () => {
        // ignore click if game over/not your turn/cell taken:
        if (gameOver || !myTurn || cell.disabled) return; 

        // update cell, send move to server:
        const pos = index + 1;
        cell.textContent = myPlayer === 1 ? 'X' : 'O';
        cell.disabled = true;
        myTurn = false;

        ws.send(pos + "\n");
    });
});
// refresh:
document.getElementById('restart').addEventListener('click', () => {
    location.reload();
});
