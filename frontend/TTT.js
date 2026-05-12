const cells = document.querySelectorAll('.cell');

let myPlayer = 0;
let myTurn = false;
let gameOver = false;

const ws = new WebSocket("ws://127.0.0.1:6789");

ws.onopen = () => {
    console.log("Connected to bridge");
};

ws.onclose = () => {
    alert("Disconnected from server");
};

ws.onmessage = (event) => {
    const msg = event.data;

    if (myPlayer === 0) {
        if (msg.includes("Player 1")) myPlayer = 1;
        else if (msg.includes("Player 2")) myPlayer = 2;
    }

    if (msg.startsWith("MOVE:")) {
        const parts = msg.split(":");
        const pos = parseInt(parts[1]) - 1;
        const player = parseInt(parts[2]);
        cells[pos].textContent = player === 1 ? "X" : "O";
        cells[pos].disabled = true;
    }

    if (msg.includes("Enter number")) {
        myTurn = true;
    }

    if (msg.includes("Waiting")) {
        myTurn = false;
    }

    if (msg.includes("Invalid")) {
        myTurn = true;
        alert("That spot is taken, try again");
    }

    if (msg.includes("VICTORY")) {
        gameOver = true;
        myTurn = false;
        alert(msg.trim());
    }

    if (msg.includes("draw")) {
        gameOver = true;
        myTurn = false;
        alert("Game is a draw!");
    }
};

cells.forEach((cell, index) => {
    cell.textContent = index + 1;
    cell.addEventListener('click', () => {
        if (gameOver || !myTurn || cell.disabled) return;

        const pos = index + 1;
        cell.textContent = myPlayer === 1 ? 'X' : 'O';
        cell.disabled = true;
        myTurn = false;

        ws.send(pos + "\n");
    });
});

document.getElementById('restart').addEventListener('click', () => {
    location.reload();
});
