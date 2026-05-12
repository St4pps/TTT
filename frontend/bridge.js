const net = require('net');
const { WebSocketServer } = require('ws');

const CPP_SERVER_IP = '127.0.0.1';
const CPP_SERVER_PORT = 8080;
const WS_PORT = 6789;

const wss = new WebSocketServer({ port: WS_PORT });

console.log(`Node.js bridge running on ws://127.0.0.1:${WS_PORT}`);

wss.on('connection', (ws) => {
    const tcp = new net.Socket();
    tcp.connect(CPP_SERVER_PORT, CPP_SERVER_IP);

    tcp.on('data', (data) => {
        if (ws.readyState === ws.OPEN) {
            ws.send(data.toString());
        }
    });

    ws.on('message', (message) => {
        tcp.write(message.toString());
    });

    tcp.on('close', () => {
        ws.close();
    });

    tcp.on('error', (err) => {
        ws.close();
    });

    ws.on('close', () => {
        tcp.destroy();
    });

    ws.on('error', (err) => {
        tcp.destroy();
    });
});
