const net = require('net');
const { WebSocketServer } = require('ws');

//C++ server connection:
const CPP_SERVER_IP = '127.0.0.1';
const CPP_SERVER_PORT = 8080;
//browser connects to this port:
const WS_PORT = 6789;

//create WS server to connect to:
const wss = new WebSocketServer({ host: '0.0.0.0', port: WS_PORT });

console.log(`Node.js bridge running on ws://127.0.0.1:${WS_PORT}`);

//runs every time browser connects to bridge:
wss.on('connection', (ws) => {
    // creates TCP connection to c++ server for browser:
    const tcp = new net.Socket();
    tcp.connect(CPP_SERVER_PORT, CPP_SERVER_IP);
    
// forward data from c++ server to the browser:
    tcp.on('data', (data) => {
        if (ws.readyState === ws.OPEN) {
            ws.send(data.toString());
        }
    });
// when browser sends move, forward to c++ server:
    ws.on('message', (message) => {
        tcp.write(message.toString());
    });
// close browser connection if server dc's:
    tcp.on('close', () => {
        ws.close();
    });
// close browser connection if errors:
    tcp.on('error', (err) => {
        ws.close();
    });
// close server connection if browser dc's:
    ws.on('close', () => {
        tcp.destroy();
    });
// close server connection if browser errors:
    ws.on('error', (err) => {
        tcp.destroy();
    });
});
