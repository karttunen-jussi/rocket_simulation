
from websockets.sync.server import serve

def WebSocketHandler(websocket):
    
    # Handle received rocket power commands from UI
    for message_received in websocket:
        print(message_received)

        message_response = "Received this message: " + message_received
        websocket.send(message_response)

# Connect Websocket with the Rocket UI
port_websocket = 8765
with serve(WebSocketHandler, "localhost", port_websocket) as server:
    server.serve_forever()
